#include "qbuCmdLinePCH.h"

#include "qbuCmdLine/QCmdLine.h"
#include "qbuCmdLine/QCmdHelp.h"
#include "qbuCmdLine/QCmdParseError.h"
#include "qbuCmdLine/QCmdParseException.h"


/////////////////////////////////////////////////////////////////////////////////////////

	class QCmdLine::qtutilsPrivate
	{
	public:
		qtutilsPrivate();
		qtutilsPrivate(QString strProgName, QStringList & strLst);
	public:
		void	initialize();
	public:
		QStringList		m_strLstCmdLine;
		QStrLstList		m_strLstLstCmdLine;
		QCmdList		m_listCmds;
		QCmdMap			m_mapCmd;
		QString			m_strProgName;
		bool			m_bIgnoreCase;
		QChar			m_chCmdChar;
		QString			m_strCmdSep;
	};

/////////////////////////////////////////////////////////////////////////////////////////
	
	QCmdLine::qtutilsPrivate::qtutilsPrivate() 
	{
		initialize();
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdLine::qtutilsPrivate::qtutilsPrivate(QString strProgName, QStringList & strLst) :
		m_strProgName(strProgName),m_strLstCmdLine(strLst)
	{
		initialize();
	}

/////////////////////////////////////////////////////////////////////////////////////////

	void QCmdLine::qtutilsPrivate::initialize()
	{
		m_strCmdSep = (";");
		m_chCmdChar = '+';
		m_bIgnoreCase = true;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdLine::QCmdLine(QString strProgName, QStringList & strLst)
	{		
		m_pPrivate = new qtutilsPrivate(strProgName,strLst);
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdLine::QCmdLine(int argc, char *argv[])
	{
		m_pPrivate = new qtutilsPrivate();
		if ( argc > 0 ) {
			m_pPrivate->m_strProgName = argv[0];
			for(int i=1;i < argc;i++) {
				m_pPrivate->m_strLstCmdLine.push_back(argv[i]);
			}
		}
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdLine::QCmdLine()
	{
		m_pPrivate = new qtutilsPrivate();	
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdLine::QCmdLine( QTextStream & args )
	{
		m_pPrivate = new qtutilsPrivate();	
		ParseStream(args,m_pPrivate->m_strLstCmdLine);
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdLine::~QCmdLine()
	{
		destroy();
		delete m_pPrivate;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdLine::iterator QCmdLine::begin()
	{
		return m_pPrivate->m_strLstLstCmdLine.begin();
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdLine::iterator QCmdLine::end()
	{
		return m_pPrivate->m_strLstLstCmdLine.end();
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

				QCmdMap::iterator it = m_pPrivate->m_mapCmd.find(strCmd);

				if ( it != m_pPrivate->m_mapCmd.end() ) {
					pCmd = it.value();
					retVal = QCmdParseError::COMMAND_ALLREADY_ADDED;
				}	
				else
					if ( pCmd != NULL ) {
						m_pPrivate->m_mapCmd.insert(strCmd,pCmd);
						m_pPrivate->m_listCmds.push_back(pCmd);
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

		if ( !m_pPrivate->m_listCmds.isEmpty() ) {
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

						QCmdMap::iterator itMap = m_pPrivate->m_mapCmd.find(str);

						if ( itMap != m_pPrivate->m_mapCmd.end() ) {
							
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
								QCmdParseException::Throw(retVal,str);
							}
						}
						else 
						{
							retVal = QCmdParseError::PARAM_NOT_COMMAND;
							QCmdParseException::Throw(retVal,str);
						}
					}
					else
					{
						retVal = QCmdParseError::COMMAND_NOT_SEPARATED;
						QCmdParseException::Throw(retVal,str);
					}
				}
			}
		}
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QString QCmdLine::GetCommandString(QString strCmd)
	{
		if (m_pPrivate->m_bIgnoreCase) {
			strCmd = strCmd.toUpper();
		}
		return strCmd;
	}

/////////////////////////////////////////////////////////////////////////////////////////

		QString QCmdLine::GetSyntax(bool bShort)
	{
		QString retVal;
		QCmd* pCmd;
		
		QCmdList::iterator it;
		for (it = m_pPrivate->m_listCmds.begin(); it != m_pPrivate->m_listCmds.end();++it) {
			pCmd = *it;
			retVal += m_pPrivate->m_strProgName + (" ");
			retVal += pCmd->GetSyntax(bShort);
			retVal += ("\n ");
		}
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	void QCmdLine::destroy()
	{
		QStringList* pLst;
		
		QStrLstList::iterator it;

		for(it = m_pPrivate->m_strLstLstCmdLine.begin(); it != m_pPrivate->m_strLstLstCmdLine.end();++it) {
			pLst = *it;
			delete pLst;
		}

		m_pPrivate->m_strLstLstCmdLine.clear();
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QCmd* QCmdLine::GetDefaultCmd()
	{
		QCmd* retVal = NULL;
		if ( !m_pPrivate->m_listCmds.isEmpty() ) { 
			retVal = *m_pPrivate->m_listCmds.begin();
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
					else
					{
						// This recreates the command line for the Throw
						strList.push_back(strTemp);
						for(++it; it != strListTmp.end();++it) {
							strList.push_back(*it);
						}
						QCmdParseException::Throw(retVal," while parsing ",strList,
							strTemp.mid(1));
					}
				}
				else
					strList.push_back(strTemp);
			}
			else
				strList.push_back(strTemp);
		}

		foreach(QString str,strList) {
			std::cout << str.toStdString() << std::endl;
		}
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	bool QCmdLine::IsCmdChar(QString str)
	{
		bool retVal = false;

		if ( !str.isEmpty() ) {
			retVal = (str[0] == m_pPrivate->m_chCmdChar);
		}
		return retVal;
	}


/////////////////////////////////////////////////////////////////////////////////////////

	int QCmdLine::Parse()
	{
		return Parse(m_pPrivate->m_strLstCmdLine);
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
						m_pPrivate->m_strLstLstCmdLine.push_back(pStrLst);
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
					m_pPrivate->m_strLstLstCmdLine.push_back(pStrLst);
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
							str = QString("%1%2")
								.arg(m_pPrivate->m_chCmdChar)
								.arg(GetCommandString(pCmd->GetName()));
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
		QCmdParseException::Throw(retVal," while parsing ",strList);
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	int QCmdLine::ParseFile(QString strFileName,QStringList & strLstFile)
	{
		int retVal = QCmdParseError::STATUS_OK;

		bool bUseMachineFile{ strFileName.startsWith('@') };

		if (bUseMachineFile) {
			strFileName = strFileName.mid(1);
		}
		
		QFile sourceFile(strFileName);
		if (sourceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

			QTextStream in(&sourceFile);

			retVal = ParseStream(in,strLstFile);
		}
		else
			retVal = QCmdParseError::FILE_MUST_EXIST;


		if (bUseMachineFile) {

			//QString strHostName = QHostInfo::localHostName();

			QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

			if (env.contains("COMPUTERNAME")) {

				QString strHostName = env.value("COMPUTERNAME");

				QFileInfo fi(strFileName);

				//fi.completeBaseName()

				QString strFileName = fi.path() + '/' + fi.completeBaseName() + '.' + strHostName + fi.suffix();


				QFile sourceFile(strFileName);
				if (sourceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

					QTextStream in(&sourceFile);

					ParseStream(in, strLstFile);
				}
			}
		}

		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

QStringList moveToNextQuote(QStringList & lst)
{
	QStringList retVal;

	while(!lst.isEmpty()) {
		QString front = lst.first();

		// Match ' or " but not \' or \"
		// QRegExp("[^\\][\'\"]")
		if (!front.contains(QRegExp("[^\\\\][\'\"]"))) {
			retVal.push_back(front);
			lst.pop_front();
		}
		else
			break;
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString handleStartingSingleQuote(QString strFront, QStringList & lst)
{
	bool bDoubleQuote=false;
	QString retVal;
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString handleStartingDoubleQuote(QString strFront, QStringList & lst)
{
	bool bSingleQuote=false;
	QString retVal;
	int nIndex = strFront.indexOf(QRegExp("[\'\"]"),1);

	while ( (nIndex >= 0) && (strFront[nIndex-1] == QChar('\\')) ) {
		nIndex = strFront.indexOf(QRegExp("[\'\"]"),nIndex);
	}

	if (nIndex > 0) {

	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QStringList handleQuotes(QStringList & lst)
{
	QStringList retVal = moveToNextQuote(lst);

	if (!lst.isEmpty()) {
		QString front = lst.first();
		lst.pop_front();
		if (lst.size() > 1) {

			if (front.contains(QRegExp("[^\\\\][\'\"]"))) {
				int nIndex = front.indexOf(QRegExp("[\'\"]"));

				while ( (nIndex != 0) && (front[nIndex-1] == QChar('\\')) ) {
					nIndex = front.indexOf(QRegExp("[\'\"]"),nIndex);
				}
				if (nIndex >= 0) {
					QChar ch = front[nIndex];
					if (ch == QChar('\"')) {
						front = front.left(nIndex) + handleStartingDoubleQuote(front.mid(nIndex),lst);
					}
					else
					{
						front = front.left(nIndex) + handleStartingSingleQuote(front.mid(nIndex),lst);
					}
				}
			}
		}
		
		retVal.push_back(front);
	}

	if (!lst.isEmpty()) {
		retVal += handleQuotes(lst);
	}
	
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

QStringList handleQuotes(QString str)
{
	QRegExp rx2("[\\s\'\"]");
	QStringList list;

	int nSingle = 0;
	int nDouble = 0;

 	int start = 0;
 	int extra = 0;
 	int end;
 	while ((end = rx2.indexIn(str, start + extra)) != -1) {

		// Just continue if the found item is escaped.
		if (end > 0) {
			if (str[end-1] == QChar('\\')) {
				extra = end - start + 1;
				continue;
			}
		}

		int matchedLen = rx2.matchedLength();
		if (start != end) {
				
			QString strMatch = str.mid(end,matchedLen);
			if (strMatch.contains(QRegExp("\\s"))) {
				if ((nDouble == 0) && (nSingle == 0)) {
					list.append(str.mid(start, end - start));
				}
				else
				{
					extra = end - start + 1;
					continue;
				}
				
			}
			else
				if ((nDouble == 0) && (nSingle == 0)) {
					if (strMatch.contains("\"")) {
						nDouble++;
					}
					else
					{
						nSingle++;
					}
					extra = end - start + 1;
					continue;
			}
			else
			{
				// We have hit a second quote.
				if (nDouble == 1) {
					if (strMatch.contains("\"")) {
						nDouble=0;
						list.append(str.mid(start, end + matchedLen - start));
					}
					else
					{
						// Ignore nested single quotes inside double quotes
						extra = end - start + 1;
						continue;
					}
				}
				if (nSingle == 1) {
					if (strMatch.contains("\'")) {
						nSingle=0;
						list.append(str.mid(start, end + matchedLen - start));
					}
					else
					{
						// Ignore nested double quotes inside single quotes
						extra = end - start + 1;
						continue;
					}
				}
			}
			 			
			
		}
		else
		{
			// This means the match is at the beginning. 
			QString strMatch = str.mid(end,matchedLen);
			if (!strMatch.contains(QRegExp("\\s"))) {
				if ((nDouble == 0) && (nSingle == 0)) {
					if (strMatch.contains("\"")) {
						nDouble++;
					}
					else
					{
						nSingle++;
					}
					extra = end - start + 1;
					continue;
				}
			}
		}
		start = end + matchedLen;
		extra = (matchedLen == 0) ? 1 : 0;
 	}
 	if (start != str.size())
 		list.append(str.mid(start));
	return list;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdLine::ParseStream( QTextStream & argStream,QStringList & strLstFile )
{
	int retVal = QCmdParseError::STATUS_OK;
// 	int nQuoteCount = 0;
// 	//Attempt to handle quotes!
// 	QString strQuoted;
// 
// 	while (!argStream.atEnd()) {
// 		QString str;
// 		argStream >> str; // This gets upto the first whitespace
// 		str.trimmed();
// 
// 		if (!str.isEmpty()) {
// 			int nQuotes = str.count('\"');
// 
// 			nQuoteCount += nQuotes;
// 
// 			if ( (nQuoteCount % 2) == 1) {
// 				if (!strQuoted.isEmpty()) {
// 					strQuoted.append(' ');
// 				}
// 				strQuoted.append(str);
// 				str.clear();
// 			}
// 			else
// 				if (strQuoted.isEmpty()) {
// 					strLstFile.push_back(str);
// 				}
// 				else
// 				{
// 					if (!str.isEmpty()) {
// 						strQuoted.append(' ');
// 						strQuoted.append(str);
// 					}
// 					strLstFile.push_back(strQuoted);
// 					strQuoted.clear();
// 				}
// 
// 		}
// 
// 	}
// 	if (!strQuoted.isEmpty()) {
// 		strLstFile.push_back(strQuoted);
// 	}

	QString str = argStream.readAll();
// 	if (!str.isEmpty()) {
// 		QString pattern("((?:[^\\s\"]+)|(?:\"(?:\\\\\"|[^\"])*\")|(?:[^\\s\']+)|(?:\'(?:\\\\\'|[^\'])*\'))");
// 
// 		QRegExp rx(pattern);
// 		int pos = 0;
// 
// 		//QStringList lst;
// 		while ((pos = rx.indexIn(str, pos)) != -1) {
// 			//qDebug() << rx.capturedTexts();
// 			//qDebug() << rx.cap(1);
// 
// 			strLstFile << rx.cap(1);
// 			pos += rx.matchedLength();
// 		}
// 	}

	// Split the string on any whitespace.
	//QStringList lst = str.split(QRegExp("[\\s+[^\\\\][\'\"]]"));
	
	//QStringList lst = str.split(QRegExp("[^\\\\][\\s+\'\"]"));
	
	//strLstFile = handleQuotes(lst);

	strLstFile = handleQuotes(str);

	return retVal;
}


/////////////////////////////////////////////////////////////////////////////////////////

QCmdList QCmdLine::getAvailableCommands()
{
	return m_pPrivate->m_listCmds;
}

/////////////////////////////////////////////////////////////////////////////////////////

void QCmdLine::setAvailableCommands( QCmdList & lstCommands )
{
	m_pPrivate->m_listCmds.clear();
	m_pPrivate->m_mapCmd.clear();

	QCmdList::iterator it = lstCommands.begin();
	for(;it != lstCommands.end();++it) {
		AddCmd(*it);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
