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
	qtutilsPrivate(QCmd* pParent);
public:
	template <typename ValType,typename OptType> int SetOpt(QString strName, ValType);
public:
	QCmd*		m_pParent;
	QString		m_strStringListEnd;
	QChar		m_chOption;
};

QCmd::qtutilsPrivate::qtutilsPrivate(QCmd* pParent) : m_pParent(pParent)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

template <typename ValType,typename OptType>
int QCmd::qtutilsPrivate::SetOpt(QString strName, ValType val)
{
	QCmdOpt* pOption;
	int retVal = FindOpt(GetOptString(strName),pOption);
	if (wasSuccessful(retVal)) {
		if (pOption != NULL) {
			OptType* pOptType = dynamic_cast<OptType*>(pOption);
			if (pOptType != NULL) {
				pOptType->SetValue(val);
			}
		}
	}
	return retVal;	
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

QCmd::QCmd(QString strName,QString strDescription, QString strExplanation,bool bIgnoreCase) : 
m_strName(strName), m_strDescription(strDescription), m_strExplanation(strExplanation), m_bIgnoreCase(bIgnoreCase)
{
	m_pPrivate = new qtutilsPrivate(this);
	if (m_pPrivate != NULL) {
		m_pPrivate->m_chOption = '-';
		m_pPrivate->m_strStringListEnd = (".");
		m_bOptional = false;
		AddOpt(QChar('?'),QString("Help"),QString("This option shows the help for this command."),(bool)false);
	}	
}

/////////////////////////////////////////////////////////////////////////////////////////

QCmd::~QCmd()
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

	delete m_pPrivate;
}

/////////////////////////////////////////////////////////////////////////////////////////

void QCmd::Initialize()
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

