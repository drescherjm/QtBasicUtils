/////////////////////////////////////////////////////////////////////////////////////////

#include "QCmd.h"
#include "QCmdArg.h"
#include "QCmdOpt.h"
#include "QCmdParseError.h"
#include "QCmdOptBool.h"
#include "QCmdParseException.h"
#include "QCmdOptBasic.h"
#include "QCmdOptQChar.h"
#include "QCmdOptQString.h"
#include "QCmdOptQStringList.h"

#include "QCmdArgBool.h"
#include "QCmdArgBasic.h"
#include "QCmdArgQChar.h"
#include "QCmdArgQString.h"
#include "QCmdArgQStringList.h"
#include "QCmdArgFileList.h"
#include "QCmdHelpException.h"

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

struct QCmd::qtutilsPrivate
{
public:
	qtutilsPrivate(QCmd* pParent,QString strName,QString strDescription, 
		QString strExplanation=QString(),bool bIgnoreCase = true);

	~qtutilsPrivate();

public:
	void	Initialize();
	int		AddOpt(QString strName, QCmdOpt* pOpt = NULL);
	int		FindOpt(QString strName, QCmdOpt *& option);
	QString GetOptString( QString strName );
	int		AddArg(QString strName, QCmdArg* pArg = NULL);
	int		FindArg(QString strName, QCmdArg *& ARGUMENT);
	QString GetSyntax();
	QString	GetName();
	QString	GetDescription();
	QString	GetExplanation();
	int     Parse();
	int		Parse(QStringList & strLst);
	int		IsOption(QString & str, QCmdOpt *& pOption);
	bool	wasSuccessful( int nRetCode ) const;
	QString exportCommandString(QChar chCommand);
public:
	template <typename ValType,typename OptType>  int AddOpt(QString strName, 
		QString strDescription, QString strExplanation, ValType nDefaultValue,
		ValType nMinVal, ValType nMaxVal);
	template <typename ValType,typename OptType>  int AddArg(QString strName, 
		QString strDescription, QString strExplanation, ValType nDefaultValue,
		ValType nMinVal, ValType nMaxVal);
	template <typename ValType,typename OptType> int SetOpt(QString strName, ValType val);
	template <typename ValType,typename ArgType> int SetArg(QString strName, ValType val);

	template <typename ValType,typename OptType> int GetOpt(QString strName, ValType & val);
	template <typename ValType,typename OptType> int GetArg(QString strName, ValType & val);
public:
	QCmd*		m_pParent;
	QString		m_strStringListEnd;
	QChar		m_chOption;
	QString		m_strName;
	bool		m_bOptional;
	bool		m_bIgnoreCase;
	QString		m_strDescription;
	QString		m_strExplanation;
	QOptList	m_listOptions;
	QArgList	m_listArguments;
	QOptMap		m_mapOpt;
	QArgMap		m_mapArg;
};

/////////////////////////////////////////////////////////////////////////////////////////

QCmd::qtutilsPrivate::qtutilsPrivate(QCmd* pParent,QString strName,QString strDescription, 
									 QString strExplanation, bool bIgnoreCase) : 
									 m_pParent(pParent), m_strName(strName),
									 m_strDescription(strDescription),
									 m_strExplanation(strExplanation),
									 m_bIgnoreCase(bIgnoreCase)
{
	m_bOptional = false;

	m_chOption = '-';
	m_strStringListEnd = (".");
}

 /////////////////////////////////////////////////////////////////////////////////////////

 QCmd::qtutilsPrivate::~qtutilsPrivate()
 {
	 QCmdPart* ptr;
	 for(QArgList::iterator it = m_listArguments.begin(); it != m_listArguments.end();++it) {
		 ptr = *it;
		 delete ptr;
	 }

	 for (QOptList::iterator it = m_listOptions.begin(); it != m_listOptions.end();++it) {
		 ptr = *it;
		 delete ptr;
	 }

 }

 /////////////////////////////////////////////////////////////////////////////////////////

 bool QCmd::qtutilsPrivate::wasSuccessful( int nRetCode ) const
 {
	 return (nRetCode == QCmdParseError::STATUS_OK);
 }

/////////////////////////////////////////////////////////////////////////////////////////

template <typename ValType,typename OptType>
int QCmd::qtutilsPrivate::SetOpt(QString strName, ValType val)
{
	int retVal = (m_pParent != NULL) ? QCmdParseError::STATUS_OK : QCmdParseError::MEMORY_CORRUPTION_ERROR;
	QCmdOpt* pOption;
	if (retVal == QCmdParseError::STATUS_OK) {
		retVal = FindOpt(GetOptString(strName),pOption);
		if (m_pParent->wasSuccessful(retVal)) {
			if (pOption != NULL) {
				OptType* pOptType = dynamic_cast<OptType*>(pOption);
				if (pOptType != NULL) {
					pOptType->SetValue(val);
				}
			}
		}
	}
	return retVal;	
}

