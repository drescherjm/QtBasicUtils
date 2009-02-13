/////////////////////////////////////////////////////////////////////////////////////////

#include "QCmd.h"
#include "QCmdArg.h"
#include "QCmdOpt.h"
#include "QCmdParseError.h"
#include "QCmdOptBool.h"
#include "QCmdParseException.h"
#include "QCmdOptBasic.h"

namespace QTUTILS {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

QCmd::QCmd(QString strName,QString strDescription, QString strExplanation,bool bIgnoreCase) : 
m_strName(strName), m_strDescription(strDescription), m_strExplanation(strExplanation), m_bIgnoreCase(bIgnoreCase)
{
	m_chOption = '-';
	m_strStringListEnd = (".");
	m_bOptional = false;
	AddOpt(QChar('?'),QString("Help"),QString("This option shows the help for this command."),(bool)false);
}

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
}

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

int QCmd::AddOpt(QChar ch, QString strDescription, QString strExplanation, bool bDefaultValue)
{
	QChar chOpt = GetOptChar(ch);
	int retVal = AddOpt( chOpt );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOptBool* ptr;
		ptr = new QCmdOptBool(chOpt,strDescription,strExplanation,bDefaultValue);
		if ( ptr ) {
			retVal = AddOpt( chOpt, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,ch);
	return retVal;
}

int QCmd::AddOpt(QChar ch, QString strDescription, QString strExplanation, quint32 nDefaultValue,
				 quint32 nMinVal, quint32 nMaxVal)
{
	QChar chOpt = GetOptChar(ch);
	int retVal = AddOpt( chOpt );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOpt_quint32* ptr;
		ptr = new QCmdOpt_quint32(chOpt,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddOpt( chOpt, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,ch);
	return retVal;
}

int QCmd::AddOpt(QChar ch, QString strDescription, QString strExplanation, int nDefaultValue,
				 int nMinVal, int nMaxVal)
{
	QChar chOpt = GetOptChar(ch);
	int retVal = AddOpt( chOpt );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOptint* ptr;
		ptr = new QCmdOptint(chOpt,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddOpt( chOpt, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,ch);
	return retVal;
}

int QCmd::AddOpt(QChar ch, QString strDescription, QString strExplanation, quint8 nDefaultValue,
				 quint8 nMinVal, quint8 nMaxVal)
{
	QChar chOpt = GetOptChar(ch);
	int retVal = AddOpt( chOpt );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOpt_quint8* ptr;
		ptr = new QCmdOpt_quint8(chOpt,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddOpt( chOpt, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,ch);
	return retVal;
}


int QCmd::AddOpt(QChar ch, QString strDescription, QString strExplanation, quint16 nDefaultValue,
				 quint16 nMinVal, quint16 nMaxVal)
{
	QChar chOpt = GetOptChar(ch);
	int retVal = AddOpt( chOpt );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOpt_quint16* ptr;
		ptr = new QCmdOpt_quint16(chOpt,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddOpt( chOpt, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,ch);
	return retVal;
}

int QCmd::AddOpt(QChar ch, QString strDescription, QString strExplanation, short nDefaultValue,
				 short nMinVal, short nMaxVal)
{
	QChar chOpt = GetOptChar(ch);
	int retVal = AddOpt( chOpt );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOptshort* ptr;
		ptr = new QCmdOptshort(chOpt,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddOpt( chOpt, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,ch);
	return retVal;
}



int QCmd::AddOpt(QChar ch, QString strDescription, QString strExplanation, float nDefaultValue,
				 float nMinVal, float nMaxVal)
{
	QChar chOpt = GetOptChar(ch);
	int retVal = AddOpt( chOpt );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOptfloat* ptr;
		ptr = new QCmdOptfloat(chOpt,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddOpt( chOpt, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,ch);
	return retVal;
}

int QCmd::AddOpt(QChar ch, QString strDescription, QString strExplanation, double nDefaultValue,
				 double nMinVal, double nMaxVal)
{
	QChar chOpt = GetOptChar(ch);
	int retVal = AddOpt( chOpt );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOptdouble* ptr;
		ptr = new QCmdOptdouble(chOpt,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddOpt( chOpt, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,ch);
	return retVal;
}

int QCmd::AddOpt(QChar ch, QString strDescription, QString strExplanation, bool bIgnoreCase, 
				 QChar chDefaultValue, QChar chMinVal, QChar chMaxVal)
{
	QChar chOpt = GetOptChar(ch);
	int retVal = AddOpt( chOpt );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOptQChar* ptr;
		ptr = new QCmdOptQChar(chOpt,strDescription,strExplanation,bIgnoreCase,
			chDefaultValue,chMinVal,chMaxVal);
		if ( ptr ) {
			retVal = AddOpt( chOpt, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,ch);
	return retVal;
}

int QCmd::AddOpt(QChar ch, QString strDescription, QString strExplanation, QString  strDefaultValue, 
				 CMDSTRVERIFY pFnVerify)
{
	QChar chOpt = GetOptChar(ch);
	int retVal = AddOpt( chOpt );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOptQString* ptr;
		ptr = new QCmdOptQString(chOpt,strDescription,strExplanation,strDefaultValue,
			pFnVerify);
		if ( ptr ) {
			retVal = AddOpt( chOpt, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,ch);
	return retVal;
}

int QCmd::AddOpt(QChar ch, QString strDescription, QString strExplanation, const QStringList & strLstDefaultValue, 
				 CMDSTRVERIFY pFnVerify)
{
	QChar chOpt = GetOptChar(ch);
	int retVal = AddOpt( chOpt );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOptQStringList* ptr;
		ptr = new QCmdOptQStringList(chOpt,strDescription,strExplanation,strLstDefaultValue,
			pFnVerify);
		if ( ptr ) {
			retVal = AddOpt( chOpt, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal,ch);
	return retVal;
}

int QCmd::AddOpt(QChar ch, QCmdOpt* pOpt)
{
	QChar chOpt = GetOptChar(ch);
	int retVal = QCmdParseError::STATUS_OK;
	if ( m_mapOpt.Lookup(chOpt,pOpt) ) {
		retVal = QCmdParseError::OPTION_ALLREADY_ADDED;
	}	
	else
		if ( pOpt != NULL ) {
			m_mapOpt.SetAt(chOpt,pOpt);
			m_listOptions.AddTail(pOpt);
		}
		QCmdParseException::Throw(retVal,ch);
		return retVal;
}

int QCmd::FindOpt(QChar ch, QCmdOpt *& option)
{
	QChar chOpt = GetOptChar(ch);
	int retVal = QCmdParseError::OPTION_NOT_FOUND;
	if ( m_mapOpt.Lookup(chOpt,option) ) {
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

int QCmd::GetOpt(QChar ch, bool & bValue)
{
	QChar chOpt = GetOptChar(ch);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(chOpt,pOpt);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOptBool* pOptBool = dynamic_cast<QCmdOptBool*>(pOpt);
		if ( pOptBool ) {
			bValue = pOptBool->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,ch,GetName());
	return retVal;
}

int QCmd::GetOpt(QChar ch, quint32 & nValue)
{
	QChar chOpt = GetOptChar(ch);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(chOpt,pOpt);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOpt_quint32* pOptquint32 = dynamic_cast<QCmdOpt_quint32*>(pOpt);
		if ( pOptquint32 ) {
			nValue = pOptquint32->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,ch,GetName());
	return retVal;
}

int QCmd::GetOpt(QChar ch, int & nValue)
{
	QChar chOpt = GetOptChar(ch);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(chOpt,pOpt);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOptint* pOptquint32 = dynamic_cast<QCmdOptint*>(pOpt);
		if ( pOptquint32 ) {
			nValue = pOptquint32->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,ch,GetName());
	return retVal;
}

int QCmd::GetOpt(QChar ch, quint8 & nValue)
{
	QChar chOpt = GetOptChar(ch);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(chOpt,pOpt);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOpt_quint8* pOptquint8 = dynamic_cast<QCmdOpt_quint8*>(pOpt);
		if ( pOptquint8 ) {
			nValue = pOptquint8->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,ch,GetName());
	return retVal;
}

int QCmd::GetOpt(QChar ch, short & nValue)
{
	QChar chOpt = GetOptChar(ch);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(chOpt,pOpt);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOptshort* pOptshort = dynamic_cast<QCmdOptshort*>(pOpt);
		if ( pOptshort ) {
			nValue = pOptshort->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,ch,GetName());
	return retVal;
}



int QCmd::GetOpt(QChar ch, quint16 & nValue)
{
	QChar chOpt = GetOptChar(ch);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(chOpt,pOpt);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOpt_quint16* pOptquint16 = dynamic_cast<QCmdOpt_quint16*>(pOpt);
		if ( pOptquint16 ) {
			nValue = pOptquint16->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,ch,GetName());
	return retVal;
}

int QCmd::GetOpt(QChar ch, float & nValue)
{
	QChar chOpt = GetOptChar(ch);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(chOpt,pOpt);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOptfloat* pOptfloat = dynamic_cast<QCmdOptfloat*>(pOpt);
		if ( pOptfloat ) {
			nValue = pOptfloat->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,ch,GetName());
	return retVal;
}

int QCmd::GetOpt(QChar ch, double & nValue)
{
	QChar chOpt = GetOptChar(ch);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(chOpt,pOpt);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOptdouble* pOptdouble = dynamic_cast<QCmdOptdouble*>(pOpt);
		if ( pOptdouble ) {
			nValue = pOptdouble->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,ch,GetName());
	return retVal;
}

int QCmd::GetOpt(QChar ch, QChar & chValue)
{
	QChar chOpt = GetOptChar(ch);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(chOpt,pOpt);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOptQChar* pOptQChar = dynamic_cast<QCmdOptQChar*>(pOpt);
		if ( pOptQChar ) {
			chValue = pOptQChar->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,ch,GetName());
	return retVal;
}

int QCmd::GetOpt(QChar ch, QString & nValue)
{
	QChar chOpt = GetOptChar(ch);
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(chOpt,pOpt);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOptQString* pOptQString = dynamic_cast<QCmdOptQString*>(pOpt);
		if ( pOptQString ) {
			nValue = pOptQString->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,ch,GetName());
	return retVal;
}

int QCmd::GetOpt(QChar ch, QStringList & nValue)
{
	QChar chOpt = GetOptChar(ch);
	nValue.RemoveAll();
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(chOpt,pOpt);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOptQStringList* pOptQStringList = dynamic_cast<QCmdOptQStringList*>(pOpt);
		if ( pOptQStringList ) {
			pOptQStringList->GetValue().CopyTo(nValue);
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,ch,GetName());
	return retVal;
}

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, bool bDefaultValue)
{
	
	int retVal = AddArg( strName );
	if ( retVal == QCmdParseError::STATUS_OK ) {
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
	QCmdParseException::Throw(retVal);
	return retVal;
}

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, quint32 nDefaultValue,
				 quint32 nMinVal, quint32 nMaxVal)
{
	
	int retVal = AddArg( strName );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgquint32* ptr;
		ptr = new QCmdArgquint32(strName,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddArg( strName, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal);
	return retVal;
}

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, int nDefaultValue,
				 int nMinVal, int nMaxVal)
{
	
	int retVal = AddArg( strName );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgint* ptr;
		ptr = new QCmdArgint(strName,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddArg( strName, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal);
	return retVal;
}

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, quint8 nDefaultValue,
				 quint8 nMinVal, quint8 nMaxVal)
{
	
	int retVal = AddArg( strName );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgquint8* ptr;
		ptr = new QCmdArgquint8(strName,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddArg( strName, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal);
	return retVal;
}


int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, quint16 nDefaultValue,
				 quint16 nMinVal, quint16 nMaxVal)
{
	
	int retVal = AddArg( strName );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgquint16* ptr;
		ptr = new QCmdArgquint16(strName,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddArg( strName, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal);
	return retVal;
}

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, short nDefaultValue,
				 short nMinVal, short nMaxVal)
{
	
	int retVal = AddArg( strName );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgshort* ptr;
		ptr = new QCmdArgshort(strName,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddArg( strName, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal);
	return retVal;
}



int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, float nDefaultValue,
				 float nMinVal, float nMaxVal)
{
	
	int retVal = AddArg( strName );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgfloat* ptr;
		ptr = new QCmdArgfloat(strName,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddArg( strName, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal);
	return retVal;
}

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, double nDefaultValue,
				 double nMinVal, double nMaxVal)
{
	
	int retVal = AddArg( strName );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgdouble* ptr;
		ptr = new QCmdArgdouble(strName,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
		if ( ptr ) {
			retVal = AddArg( strName, ptr );
		}
		else
		{
			retVal =  QCmdParseError::MEMORY_ALLOCATION_ERROR;
		}
	}
	QCmdParseException::Throw(retVal);
	return retVal;
}

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, bool bIgnoreCase, 
				 QChar  chDefaultValue, QChar  chMinVal, QChar  chMaxVal)
{
	
	int retVal = AddArg( strName );
	if ( retVal == QCmdParseError::STATUS_OK ) {
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
	QCmdParseException::Throw(retVal);
	return retVal;
}

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, QString  strDefaultValue, 
				 CMDSTRVERIFY pFnVerify)
{
	
	int retVal = AddArg( strName );
	if ( retVal == QCmdParseError::STATUS_OK ) {
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
	QCmdParseException::Throw(retVal);
	return retVal;
}

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, const QStringList &  strLstDefaultValue, 
				 CMDSTRVERIFY pFnVerify)
{
	
	int retVal = AddArg( strName );
	if ( retVal == QCmdParseError::STATUS_OK ) {
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
	QCmdParseException::Throw(retVal);
	return retVal;
}

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, const QCmdLineFileList &  strLstDefaultValue, 
				 CMDSTRVERIFY pFnVerify)
{
	
	int retVal = AddArg( strName );
	if ( retVal == QCmdParseError::STATUS_OK ) {
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
	QCmdParseException::Throw(retVal);
	return retVal;
}


int QCmd::AddArg(QString strName, QCmdArg* pArg)
{
	
	int retVal = QCmdParseError::STATUS_OK;
	if ( m_mapArg.Lookup(strName,pArg) ) {
		retVal = QCmdParseError::ARGUMENT_ALLREADY_ADDED;
	}	
	else
		if ( pArg != NULL ) {
			pArg->m_bOptional = m_bOptional;
			m_mapArg.SetAt(strName,pArg);
			m_listArguments.AddTail(pArg);
		}
		QCmdParseException::Throw(retVal);
		return retVal;
}

int QCmd::FindArg(QString strName, QCmdArg *& ARGUMENT)
{
	
	int retVal = QCmdParseError::ARGUMENT_NOT_FOUND;
	if ( m_mapArg.Lookup(strName,ARGUMENT) ) {
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
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgBool* pArgBool = dynamic_cast<QCmdArgBool*>(pArg);
		if ( pArgBool ) {
			bValue = pArgBool->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal);
	return retVal;
}

int QCmd::GetArg(QString strName, quint32 & nValue)
{
	
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgquint32* pArgquint32 = dynamic_cast<QCmdArgquint32*>(pArg);
		if ( pArgquint32 ) {
			nValue = pArgquint32->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal);
	return retVal;
}

int QCmd::GetArg(QString strName, int & nValue)
{
	
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgint* pArgquint32 = dynamic_cast<QCmdArgint*>(pArg);
		if ( pArgquint32 ) {
			nValue = pArgquint32->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal);
	return retVal;
}

int QCmd::GetArg(QString strName, quint8 & nValue)
{
	
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgquint8* pArgquint8 = dynamic_cast<QCmdArgquint8*>(pArg);
		if ( pArgquint8 ) {
			nValue = pArgquint8->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal);
	return retVal;
}

int QCmd::GetArg(QString strName, short & nValue)
{
	
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgshort* pArgshort = dynamic_cast<QCmdArgshort*>(pArg);
		if ( pArgshort ) {
			nValue = pArgshort->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal);
	return retVal;
}



int QCmd::GetArg(QString strName, quint16 & nValue)
{
	
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgquint16* pArgquint16 = dynamic_cast<QCmdArgquint16*>(pArg);
		if ( pArgquint16 ) {
			nValue = pArgquint16->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	return retVal;
}

int QCmd::GetArg(QString strName, float & nValue)
{
	
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgfloat* pArgfloat = dynamic_cast<QCmdArgfloat*>(pArg);
		if ( pArgfloat ) {
			nValue = pArgfloat->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	return retVal;
}

int QCmd::GetArg(QString strName, double & nValue)
{
	
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgdouble* pArgdouble = dynamic_cast<QCmdArgdouble*>(pArg);
		if ( pArgdouble ) {
			nValue = pArgdouble->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal);
	return retVal;
}

int QCmd::GetArg(QString strName, QString & nValue)
{
	
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgQString* pArgQString = dynamic_cast<QCmdArgQString*>(pArg);
		if ( pArgQString ) {
			nValue = pArgQString->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal);
	return retVal;
}

int QCmd::GetArg(QString strName, QStringList & nValue)
{
	nValue.RemoveAll();
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgQStringList* pArgQString = dynamic_cast<QCmdArgQStringList*>(pArg);
		if ( pArgQString ) {
			pArgQString->GetValue().CopyTo(nValue);
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal);
	return retVal;
}

int QCmd::GetArg(QString strName, QCmdLineFileList & nValue)
{
	nValue.m_strListFiles.RemoveAll();
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgFileList* pArgQString = dynamic_cast<QCmdArgFileList*>(pArg);
		if ( pArgQString ) {
			pArgQString->GetValue().CopyTo(nValue);
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal);
	return retVal;
}

int QCmd::GetArg(QString strName, QChar & chValue)
{
	
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgQChar* pArgQChar = dynamic_cast<QCmdArgQChar*>(pArg);
		if ( pArgQChar ) {
			chValue = pArgQChar->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal);
	return retVal;
}

QString QCmd::GetSyntax()
{
	QString retVal;
	retVal.Format("+%s ",GetName());
	POSITION pos; 
	QCmdOpt* pCmdOpt;
	QCmdArg* pCmdArg;
	
	pos = m_listOptions.GetHeadPosition();
	while( pos ) {
		pCmdOpt = m_listOptions.GetNext(pos);
		retVal += ("[-");
		retVal += pCmdOpt->GetShortSyntax();
		retVal += ("] ");
	}
	
	pos = m_listArguments.GetHeadPosition();
	while( pos ) {
		pCmdArg = m_listArguments.GetNext(pos);
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
	
	retVal += ("\nArguments:\n");
	QString str;

	pos = m_listArguments.GetHeadPosition();
	while( pos ) {
		pCmdArg = m_listArguments.GetNext(pos);
		str.Format("  %s -- ",pCmdArg->GetName());
		retVal += str + pCmdArg->GetSyntax();
		retVal += ("\n");
		str = pCmdArg->GetExplanation();
		if ( !str.IsEmpty() ) {
			retVal += ("  \t") + str + ("\n");
		}
	}
	retVal += ("\nOptions:\n");
	
	pos = m_listOptions.GetHeadPosition();
	while( pos ) {
		pCmdOpt = m_listOptions.GetNext(pos);
		str.Format("  %c -- ",pCmdOpt->GetName());
		retVal += str + pCmdOpt->GetSyntax();
		retVal += ("\n");
		str = pCmdOpt->GetExplanation();
		if ( !str.IsEmpty() ) {
			retVal += ("  \t") + str + ("\n");
		}
	}
	return retVal;
}

QChar QCmd::GetOptChar(QChar ch)
{
	if ( m_bIgnoreCase ) {
		return _totupper(ch);
	}
	else
		return ch;
}

}; //namespace QTUTILS