int QCmd::AddOpt(QString strName, QString strDescription, QString strExplanation, bool bDefaultValue)
{
	QString strOpt = GetOptString(strName);
	int retVal = AddOpt( strOpt );
	if ( wasSuccessful(retVal) ) {
		QCmdOptBool* ptr;
		ptr = new QCmdOptBool(strOpt,strDescription,strExplanation,bDefaultValue);
		if ( ptr ) {
			retVal = AddOpt( strOpt, ptr );
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
	QString strOpt = GetOptString(strName);
	int retVal = AddOpt( strOpt );
	if ( wasSuccessful(retVal) ) {
		QCmdOpt_quint32* ptr;
		ptr = new QCmdOpt_quint32(strOpt,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddOpt( strOpt, ptr );
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

int QCmd::AddOpt(QString strName, QString strDescription, QString strExplanation, int nDefaultValue,
				 int nMinVal, int nMaxVal)
{
	QString strOpt = GetOptString(strName);
	int retVal = AddOpt( strOpt );
	if ( wasSuccessful(retVal) ) {
		QCmdOpt_int* ptr;
		ptr = new QCmdOpt_int(strOpt,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddOpt( strOpt, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

int QCmd::AddOpt(QString strName, QString strDescription, QString strExplanation, quint8 nDefaultValue,
				 quint8 nMinVal, quint8 nMaxVal)
{
	QString strOpt = GetOptString(strName);
	int retVal = AddOpt( strOpt );
	if ( wasSuccessful(retVal) ) {
		QCmdOpt_quint8* ptr;
		ptr = new QCmdOpt_quint8(strOpt,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddOpt( strOpt, ptr );
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

int QCmd::AddOpt(QString strName, QString strDescription, QString strExplanation, quint16 nDefaultValue,
				 quint16 nMinVal, quint16 nMaxVal)
{
	QString strOpt = GetOptString(strName);
	int retVal = AddOpt( strOpt );
	if ( wasSuccessful(retVal) ) {
		QCmdOpt_quint16* ptr;
		ptr = new QCmdOpt_quint16(strOpt,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddOpt( strOpt, ptr );
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

int QCmd::AddOpt(QString strName, QString strDescription, QString strExplanation, short nDefaultValue,
				 short nMinVal, short nMaxVal)
{
	QString strOpt = GetOptString(strName);
	int retVal = AddOpt( strOpt );
	if ( wasSuccessful(retVal) ) {
		QCmdOpt_short* ptr;
		ptr = new QCmdOpt_short(strOpt,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddOpt( strOpt, ptr );
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

int QCmd::AddOpt(QString strName, QString strDescription, QString strExplanation, float nDefaultValue,
				 float nMinVal, float nMaxVal)
{
	QString strOpt = GetOptString(strName);
	int retVal = AddOpt( strOpt );
	if ( wasSuccessful(retVal) ) {
		QCmdOpt_float* ptr;
		ptr = new QCmdOpt_float(strOpt,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddOpt( strOpt, ptr );
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

int QCmd::AddOpt(QString strName, QString strDescription, QString strExplanation, double nDefaultValue,
				 double nMinVal, double nMaxVal)
{
	QString strOpt = GetOptString(strName);
	int retVal = AddOpt( strOpt );
	if ( wasSuccessful(retVal) ) {
		QCmdOpt_double* ptr;
		ptr = new QCmdOpt_double(strOpt,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddOpt( strOpt, ptr );
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

int QCmd::AddOpt(QString strName, QString strDescription, QString strExplanation, bool bIgnoreCase, 
				 QChar chDefaultValue, QChar chMinVal, QChar chMaxVal)
{
	QString strOpt = GetOptString(strName);
	int retVal = AddOpt( strOpt );
	if ( wasSuccessful(retVal) ) {
		QCmdOptQChar* ptr;
		ptr = new QCmdOptQChar(strOpt,strDescription,strExplanation,bIgnoreCase,
			chDefaultValue,chMinVal,chMaxVal);
		if ( ptr ) {
			retVal = AddOpt( strOpt, ptr );
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
	QString strOpt = GetOptString(strName);
	int retVal = AddOpt( strOpt );
	if ( wasSuccessful(retVal) ) {
		QCmdOptQString* ptr;
		ptr = new QCmdOptQString(strOpt,strDescription,strExplanation,strDefaultValue,
			pFnVerify);
		if ( ptr ) {
			retVal = AddOpt( strOpt, ptr );
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
	QString strOpt = GetOptString(strName);
	int retVal = AddOpt( strOpt );
	if ( wasSuccessful(retVal) ) {
		QCmdOptQStringList* ptr;
		ptr = new QCmdOptQStringList(strOpt,strDescription,strExplanation,strLstDefaultValue,
			pFnVerify);
		if ( ptr ) {
			retVal = AddOpt( strOpt, ptr );
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

int QCmd::AddOpt(QString strName, QCmdOpt* pOpt)
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

int QCmd::FindOpt(QString strName, QCmdOpt *& option)
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

int QCmd::GetOpt(QString strName, bool & bValue)
{
	QString strOpt = GetOptString(strName);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(strOpt,pOpt);
	if ( wasSuccessful(retVal) ) {
		QCmdOptBool* pOptBool = dynamic_cast<QCmdOptBool*>(pOpt);
		if ( pOptBool ) {
			bValue = pOptBool->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName,GetName());
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, quint32 & nValue)
{
	QString strOpt = GetOptString(strName);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(strOpt,pOpt);
	if ( wasSuccessful(retVal) ) {
		QCmdOpt_quint32* pOptquint32 = dynamic_cast<QCmdOpt_quint32*>(pOpt);
		if ( pOptquint32 ) {
			nValue = pOptquint32->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName,GetName());
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, int & nValue)
{
	QString strOpt = GetOptString(strName);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(strOpt,pOpt);
	if ( wasSuccessful(retVal) ) {
		QCmdOpt_int* pOptquint32 = dynamic_cast<QCmdOpt_int*>(pOpt);
		if ( pOptquint32 ) {
			nValue = pOptquint32->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName,GetName());
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, quint8 & nValue)
{
	QString strOpt = GetOptString(strName);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(strOpt,pOpt);
	if ( wasSuccessful(retVal) ) {
		QCmdOpt_quint8* pOptquint8 = dynamic_cast<QCmdOpt_quint8*>(pOpt);
		if ( pOptquint8 ) {
			nValue = pOptquint8->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName,GetName());
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, short & nValue)
{
	QString strOpt = GetOptString(strName);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(strOpt,pOpt);
	if ( wasSuccessful(retVal) ) {
		QCmdOpt_short* pOptshort = dynamic_cast<QCmdOpt_short*>(pOpt);
		if ( pOptshort ) {
			nValue = pOptshort->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName,GetName());
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, quint16 & nValue)
{
	QString strOpt = GetOptString(strName);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(strOpt,pOpt);
	if ( wasSuccessful(retVal) ) {
		QCmdOpt_quint16* pOptquint16 = dynamic_cast<QCmdOpt_quint16*>(pOpt);
		if ( pOptquint16 ) {
			nValue = pOptquint16->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName,GetName());
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, float & nValue)
{
	QString strOpt = GetOptString(strName);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(strOpt,pOpt);
	if ( wasSuccessful(retVal) ) {
		QCmdOpt_float* pOptfloat = dynamic_cast<QCmdOpt_float*>(pOpt);
		if ( pOptfloat ) {
			nValue = pOptfloat->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName,GetName());
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, double & nValue)
{
	QString strOpt = GetOptString(strName);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(strOpt,pOpt);
	if ( wasSuccessful(retVal) ) {
		QCmdOpt_double* pOptdouble = dynamic_cast<QCmdOpt_double*>(pOpt);
		if ( pOptdouble ) {
			nValue = pOptdouble->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName,GetName());
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, QChar & chValue)
{
	QString strOpt = GetOptString(strName);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(strOpt,pOpt);
	if ( wasSuccessful(retVal) ) {
		QCmdOptQChar* pOptQChar = dynamic_cast<QCmdOptQChar*>(pOpt);
		if ( pOptQChar ) {
			chValue = pOptQChar->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName,GetName());
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, QString & nValue)
{
	QString strOpt = GetOptString(strName);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(strOpt,pOpt);
	if ( wasSuccessful(retVal) ) {
		QCmdOptQString* pOptQString = dynamic_cast<QCmdOptQString*>(pOpt);
		if ( pOptQString ) {
			nValue = pOptQString->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName,GetName());
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetOpt(QString strName, QStringList & nValue)
{
	QString strOpt = GetOptString(strName);
	nValue.clear();
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(strOpt,pOpt);
	if ( wasSuccessful(retVal) ) {
		QCmdOptQStringList* pOptQStringList = dynamic_cast<QCmdOptQStringList*>(pOpt);
		if ( pOptQStringList ) {
			nValue = pOptQStringList->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName,GetName());
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, bool bDefaultValue)
{
	
	int retVal = AddArg( strName );
	if ( wasSuccessful(retVal) ) {
		QCmdArgBool* ptr;
		ptr = new QCmdArgBool(strName,strDescription,strExplanation,bDefaultValue);
		if ( ptr ) {
			retVal = AddArg( strName, ptr );
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
	
	int retVal = AddArg( strName );
	if ( wasSuccessful(retVal) ) {
		QCmdArg_quint32* ptr;
		ptr = new QCmdArg_quint32(strName,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddArg( strName, ptr );
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

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, int nDefaultValue,
				 int nMinVal, int nMaxVal)
{
	
	int retVal = AddArg( strName );
	if ( wasSuccessful(retVal) ) {
		QCmdArg_int* ptr;
		ptr = new QCmdArg_int(strName,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddArg( strName, ptr );
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

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, quint8 nDefaultValue,
				 quint8 nMinVal, quint8 nMaxVal)
{
	
	int retVal = AddArg( strName );
	if ( wasSuccessful(retVal) ) {
		QCmdArg_quint8* ptr;
		ptr = new QCmdArg_quint8(strName,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddArg( strName, ptr );
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

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, quint16 nDefaultValue,
				 quint16 nMinVal, quint16 nMaxVal)
{
	
	int retVal = AddArg( strName );
	if ( wasSuccessful(retVal) ) {
		QCmdArg_quint16* ptr;
		ptr = new QCmdArg_quint16(strName,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddArg( strName, ptr );
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

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, short nDefaultValue,
				 short nMinVal, short nMaxVal)
{
	
	int retVal = AddArg( strName );
	if ( wasSuccessful(retVal) ) {
		QCmdArg_short* ptr;
		ptr = new QCmdArg_short(strName,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddArg( strName, ptr );
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

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, float nDefaultValue,
				 float nMinVal, float nMaxVal)
{
	
	int retVal = AddArg( strName );
	if ( wasSuccessful(retVal) ) {
		QCmdArg_float* ptr;
		ptr = new QCmdArg_float(strName,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddArg( strName, ptr );
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

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, double nDefaultValue,
				 double nMinVal, double nMaxVal)
{
	
	int retVal = AddArg( strName );
	if ( wasSuccessful(retVal) ) {
		QCmdArg_double* ptr;
		ptr = new QCmdArg_double(strName,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddArg( strName, ptr );
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

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, bool bIgnoreCase, 
				 QChar  chDefaultValue, QChar  chMinVal, QChar  chMaxVal)
{
	
	int retVal = AddArg( strName );
	if ( wasSuccessful(retVal) ) {
		QCmdArgQChar* ptr;
		ptr = new QCmdArgQChar(strName,strDescription,strExplanation,bIgnoreCase,
			chDefaultValue,chMinVal,chMaxVal);
		if ( ptr ) {
			retVal = AddArg( strName, ptr );
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
	
	int retVal = AddArg( strName );
	if ( wasSuccessful(retVal) ) {
		QCmdArgQString* ptr;
		ptr = new QCmdArgQString(strName,strDescription,strExplanation,strDefaultValue,
			pFnVerify);
		if ( ptr ) {
			retVal = AddArg( strName, ptr );
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
	
	int retVal = AddArg( strName );
	if ( wasSuccessful(retVal) ) {
		QCmdArgQStringList* ptr;
		ptr = new QCmdArgQStringList(strName,strDescription,strExplanation,strLstDefaultValue,
			pFnVerify);
		if ( ptr ) {
			retVal = AddArg( strName, ptr );
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
	
	int retVal = AddArg( strName );
	if ( wasSuccessful(retVal) ) {
		QCmdArgFileList* ptr;
		ptr = new QCmdArgFileList(strName,strDescription,strExplanation,strLstDefaultValue,
			pFnVerify);
		if ( ptr ) {
			retVal = AddArg( strName, ptr );
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

int QCmd::AddArg(QString strName, QCmdArg* pArg)
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

int QCmd::FindArg(QString strName, QCmdArg *& ARGUMENT)
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

int QCmd::GetArg(QString strName, bool & bValue)
{
	
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( wasSuccessful(retVal) ) {
		QCmdArgBool* pArgBool = dynamic_cast<QCmdArgBool*>(pArg);
		if ( pArgBool ) {
			bValue = pArgBool->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, quint32 & nValue)
{
	
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( wasSuccessful(retVal) ) {
		QCmdArg_quint32* pArgquint32 = dynamic_cast<QCmdArg_quint32*>(pArg);
		if ( pArgquint32 ) {
			nValue = pArgquint32->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

int QCmd::GetArg(QString strName, int & nValue)
{
	
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( wasSuccessful(retVal) ) {
		QCmdArg_int* pArgquint32 = dynamic_cast<QCmdArg_int*>(pArg);
		if ( pArgquint32 ) {
			nValue = pArgquint32->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, quint8 & nValue)
{
	
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( wasSuccessful(retVal) ) {
		QCmdArg_quint8* pArgquint8 = dynamic_cast<QCmdArg_quint8*>(pArg);
		if ( pArgquint8 ) {
			nValue = pArgquint8->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, short & nValue)
{
	
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( wasSuccessful(retVal) ) {
		QCmdArg_short* pArgshort = dynamic_cast<QCmdArg_short*>(pArg);
		if ( pArgshort ) {
			nValue = pArgshort->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, quint16 & nValue)
{
	
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( wasSuccessful(retVal) ) {
		QCmdArg_quint16* pArgquint16 = dynamic_cast<QCmdArg_quint16*>(pArg);
		if ( pArgquint16 ) {
			nValue = pArgquint16->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, float & nValue)
{
	
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( wasSuccessful(retVal) ) {
		QCmdArg_float* pArgfloat = dynamic_cast<QCmdArg_float*>(pArg);
		if ( pArgfloat ) {
			nValue = pArgfloat->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, double & nValue)
{
	
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( wasSuccessful(retVal) ) {
		QCmdArg_double* pArgdouble = dynamic_cast<QCmdArg_double*>(pArg);
		if ( pArgdouble ) {
			nValue = pArgdouble->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, QString & nValue)
{
	
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( wasSuccessful(retVal) ) {
		QCmdArgQString* pArgQString = dynamic_cast<QCmdArgQString*>(pArg);
		if ( pArgQString ) {
			nValue = pArgQString->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::GetArg(QString strName, QStringList & nValue)
{
	nValue.clear();
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( wasSuccessful(retVal) ) {
		QCmdArgQStringList* pArgQString = dynamic_cast<QCmdArgQStringList*>(pArg);
		if ( pArgQString ) {
			nValue =pArgQString->GetValue();
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
	int retVal = FindArg(strName,pArg);
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

int QCmd::GetArg(QString strName, QChar & chValue)
{
	
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( wasSuccessful(retVal) ) {
		QCmdArgQChar* pArgQChar = dynamic_cast<QCmdArgQChar*>(pArg);
		if ( pArgQChar ) {
			chValue = pArgQChar->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmd::GetSyntax()
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
		if ( pCmdArg->GetOptional() ) {
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

QString QCmd::GetOptString( QString strName )
{

	if ( m_bIgnoreCase ) {
		return strName.toUpper();
	}
	else
		return strName;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::Execute()
{
	return QCmdParseError::STATUS_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::Parse()
{
	int retVal;
	QCmdOpt* pOpt;

	QStringList::iterator it = m_strLstCmd.begin();
	QString str;
	for(; it != m_strLstCmd.end();++it) {
		str = *it;
		if ( IsOption(str,pOpt) == QCmdParseError::STATUS_OK ) {
			if (pOpt->GetName() == "?") {
				QCmdHelpException::Throw(GetSyntax());
			}
		}
	}
	retVal = Parse(m_strLstCmd);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::Parse(QStringList & strLst)
{
	Initialize();
	
	QString str;

	int retVal = (m_pPrivate != NULL) ? QCmdParseError::STATUS_OK : QCmdParseError::MEMORY_ALLOCATION_ERROR;
	if (wasSuccessful(retVal)) {
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
			if ( str.compare(m_pPrivate->m_strStringListEnd,Qt::CaseInsensitive) == 0 ) {
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
			if ( !pArg->GetOptional() ) {
				retVal = QCmdParseError::NOT_ENOUGH_ARGUMENTS;
			}
		}
	}
	QCmdParseException::Throw(retVal," while parsing ",strLst, str);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::IsOption(QString & str, QCmdOpt *& pOption)
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

int QCmd::SetOpt( QString strName, bool bValue )
{
	QCmdOpt* pOption;
	int retVal = FindOpt(GetOptString(strName),pOption);
	if (wasSuccessful(retVal)) {
		if (pOption != NULL) {
			QCmdOptBool* pBoolOpt = dynamic_cast<QCmdOptBool*>(pOption);
			if (pBoolOpt != NULL) {
				pBoolOpt->SetValue(bValue);
			}
		}
	}
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, quint32 nValue )
{
	QCmdOpt* pOption;
	int retVal = FindOpt(GetOptString(strName),pOption);
	if (wasSuccessful(retVal)) {
		if (pOption != NULL) {
			QCmdOpt_quint32* pIntOpt = dynamic_cast<QCmdOpt_quint32*>(pOption);
			if (pIntOpt != NULL) {
				pIntOpt->SetValue(nValue);
			}
		}
	}
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, int nValue )
{
	QCmdOpt* pOption;
	int retVal = FindOpt(GetOptString(strName),pOption);
	if (wasSuccessful(retVal)) {
		if (pOption != NULL) {
			QCmdOpt_int* pIntOpt = dynamic_cast<QCmdOpt_int*>(pOption);
			if (pIntOpt != NULL) {
				pIntOpt->SetValue(nValue);
			}
		}
	}
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, quint8 nValue )
{
	QCmdOpt* pOption;
	int retVal = FindOpt(GetOptString(strName),pOption);
	if (wasSuccessful(retVal)) {
		if (pOption != NULL) {
			QCmdOpt_quint8* pIntOpt = dynamic_cast<QCmdOpt_quint8*>(pOption);
			if (pIntOpt != NULL) {
				pIntOpt->SetValue(nValue);
			}
		}
	}
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, quint16 nValue )
{
	QCmdOpt* pOption;
	int retVal = FindOpt(GetOptString(strName),pOption);
	if (wasSuccessful(retVal)) {
		if (pOption != NULL) {
			QCmdOpt_quint16* pIntOpt = dynamic_cast<QCmdOpt_quint16*>(pOption);
			if (pIntOpt != NULL) {
				pIntOpt->SetValue(nValue);
			}
		}
	}
	return retVal;	
}
/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, short nValue )
{
	QCmdOpt* pOption;
	int retVal = FindOpt(GetOptString(strName),pOption);
	if (wasSuccessful(retVal)) {
		if (pOption != NULL) {
			QCmdOpt_short* pIntOpt = dynamic_cast<QCmdOpt_short*>(pOption);
			if (pIntOpt != NULL) {
				pIntOpt->SetValue(nValue);
			}
		}
	}
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, float nValue )
{
	QCmdOpt* pOption;
	int retVal = FindOpt(GetOptString(strName),pOption);
	if (wasSuccessful(retVal)) {
		if (pOption != NULL) {
			QCmdOpt_float* pIntOpt = dynamic_cast<QCmdOpt_float*>(pOption);
			if (pIntOpt != NULL) {
				pIntOpt->SetValue(nValue);
			}
		}
	}
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, double nValue )
{
	QCmdOpt* pOption;
	int retVal = FindOpt(GetOptString(strName),pOption);
	if (wasSuccessful(retVal)) {
		if (pOption != NULL) {
			QCmdOpt_double* pIntOpt = dynamic_cast<QCmdOpt_double*>(pOption);
			if (pIntOpt != NULL) {
				pIntOpt->SetValue(nValue);
			}
		}
	}
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, QChar chValue )
{
	/*
	QCmdOpt* pOption;
	int retVal = FindOpt(GetOptString(strName),pOption);
	if (wasSuccessful(retVal)) {
		if (pOption != NULL) {
			QCmdOptQChar* pIntOpt = dynamic_cast<QCmdOptQChar*>(pOption);
			if (pIntOpt != NULL) {
				pIntOpt->SetValue(chValue);
			}
		}
	}
	return retVal;
	*/

	return m_pPrivate->SetOpt<QChar,QCmdOptQChar>(strName,chValue);
}
/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, QString nValue )
{
	QCmdOpt* pOption;
	int retVal = FindOpt(GetOptString(strName),pOption);
	if (wasSuccessful(retVal)) {
		if (pOption != NULL) {
			QCmdOptQString* pIntOpt = dynamic_cast<QCmdOptQString*>(pOption);
			if (pIntOpt != NULL) {
				pIntOpt->SetValue(nValue);
			}
		}
	}
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, QStringList nValue )
{
	QCmdOpt* pOption;
	int retVal = FindOpt(GetOptString(strName),pOption);
	if (wasSuccessful(retVal)) {
		if (pOption != NULL) {
			QCmdOptQStringList* pIntOpt = dynamic_cast<QCmdOptQStringList*>(pOption);
			if (pIntOpt != NULL) {
				pIntOpt->SetValue(nValue);
			}
		}
	}
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

int QCmd::SetOpt( QString strName, QCmdLineFileList nValue )
{
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
}

/////////////////////////////////////////////////////////////////////////////////////////

bool QCmd::wasSuccessful( int nRetCode ) const
{
	return (nRetCode == QCmdParseError::STATUS_OK);
}

/////////////////////////////////////////////////////////////////////////////////////////

}; //namespace QTUTILS
