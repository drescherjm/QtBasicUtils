#include "QCmdLine.h"
#include "QCmdHelp.h"
#include "QCmdParseError.h"
#include <QFile>
#include <QTextStream>

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdLine::QCmdLine(QString strProgName, QStringList & strLst) :  
		m_strProgName(strProgName),m_strLstCmdLine(strLst)
	{		
		Initialize();
	}


/////////////////////////////////////////////////////////////////////////////////////////

	QCmdLine::QCmdLine()
	{
		Initialize();	
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdLine::~QCmdLine()
	{
		destroy();
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdLine::iterator QCmdLine::begin()
	{
		return m_strLstLstCmdLine.begin();
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdLine::iterator QCmdLine::end()
	{
		return m_strLstLstCmdLine.end();
	}

/////////////////////////////////////////////////////////////////////////////////////////

	int QCmdLine::AddCmd(QCmd *pCmd)
	{
		QString strCmd;
		int retVal = QCmdParseError::STATUS_OK;
		if ( pCmd != NULL ) {
			pCmd = dynamic_cast<QCmd*>(pCmd);
			if ( pCmd != NULL ) {
				strCmd = GetCommandString(pCmd->GetName());

				QCmdMap::iterator it = m_mapCmd.find(strCmd);

				if ( it != m_mapCmd.end() ) {
					pCmd = it.value();
					retVal = QCmdParseError::COMMAND_ALLREADY_ADDED;
				}	
				else
					if ( pCmd != NULL ) {
						m_mapCmd.insert(strCmd,pCmd);
						m_listCmds.push_back(pCmd);
					}
					QCmdHelp* pCmdHelp = dynamic_cast<QCmdHelp*>(pCmd);
					if ( pCmdHelp ) {
						pCmdHelp->m_pCmdLine = this;
					}
			}
		}
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	int QCmdLine::GetNextCommand(QCmdLine::iterator & it,QCmd *& pCmd)
	{
		int retVal = QCmdParseError::STATUS_OK;
		pCmd = NULL;
		QStringList* pStrLstCmd;
		QString str;

		if ( !m_listCmds.isEmpty() ) {
			if ( it != end() ) {
				
				pStrLstCmd = *it;
				it++;

				if ( pStrLstCmd ) {
					if (!pStrLstCmd->isEmpty()) {
						QStringList::iterator itStrLst = pStrLstCmd->begin();

						str = *itStrLst;
						itStrLst++;

						//The following will convert the command to all uppercase if 
						// m_bIgnoreCase is true
						str = GetCommandString(str.mid(1));

						QCmdMap::iterator itMap = m_mapCmd.find(str);

						if ( itMap != m_mapCmd.end() ) {
							
							pCmd = itMap.value();

							if ( pCmd ) {
								pCmd->m_strLstCmd.clear();
								while(itStrLst != pStrLstCmd->end()) {
									
									str = *itStrLst;
									itStrLst++;

									pCmd->m_strLstCmd.push_back(str);
								}
							}
							else
							{
								retVal = QCmdParseError::MEMORY_CORRUPTION_ERROR;
							}
						}
						else 
						{
							retVal = QCmdParseError::PARAM_NOT_COMMAND;
						}
					}
					else
					{
						retVal = QCmdParseError::COMMAND_NOT_SEPARATED;
					}
				}
			}
		}
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	void QCmdLine::Initialize()
	{
		m_strCmdSep = (";");
		m_chCmdChar = '+';
		m_bIgnoreCase = TRUE;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QString QCmdLine::GetCommandString(QString strCmd)
	{
		if (m_bIgnoreCase) {
			strCmd = strCmd.toUpper();
		}
		return strCmd;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdLine::QCmdLine(int argc, char *argv[])
	{
		Initialize();
		if ( argc > 0 ) {
			m_strProgName = argv[0];
			for(int i=1;i < argc;i++) {
				m_strLstCmdLine.push_back(argv[i]);
			}
		}
	}

/////////////////////////////////////////////////////////////////////////////////////////

	void QCmd::EndRequiredArguments()
	{
		m_bOptional = true;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QString QCmdLine::GetSyntax()
	{
		QString retVal;
		QCmd* pCmd;
		
		QCmdList::iterator it;
		for (it = m_listCmds.begin(); it != m_listCmds.end();++it) {
			pCmd = *it;
			retVal += m_strProgName + (" ");
			retVal += pCmd->GetSyntax();
			retVal += ("\n ");
		}
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	void QCmdLine::destroy()
	{
		QStringList* pLst;
		
		QStrLstList::iterator it;

		for(it = m_strLstLstCmdLine.begin(); it != m_strLstLstCmdLine.end();++it) {
			pLst = *it;
			delete pLst;
		}

		m_strLstLstCmdLine.clear();
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QCmd* QCmdLine::GetDefaultCmd()
	{
		QCmd* retVal = NULL;
		if ( !m_listCmds.isEmpty() ) { 
			retVal = *m_listCmds.begin();
		}
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	int QCmdLine::PreProcess(QStringList & strList)
	{
		int retVal = QCmdParseError::STATUS_OK;
		QStringList strListTmp = strList;
		strList.clear();

		QStringList::iterator it;
		for(it = strListTmp.begin(); 
			it !=strListTmp.end() && (retVal == QCmdParseError::STATUS_OK);++it) {

			QString strTemp = *it;
			if (!strTemp.isEmpty()) {
				if (strTemp[0] == '@') {
					QStringList strLstFile;
					retVal = ParseFile(strTemp.mid(1),strLstFile);
					if (retVal == QCmdParseError::STATUS_OK) {
						strList += strLstFile;
					}
				}
				else
					strList.push_back(strTemp);
			}
			else
				strList.push_back(strTemp);
		}
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	bool QCmdLine::IsCmdChar(QString str)
	{
		bool retVal = FALSE;

		if ( !str.isEmpty() ) {
			retVal = (str[0] == m_chCmdChar);
		}
		return retVal;
	}


/////////////////////////////////////////////////////////////////////////////////////////

	int QCmdLine::Parse()
	{
		return Parse(m_strLstCmdLine);
	}

/////////////////////////////////////////////////////////////////////////////////////////

	int QCmdLine::Parse(QStringList & strList)
	{

		int retVal = PreProcess(strList);
		if (retVal == QCmdParseError::STATUS_OK) {
			destroy();
			QString str;
			QStringList* pStrLst = NULL;
			
			QStringList::iterator it;

			for(it = strList.begin(); it != strList.end();++it) {
				str = *it;
				if ( pStrLst == NULL ) {
					pStrLst = new QStringList;
					pStrLst->push_back(str);
				}
				else
					if ( IsCmdChar( str ) ) {
						m_strLstLstCmdLine.push_back(pStrLst);
						pStrLst = new QStringList;
						pStrLst->push_back(str);
					}
					else
					{
						pStrLst->push_back(str);
					}
			}
			if ( pStrLst != NULL ) {
				if ( !pStrLst->isEmpty()) {
					m_strLstLstCmdLine.push_back(pStrLst);
					pStrLst = NULL; 
				}
				else
				{
					delete pStrLst;
				}
			}

			QStrLstList::iterator itLstLst = begin();
			while( itLstLst != end() ) {
				
				pStrLst = *itLstLst;
				itLstLst++;

				QStringList::iterator it = pStrLst->begin();
				if ( it != pStrLst->end() ) {
					str = *it;
					if ( !IsCmdChar( str ) ) {
						QCmd* pCmd = GetDefaultCmd();
						if ( pCmd ) {
							str.sprintf("%c%s",m_chCmdChar,GetCommandString(pCmd->GetName()));
							pStrLst->push_front(str);
						}
						else
						{
							retVal = QCmdParseError::NO_DEFAULT_COMMAND;
							break;
						}
					}
				}
				else
				{
					retVal = QCmdParseError::COMMAND_NOT_SEPARATED;
					break;
				}
			}
		}

		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	int QCmdLine::ParseFile(QString strFileName,QStringList & strLstFile)
	{
		int retVal = QCmdParseError::STATUS_OK;
		
		QFile sourceFile(strFileName);
		if (sourceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

			QTextStream in(&sourceFile);
			while (!in.atEnd()) {
				QString line = in.readLine();

				strLstFile.push_back(line);
			}
		}
		else
			retVal = QCmdParseError::FILE_MUST_EXIST;

		return retVal;
	}
}; //namespace QTUTILS