/////////////////////////////////////////////////////////////////////////////////////////

template <typename ValType,typename ArgType>
int QCmd::qtutilsPrivate::SetArg(QString strName, ValType val)
{
	int retVal = (m_pParent != NULL) ? QCmdParseError::STATUS_OK : QCmdParseError::MEMORY_CORRUPTION_ERROR;
	QCmdArg* pArgument;
	if (retVal == QCmdParseError::STATUS_OK) {
		retVal = FindArg(strName,pArgument);
		if (m_pParent->wasSuccessful(retVal)) {
			if (pArgument != NULL) {
				ArgType* pArgType = dynamic_cast<ArgType*>(pArgument);
				if (pArgType != NULL) {
					pArgType->SetValue(val);
				}
			}
		}
	}
	return retVal;	
}

/////////////////////////////////////////////////////////////////////////////////////////

template <typename ValType,typename OptType>
int QCmd::qtutilsPrivate::GetOpt( QString strName, ValType & val )
{
	int retVal = (m_pParent != NULL) ? QCmdParseError::STATUS_OK : QCmdParseError::MEMORY_CORRUPTION_ERROR;
	QCmdOpt* pOption = NULL;
	if (retVal == QCmdParseError::STATUS_OK) {
		QString strOpt = GetOptString(strName);
		retVal = FindOpt(strOpt,pOption);
		if ( m_pParent->wasSuccessful(retVal) ) {
			OptType* pOptType= dynamic_cast<OptType*>(pOption);
			if ( pOptType ) {
				val = pOptType->GetValue();
			}
			else
				retVal = QCmdParseError::OPTION_WRONG_TYPE;
		}	
	}
	QCmdParseException::Throw(retVal,strName,m_pParent->GetName());
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

template <typename ValType,typename ArgType>
int QCmd::qtutilsPrivate::GetArg( QString strName, ValType & val )
{
	int retVal = (m_pParent != NULL) ? QCmdParseError::STATUS_OK : QCmdParseError::MEMORY_CORRUPTION_ERROR;
	QCmdArg* pArgion = NULL;
	if (retVal == QCmdParseError::STATUS_OK) {
		QString strArg = strName;
		retVal = FindArg(strArg,pArgion);
		if ( m_pParent->wasSuccessful(retVal) ) {
			ArgType* pArgType= dynamic_cast<ArgType*>(pArgion);
			if ( pArgType ) {
				val = pArgType->GetValue();
			}
			else
				retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
		}	
	}
	QCmdParseException::Throw(retVal,strName,m_pParent->GetName());
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

template <typename ValType,typename OptType>
int QCmd::qtutilsPrivate::AddOpt( QString strName, 
				QString strDescription, QString strExplanation, 
				ValType nDefaultValue, ValType nMinVal, ValType nMaxVal )
{
	int retVal = (m_pParent != NULL) ? QCmdParseError::STATUS_OK : QCmdParseError::MEMORY_CORRUPTION_ERROR;
	if (retVal == QCmdParseError::STATUS_OK) {
		QString strOpt = GetOptString(strName);
		retVal = AddOpt( strOpt );
		if ( wasSuccessful(retVal) ) {
			OptType* ptr;
			ptr = new OptType(strOpt,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
			if ( ptr ) {
				retVal = AddOpt( strOpt, ptr );
			}
			else
			{
				retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
			}
		}
	}
	
	QCmdParseException::Throw(retVal,strName);
	return retVal;	
}

/////////////////////////////////////////////////////////////////////////////////////////

template <typename ValType,typename ArgType>
int QCmd::qtutilsPrivate::AddArg( QString strName, 
								 QString strDescription, QString strExplanation, 
								 ValType nDefaultValue, ValType nMinVal, ValType nMaxVal )
{
	int retVal = (m_pParent != NULL) ? QCmdParseError::STATUS_OK : QCmdParseError::MEMORY_CORRUPTION_ERROR;
	if (retVal == QCmdParseError::STATUS_OK) {
		retVal = AddArg( strName );
		if ( wasSuccessful(retVal) ) {
			ArgType* ptr;
			ptr = new ArgType(strName,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
			if ( ptr ) {
				retVal = AddArg( strName, ptr );
			}
			else
			{
				retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
			}
		}
	}

	QCmdParseException::Throw(retVal,strName);
	return retVal;	
}
/////////////////////////////////////////////////////////////////////////////////////////

void QCmd::qtutilsPrivate::Initialize()
{
	QCmdPart* ptr;
	m_bOptional = false;
	for(QArgList::iterator it = m_listArguments.begin(); it != m_listArguments.end();++it) {
		ptr = *it;
		ptr->Initialize();
	}

	for (QOptList::iterator it = m_listOptions.begin(); it != m_listOptions.end();++it) {
		ptr = *it;
		ptr->Initialize();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::qtutilsPrivate::AddOpt(QString strName, QCmdOpt* pOpt)
{
	QString strOpt = GetOptString(strName);
	int retVal = QCmdParseError::STATUS_OK;

	QOptMap::iterator it = m_mapOpt.find(strOpt);

	if ( it != m_mapOpt.end() ) {
		retVal = QCmdParseError::OPTION_ALLREADY_ADDED;
	}	
	else
		if ( pOpt != NULL ) {
			m_mapOpt.insert(strOpt,pOpt);
			m_listOptions.push_back(pOpt);
		}
		QCmdParseException::Throw(retVal,strName);
		return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmd::qtutilsPrivate::GetOptString( QString strName )
{

	if ( m_bIgnoreCase ) {
		return strName.toUpper();
	}
	else
		return strName;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::qtutilsPrivate::FindOpt(QString strName, QCmdOpt *& option)
{
	QString strOpt = GetOptString(strName);
	int retVal = QCmdParseError::OPTION_NOT_FOUND;

	QOptMap::iterator it = m_mapOpt.find(strOpt);
	if ( it != m_mapOpt.end() ) {
		option = *it;
		if ( option != NULL ) {
			retVal = QCmdParseError::STATUS_OK;
		}
		else
		{
			retVal = QCmdParseError::MEMORY_CORRUPTION_ERROR;
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::qtutilsPrivate::AddArg(QString strName, QCmdArg* pArg)
{
	int retVal = QCmdParseError::STATUS_OK;

	QArgMap::iterator it = m_mapArg.find(strName);
	if ( it != m_mapArg.end() ) {
		retVal = QCmdParseError::ARGUMENT_ALLREADY_ADDED;
	}	
	else
		if ( pArg != NULL ) {
			pArg->m_bOptional = m_bOptional;
			m_mapArg.insert(strName,pArg);
			m_listArguments.push_back(pArg);
		}
		QCmdParseException::Throw(retVal,strName);
		return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::qtutilsPrivate::FindArg(QString strName, QCmdArg *& ARGUMENT)
{

	int retVal = QCmdParseError::ARGUMENT_NOT_FOUND;
	QArgMap::iterator it = m_mapArg.find(strName);
	if ( it != m_mapArg.end() ) {
		ARGUMENT = *it;
		if ( ARGUMENT != NULL ) {
			retVal = QCmdParseError::STATUS_OK;
		}
		else
		{
			retVal = QCmdParseError::MEMORY_CORRUPTION_ERROR;
		}
	}	
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmd::qtutilsPrivate::GetSyntax()
{
	QString retVal;

	retVal = ("+") + GetName() + " ";

	QCmdOpt* pCmdOpt;
	QCmdArg* pCmdArg;

	for(QOptList::iterator it=m_listOptions.begin(); it != m_listOptions.end();++it) {
		pCmdOpt = *it;
		retVal += ("[-");
		if (!pCmdOpt->isExtendedOption()) {
			retVal += pCmdOpt->GetShortSyntax();
		}
		else
		{
			retVal += ("-");
			retVal += pCmdOpt->GetShortSyntax();
		}
		retVal += ("] ");
	}

	for(QArgList::iterator it=m_listArguments.begin(); it != m_listArguments.end();++it) {
		pCmdArg = *it;
		if ( pCmdArg->isOptional() ) {
			retVal += ("[");
			retVal += pCmdArg->GetShortSyntax();
			retVal += ("] ");
		}
		else
		{
			retVal += ("<") + pCmdArg->GetShortSyntax() + ("> ");
		}
	}

	retVal += ("\nDescription:\n  ") + GetDescription();

	if (!m_listArguments.isEmpty()) {
		retVal += ("\nArguments:\n");
		QString str;

		for(QArgList::iterator it=m_listArguments.begin(); it != m_listArguments.end();++it) {
			pCmdArg = *it;

			retVal += "  " + pCmdArg->GetName() + " -- " + pCmdArg->GetSyntax();
			retVal += ("\n");
			str = pCmdArg->GetExplanation();
			if ( !str.isEmpty() ) {
				retVal += ("  \t") + str + ("\n");
			}
		}
	}

	if (!m_listOptions.isEmpty()) {
		retVal += ("\nOptions:\n");
		QString str;
		for(QOptList::iterator it=m_listOptions.begin(); it != m_listOptions.end();++it) {
			pCmdOpt = *it;
			if(!pCmdOpt->isExtendedOption()) {
				str = QString("  -%1 -- ").arg(pCmdOpt->GetName());
			}
			else
			{
				str = QString("  --%1 -- ").arg(pCmdOpt->GetName());
			}

			retVal += str + pCmdOpt->GetSyntax();
			retVal += ("\n");
			str = pCmdOpt->GetExplanation();
			if ( !str.isEmpty() ) {
				retVal += ("  \t") + str + ("\n");
			}
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::qtutilsPrivate::Parse(QStringList & strLst)
{
	Initialize();

	QString str;

	int retVal = QCmdParseError::STATUS_OK;

	QCmdOpt* pOpt=NULL;
	QCmdArg* pArg=NULL;
	QCmdArg* pTest= NULL;

	QArgList::iterator itArg = m_listArguments.begin();
	for(QStringList::iterator it=strLst.begin(); it != strLst.end();++it) {
		str = *it;
		retVal = IsOption(str,pOpt);
		switch(retVal) {
		case QCmdParseError::STATUS_OK:
			retVal = pOpt->ImportData(str);
			pOpt = dynamic_cast<QCmdOptQStringList*>(pOpt);
			break;
		case QCmdParseError::PARAM_NOT_OPTION:
			if ( str.compare(m_strStringListEnd,Qt::CaseInsensitive) == 0 ) {
				pOpt = NULL;
				pArg = NULL;
				retVal = QCmdParseError::STATUS_OK;
				break;
			}
			if ( pOpt != NULL ) {
				pOpt = dynamic_cast<QCmdOptQStringList*>(pOpt);
				if ( pOpt != NULL ) {
					retVal = pOpt->ImportData(str);
					break;
				}
			}
			if ( pArg != NULL ) {
				pTest = dynamic_cast<QCmdArgQStringList*>(pArg);
				if ( pTest != NULL ) {
					pArg = pTest;
					retVal = pArg->ImportData(str);
					break;
				}
			}
			if ( pArg != NULL ) {
				pTest = dynamic_cast<QCmdArgFileList*>(pArg);
				if ( pTest != NULL ) {
					pArg = pTest;
					retVal = pArg->ImportData(str);
					break;
				}
			}
			if ( itArg != m_listArguments.end() ) {
				pArg = *itArg;
				itArg++;
				retVal = pArg->ImportData(str);
			}
			else
				retVal = QCmdParseError::TOO_MANY_ARGUMENTS;
			break;
		}
		if ( retVal != QCmdParseError::STATUS_OK ) {
			break;
		}

	}
	if ( itArg != m_listArguments.end() ) {
		pArg = *itArg;
		itArg++;
		if ( !pArg->isOptional() ) {
			retVal = QCmdParseError::NOT_ENOUGH_ARGUMENTS;
		}
	}

	QCmdParseException::Throw(retVal," while parsing ",strLst, str);
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::qtutilsPrivate::IsOption(QString & str, QCmdOpt *& pOption)
{
	int retVal = QCmdParseError::PARAM_NOT_OPTION;
	if ( str.length() > 1 ) {
		if ( str[0] == '-' ) {
			if (str[1] != '-') {
				if ( !str[1].isDigit() ) {
					QString strName = str[1];
					retVal = FindOpt(GetOptString(strName),pOption);
					if ( wasSuccessful(retVal) ) {
						str = QString( str.mid(2) );
					}
				}
			}
			else
			{
				QStringList strLst = str.mid(2).split("=");
				if (!strLst.isEmpty()) {
					QString strName = strLst.front();
					strLst.pop_front();
					retVal = FindOpt(GetOptString(strName),pOption);
					if ( wasSuccessful(retVal) ) {
						if (!strLst.isEmpty()) {
							str = strLst.front();
						}
						else
						{
							str = QString();
						}

					}
				}
				else
					retVal = QCmdParseError::PARAM_NOT_OPTION;

			}
		}
	}
	return retVal;
}


/////////////////////////////////////////////////////////////////////////////////////////

QString QCmd::qtutilsPrivate::GetName()
{
	return m_strName;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmd::qtutilsPrivate::GetDescription()
{
	return m_strDescription;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmd::qtutilsPrivate::GetExplanation()
{
	return m_strExplanation;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::qtutilsPrivate::Parse()
{
	int retVal;
	QCmdOpt* pOpt;

	QStringList::iterator it = m_pParent->m_strLstCmd.begin();
	QString str;
	for(; it != m_pParent->m_strLstCmd.end();++it) {
		str = *it;
		if ( IsOption(str,pOpt) == QCmdParseError::STATUS_OK ) {
			if (pOpt->GetName() == "?") {
				QCmdHelpException::Throw(GetSyntax());
			}
		}
	}
	retVal = Parse(m_pParent->m_strLstCmd);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmd::qtutilsPrivate::exportCommandString(QChar chCommand)
{
	QString retVal = chCommand + GetName()+ " ";

	QArgList::iterator it = m_listArguments.begin();
	for(; it != m_listArguments.end();++it) {
		QCmdArg* pArg = *it;
		QString strExport = pArg->exportCommandString();
		if (!strExport.isEmpty()) {
			retVal += strExport + " ";
		}
	}

	QOptList::iterator itOpt = m_listOptions.begin();
	for(; itOpt != m_listOptions.end();++itOpt) {
		QCmdOpt* pOpt = *itOpt;
		QString strExport = pOpt->exportCommandString();
		if (!strExport.isEmpty()) {
			retVal += strExport + " ";
		}
	}

	return retVal;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

QCmd::QCmd(QString strName,QString strDescription, QString strExplanation,bool bIgnoreCase) 
{
	m_pPrivate = new qtutilsPrivate(this,strName,strDescription,strExplanation,bIgnoreCase);
	if (m_pPrivate != NULL) {
		AddOpt(QChar('?'),QString("Help"),QString("This option shows the help for this command."),
			(bool)false);
	}	
}
/////////////////////////////////////////////////////////////////////////////////////////

QCmd::QCmd( const QCmd & other )
{
	m_pPrivate = new qtutilsPrivate(this,QString(),QString());
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

QCmd::~QCmd()
{
	delete m_pPrivate;
}

/////////////////////////////////////////////////////////////////////////////////////////

void QCmd::Initialize()
{
	m_pPrivate->Initialize();
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddOpt(QString strName, QString strDescription, QString strExplanation, bool bDefaultValue)
{
	QString strOpt = m_pPrivate->GetOptString(strName);
	int retVal = m_pPrivate->AddOpt( strOpt );
	if ( wasSuccessful(retVal) ) {
		QCmdOptBool* ptr;
		ptr = new QCmdOptBool(strOpt,strDescription,strExplanation,bDefaultValue);
		if ( ptr ) {
			retVal = m_pPrivate->AddOpt( strOpt, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddOpt(QString strName, QString strDescription, QString strExplanation, quint32 nDefaultValue,
				 quint32 nMinVal, quint32 nMaxVal)
{
	return m_pPrivate->AddOpt<quint32,QCmdOpt_quint32>(strName,strDescription,
		strExplanation,nDefaultValue,nMinVal,nMaxVal);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddOpt(QString strName, QString strDescription, QString strExplanation, int nDefaultValue,
				 int nMinVal, int nMaxVal)
{
	return m_pPrivate->AddOpt<int,QCmdOpt_int>(strName,strDescription,
		strExplanation,nDefaultValue,nMinVal,nMaxVal);
}

int QCmd::AddOpt(QString strName, QString strDescription, QString strExplanation, quint8 nDefaultValue,
				 quint8 nMinVal, quint8 nMaxVal)
{
	return m_pPrivate->AddOpt<quint8,QCmdOpt_quint8>(strName,strDescription,
		strExplanation,nDefaultValue,nMinVal,nMaxVal);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddOpt(QString strName, QString strDescription, QString strExplanation, quint16 nDefaultValue,
				 quint16 nMinVal, quint16 nMaxVal)
{
	return m_pPrivate->AddOpt<quint16,QCmdOpt_quint16>(strName,strDescription,
		strExplanation,nDefaultValue,nMinVal,nMaxVal);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddOpt(QString strName, QString strDescription, QString strExplanation, short nDefaultValue,
				 short nMinVal, short nMaxVal)
{
	return m_pPrivate->AddOpt<short,QCmdOpt_short>(strName,strDescription,
		strExplanation,nDefaultValue,nMinVal,nMaxVal);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddOpt(QString strName, QString strDescription, QString strExplanation, float nDefaultValue,
				 float nMinVal, float nMaxVal)
{
	return m_pPrivate->AddOpt<float,QCmdOpt_float>(strName,strDescription,
		strExplanation,nDefaultValue,nMinVal,nMaxVal);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddOpt(QString strName, QString strDescription, QString strExplanation, double nDefaultValue,
				 double nMinVal, double nMaxVal)
{
	return m_pPrivate->AddOpt<double,QCmdOpt_double>(strName,strDescription,
		strExplanation,nDefaultValue,nMinVal,nMaxVal);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddOpt(QString strName, QString strDescription, QString strExplanation, bool bIgnoreCase, 
				 QChar chDefaultValue, QChar chMinVal, QChar chMaxVal)
{
	QString strOpt = m_pPrivate->GetOptString(strName);
	int retVal = m_pPrivate->AddOpt( strOpt );
	if ( wasSuccessful(retVal) ) {
		QCmdOptQChar* ptr;
		ptr = new QCmdOptQChar(strOpt,strDescription,strExplanation,bIgnoreCase,
			chDefaultValue,chMinVal,chMaxVal);
		if ( ptr ) {
			retVal = m_pPrivate->AddOpt( strOpt, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddOpt(QString strName, QString strDescription, QString strExplanation, QString  strDefaultValue, 
				 CMDSTRVERIFY pFnVerify)
{
	QString strOpt = m_pPrivate->GetOptString(strName);
	int retVal = m_pPrivate->AddOpt( strOpt );
	if ( wasSuccessful(retVal) ) {
		QCmdOptQString* ptr;
		ptr = new QCmdOptQString(strOpt,strDescription,strExplanation,strDefaultValue,
			pFnVerify);
		if ( ptr ) {
			retVal = m_pPrivate->AddOpt( strOpt, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddOpt(QString strName, QString strDescription, QString strExplanation, const QStringList & strLstDefaultValue, 
				 CMDSTRVERIFY pFnVerify)
{
	QString strOpt = m_pPrivate->GetOptString(strName);
	int retVal = m_pPrivate->AddOpt( strOpt );
	if ( wasSuccessful(retVal) ) {
		QCmdOptQStringList* ptr;
		ptr = new QCmdOptQStringList(strOpt,strDescription,strExplanation,strLstDefaultValue,
			pFnVerify);
		if ( ptr ) {
			retVal = m_pPrivate->AddOpt( strOpt, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, bool & bValue)
{
	return m_pPrivate->GetOpt<bool,QCmdOptBool>(strName,bValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, quint32 & nValue)
{
	return m_pPrivate->GetOpt<quint32,QCmdOpt_quint32>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, int & nValue)
{
	return m_pPrivate->GetOpt<int,QCmdOpt_int>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, quint8 & nValue)
{
	return m_pPrivate->GetOpt<quint8,QCmdOpt_quint8>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, short & nValue)
{
	return m_pPrivate->GetOpt<short,QCmdOpt_short>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, quint16 & nValue)
{
	return m_pPrivate->GetOpt<quint16,QCmdOpt_quint16>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, float & nValue)
{
	return m_pPrivate->GetOpt<float,QCmdOpt_float>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, double & nValue)
{
	return m_pPrivate->GetOpt<double,QCmdOpt_double>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, QChar & chValue)
{
	return m_pPrivate->GetOpt<QChar,QCmdOptQChar>(strName,chValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, QString & nValue)
{
	return m_pPrivate->GetOpt<QString,QCmdOptQString>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, QStringList & nValue)
{
	return m_pPrivate->GetOpt<QStringList,QCmdOptQStringList>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, bool bDefaultValue)
{
	
	int retVal = m_pPrivate->AddArg( strName );
	if ( wasSuccessful(retVal) ) {
		QCmdArgBool* ptr;
		ptr = new QCmdArgBool(strName,strDescription,strExplanation,bDefaultValue);
		if ( ptr ) {
			retVal = m_pPrivate->AddArg( strName, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, quint32 nDefaultValue,
				 quint32 nMinVal, quint32 nMaxVal)
{
	return m_pPrivate->AddArg<quint32,QCmdArg_quint32>(strName,strDescription,
		strExplanation,nDefaultValue,nMinVal,nMaxVal);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, int nDefaultValue,
				 int nMinVal, int nMaxVal)
{
	return m_pPrivate->AddArg<int,QCmdArg_int>(strName,strDescription,
		strExplanation,nDefaultValue,nMinVal,nMaxVal);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, quint8 nDefaultValue,
				 quint8 nMinVal, quint8 nMaxVal)
{
	return m_pPrivate->AddArg<quint8,QCmdArg_quint8>(strName,strDescription,
		strExplanation,nDefaultValue,nMinVal,nMaxVal);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, quint16 nDefaultValue,
				 quint16 nMinVal, quint16 nMaxVal)
{
	return m_pPrivate->AddArg<quint16,QCmdArg_quint16>(strName,strDescription,
		strExplanation,nDefaultValue,nMinVal,nMaxVal);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, short nDefaultValue,
				 short nMinVal, short nMaxVal)
{
	return m_pPrivate->AddArg<short,QCmdArg_short>(strName,strDescription,
		strExplanation,nDefaultValue,nMinVal,nMaxVal);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, float nDefaultValue,
				 float nMinVal, float nMaxVal)
{
	return m_pPrivate->AddArg<float,QCmdArg_float>(strName,strDescription,
		strExplanation,nDefaultValue,nMinVal,nMaxVal);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, double nDefaultValue,
				 double nMinVal, double nMaxVal)
{
	return m_pPrivate->AddArg<double,QCmdArg_double>(strName,strDescription,
		strExplanation,nDefaultValue,nMinVal,nMaxVal);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, bool bIgnoreCase, 
				 QChar  chDefaultValue, QChar  chMinVal, QChar  chMaxVal)
{
	
	int retVal = m_pPrivate->AddArg( strName );
	if ( wasSuccessful(retVal) ) {
		QCmdArgQChar* ptr;
		ptr = new QCmdArgQChar(strName,strDescription,strExplanation,bIgnoreCase,
			chDefaultValue,chMinVal,chMaxVal);
		if ( ptr ) {
			retVal = m_pPrivate->AddArg( strName, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, QString  strDefaultValue, 
				 CMDSTRVERIFY pFnVerify)
{
	
	int retVal = m_pPrivate->AddArg( strName );
	if ( wasSuccessful(retVal) ) {
		QCmdArgQString* ptr;
		ptr = new QCmdArgQString(strName,strDescription,strExplanation,strDefaultValue,
			pFnVerify);
		if ( ptr ) {
			retVal = m_pPrivate->AddArg( strName, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, const QStringList &  strLstDefaultValue, 
				 CMDSTRVERIFY pFnVerify)
{
	
	int retVal = m_pPrivate->AddArg( strName );
	if ( wasSuccessful(retVal) ) {
		QCmdArgQStringList* ptr;
		ptr = new QCmdArgQStringList(strName,strDescription,strExplanation,strLstDefaultValue,
			pFnVerify);
		if ( ptr ) {
			retVal = m_pPrivate->AddArg( strName, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, const QCmdLineFileList &  strLstDefaultValue, 
				 CMDSTRVERIFY pFnVerify)
{
	
	int retVal = m_pPrivate->AddArg( strName );
	if ( wasSuccessful(retVal) ) {
		QCmdArgFileList* ptr;
		ptr = new QCmdArgFileList(strName,strDescription,strExplanation,strLstDefaultValue,
			pFnVerify);
		if ( ptr ) {
			retVal = m_pPrivate->AddArg( strName, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, bool & bValue)
{
	return m_pPrivate->GetArg<bool,QCmdArgBool>(strName,bValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, quint32 & nValue)
{
	return m_pPrivate->GetArg<quint32,QCmdArg_quint32>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, int & nValue)
{
	return m_pPrivate->GetArg<int,QCmdArg_int>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, quint8 & nValue)
{
	return m_pPrivate->GetArg<quint8,QCmdArg_quint8>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, short & nValue)
{
	return m_pPrivate->GetArg<short,QCmdArg_short>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, quint16 & nValue)
{
	return m_pPrivate->GetArg<quint16,QCmdArg_quint16>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, float & nValue)
{
	return m_pPrivate->GetArg<float,QCmdArg_float>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, double & nValue)
{
	return m_pPrivate->GetArg<double,QCmdArg_double>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, QChar & chValue)
{
	return m_pPrivate->GetArg<QChar,QCmdArgQChar>(strName,chValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, QString & nValue)
{
	return m_pPrivate->GetArg<QString,QCmdArgQString>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, QStringList & nValue)
{
	return m_pPrivate->GetArg<QStringList,QCmdArgQStringList>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::Execute()
{
	return QCmdParseError::STATUS_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::Parse( QStringList & strLst )
{
	int retVal = (m_pPrivate != NULL) ? QCmdParseError::STATUS_OK : QCmdParseError::MEMORY_ALLOCATION_ERROR;
	if (wasSuccessful(retVal)) {
		m_pPrivate->Parse(strLst);
	}
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::Parse()
{
	int retVal = (m_pPrivate != NULL) ? QCmdParseError::STATUS_OK : QCmdParseError::MEMORY_ALLOCATION_ERROR;
	if (wasSuccessful(retVal)) {
		m_pPrivate->Parse();
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, bool bValue )
{
	return m_pPrivate->SetOpt<bool,QCmdOptBool>(strName,bValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, quint32 nValue )
{
	return m_pPrivate->SetOpt<quint32,QCmdOpt_quint32>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, int nValue )
{
	return m_pPrivate->SetOpt<int,QCmdOpt_int>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, quint8 nValue )
{
	return m_pPrivate->SetOpt<quint8,QCmdOpt_quint8>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, quint16 nValue )
{
	return m_pPrivate->SetOpt<quint16,QCmdOpt_quint16>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, short nValue )
{
	return m_pPrivate->SetOpt<short,QCmdOpt_short>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, float nValue )
{
	return m_pPrivate->SetOpt<float,QCmdOpt_float>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, double nValue )
{
	return m_pPrivate->SetOpt<double,QCmdOpt_double>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, QChar chValue )
{
	return m_pPrivate->SetOpt<QChar,QCmdOptQChar>(strName,chValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, QString nValue )
{
	return m_pPrivate->SetOpt<QString,QCmdOptQString>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, QStringList nValue )
{
	return m_pPrivate->SetOpt<QStringList,QCmdOptQStringList>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, QCmdLineFileList nValue )
{
	/*
	QCmdOpt* pOption;
	int retVal = FindOpt(GetOptString(strName),pOption);
	if (wasSuccessful(retVal)) {
		if (pOption != NULL) {
			QCmdLineFileList* pIntOpt = dynamic_cast<QCmdLineFileList*>(pOption);
			if (pIntOpt != NULL) {
				pIntOpt->SetValue(nValue);
			}
		}
	}
	*/

	return QCmdParseError::NOT_IMPLEMENTED;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetArg( QString strName, bool bValue )
{
	return m_pPrivate->SetArg<bool,QCmdArgBool>(strName,bValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetArg( QString strName, quint32 nValue )
{
	return m_pPrivate->SetArg<quint32,QCmdArg_quint32>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetArg( QString strName, int nValue )
{
	return m_pPrivate->SetArg<int,QCmdArg_int>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetArg( QString strName, quint8 nValue )
{
	return m_pPrivate->SetArg<quint8,QCmdArg_quint8>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetArg( QString strName, quint16 nValue )
{
	return m_pPrivate->SetArg<quint16,QCmdArg_quint16>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetArg( QString strName, short nValue )
{
	return m_pPrivate->SetArg<short,QCmdArg_short>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetArg( QString strName, float nValue )
{
	return m_pPrivate->SetArg<float,QCmdArg_float>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetArg( QString strName, double nValue )
{
	return m_pPrivate->SetArg<double,QCmdArg_double>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetArg( QString strName, QChar chValue )
{
	return m_pPrivate->SetArg<QChar,QCmdArgQChar>(strName,chValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetArg( QString strName, QString nValue )
{
	return m_pPrivate->SetArg<QString,QCmdArgQString>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetArg( QString strName, QStringList nValue )
{
	return m_pPrivate->SetArg<QStringList,QCmdArgQStringList>(strName,nValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetArg( QString strName, QCmdLineFileList nValue )
{
	nValue.m_strListFiles.clear();
	QCmdArg* pArg=NULL;
	int retVal = m_pPrivate->FindArg(strName,pArg);
	if ( wasSuccessful(retVal) ) {
		QCmdArgFileList* pArgQString = dynamic_cast<QCmdArgFileList*>(pArg);
		if ( pArgQString ) {
			pArgQString->SetValue(nValue);
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, QCmdLineFileList & nValue)
{
	nValue.m_strListFiles.clear();
	QCmdArg* pArg=NULL;
	int retVal = m_pPrivate->FindArg(strName,pArg);
	if ( wasSuccessful(retVal) ) {
		QCmdArgFileList* pArgQString = dynamic_cast<QCmdArgFileList*>(pArg);
		if ( pArgQString ) {
			pArgQString->GetValue().CopyTo(nValue);
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool QCmd::wasSuccessful( int nRetCode ) const
{
	return (nRetCode == QCmdParseError::STATUS_OK);
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmd::GetName()
{
	QString retVal;
	if (m_pPrivate != NULL) {
		retVal = m_pPrivate->GetName();
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmd::GetDescription()
{
	QString retVal;
	if (m_pPrivate != NULL) {
		retVal = m_pPrivate->GetDescription();
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void QCmd::EndRequiredArguments()
{
	m_pPrivate->m_bOptional = true;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmd::GetSyntax()
{
	QString retVal;
	if (m_pPrivate != NULL) {
		retVal = m_pPrivate->GetSyntax();
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmd::exportCommandString(QChar chCommand)
{
	QString retVal;
	if (m_pPrivate != NULL) {
		retVal = m_pPrivate->exportCommandString(chCommand);
	}
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

QOptList QCmd::getOptions(bool bDuplicate) const
{
	QOptList retVal;
	if (!bDuplicate) {
		retVal = m_pPrivate->m_listOptions;
	}
	else
	{	
		QOptList lstOldOpts = m_pPrivate->m_listOptions;
		foreach(QCmdOpt* pOpt,lstOldOpts) {
			if (pOpt != NULL) {
				QCmdOpt* pClone = dynamic_cast<QCmdOpt*>(pOpt->Clone());
				if (pClone) {
					retVal.push_back(pClone);
				}
			}
		}
	}
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

QTUTILS::QArgList QCmd::getArguments(bool bDuplicate) const
{
	QArgList retVal;
	if (!bDuplicate) {
		retVal = m_pPrivate->m_listArguments;
	}
	else
	{	
		QArgList lstOldArgs = m_pPrivate->m_listArguments;
		foreach(QCmdArg* pArg,lstOldArgs) {
			if (pArg != NULL) {
				QCmdArg* pClone = dynamic_cast<QCmdArg*>(pArg->Clone());
				if (pClone) {
					retVal.push_back(pClone);
				}
			}
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////


QCmd* QCmd::Clone()
{
	QCmd* retVal = NULL;
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QCmd* QCmd::New()
{
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////

void QCmd::setOptions( QOptList & lstOptions )
{
	m_pPrivate->m_listOptions = lstOptions;
}
/////////////////////////////////////////////////////////////////////////////////////////

void QCmd::setArguments( QArgList & lstArguments )
{
	m_pPrivate->m_listArguments = lstArguments;
}
/////////////////////////////////////////////////////////////////////////////////////////

void QCmd::copy( const QCmd & other )
{
	m_pPrivate->m_strName = other.m_pPrivate->m_strName;
	m_pPrivate->m_strExplanation = other.m_pPrivate->m_strExplanation;
	m_pPrivate->m_strDescription = other.m_pPrivate->m_strDescription;
	m_pPrivate->m_chOption = other.m_pPrivate->m_chOption;
	m_pPrivate->m_bOptional = other.m_pPrivate->m_bOptional;
	m_pPrivate->m_bIgnoreCase = other.m_pPrivate->m_bIgnoreCase;
		
	setArguments(other.getArguments(true));
	setOptions(other.getOptions(true));
}
/////////////////////////////////////////////////////////////////////////////////////////

void QCmd::destroy()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

}; //namespace QTUTILS
