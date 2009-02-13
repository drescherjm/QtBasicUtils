/////////////////////////////////////////////////////////////////////////////////////////

#include "QCmd.h"

namespace QTUTILS {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

QCmd::QCmd(QString strName,QString strDescription, QString strExplanation,bool bIgnoreCase) : 
m_strName(strName), m_strDescription(strDescription), m_strExplanation(strExplanation), m_bIgnoreCase(bIgnoreCase)
{
	m_chOption = '-';
	m_strStringListEnd = _T(".");
	m_bOptional = false;
	AddOpt('?',"Help","This option shows the help for this command.",false);
}

QCmd::~QCmd()
{
	POSITION pos; 
	QCmdPart* ptr;
	pos = m_listArguments.GetHeadPosition();
	while( pos ) {
		ptr = m_listArguments.GetNext(pos);
		delete ptr;
	}
	pos = m_listOptions.GetHeadPosition();
	while( pos ) {
		ptr = m_listOptions.GetNext(pos);
		delete ptr;
	}
}

void QCmd::Initialize()
{
	POSITION pos; 
	QCmdPart* ptr;
	m_bOptional = false;
	pos = m_listArguments.GetHeadPosition();
	while( pos ) {
		ptr = m_listArguments.GetNext(pos);
		ptr->Initialize();
	}
	pos = m_listOptions.GetHeadPosition();
	while( pos ) {
		ptr = m_listOptions.GetNext(pos);
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
		QCmdOptUINT* ptr;
		ptr = new QCmdOptUINT(chOpt,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
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
		QCmdOptquint8* ptr;
		ptr = new QCmdOptquint8(chOpt,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
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
		QCmdOptquint16* ptr;
		ptr = new QCmdOptquint16(chOpt,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
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
		QCmdOptCString* ptr;
		ptr = new QCmdOptCString(chOpt,strDescription,strExplanation,strDefaultValue,
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

int QCmd::AddOpt(QChar ch, QString strDescription, QString strExplanation, const CStringList & strLstDefaultValue, 
				 CMDSTRVERIFY pFnVerify)
{
	QChar chOpt = GetOptChar(ch);
	int retVal = AddOpt( chOpt );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOptCStringList* ptr;
		ptr = new QCmdOptCStringList(chOpt,strDescription,strExplanation,strLstDefaultValue,
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
		QCmdOptUINT* pOptUINT = dynamic_cast<QCmdOptUINT*>(pOpt);
		if ( pOptUINT ) {
			nValue = pOptUINT->GetValue();
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
		QCmdOptint* pOptUINT = dynamic_cast<QCmdOptint*>(pOpt);
		if ( pOptUINT ) {
			nValue = pOptUINT->GetValue();
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
		QCmdOptquint8* pOptquint8 = dynamic_cast<QCmdOptquint8*>(pOpt);
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
		QCmdOptquint16* pOptquint16 = dynamic_cast<QCmdOptquint16*>(pOpt);
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
		QCmdOptCString* pOptCString = dynamic_cast<QCmdOptCString*>(pOpt);
		if ( pOptCString ) {
			nValue = pOptCString->GetValue();
		}
		else
			retVal = QCmdParseError::OPTION_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal,ch,GetName());
	return retVal;
}

int QCmd::GetOpt(QChar ch, CStringList & nValue)
{
	QChar chOpt = GetOptChar(ch);
	nValue.RemoveAll();
	QCmdOpt* pOpt=NULL;
	int retVal = FindOpt(chOpt,pOpt);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdOptCStringList* pOptCStringList = dynamic_cast<QCmdOptCStringList*>(pOpt);
		if ( pOptCStringList ) {
			pOptCStringList->GetValue().CopyTo(nValue);
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
		QCmdArgUINT* ptr;
		ptr = new QCmdArgUINT(strName,strDescription,strExplanation,nDefaultValue,nMinVal,nMaxVal);
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
		QCmdArgCString* ptr;
		ptr = new QCmdArgCString(strName,strDescription,strExplanation,strDefaultValue,
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

int QCmd::AddArg(QString strName, QString strDescription, QString strExplanation, const CStringList &  strLstDefaultValue, 
				 CMDSTRVERIFY pFnVerify)
{
	
	int retVal = AddArg( strName );
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgCStringList* ptr;
		ptr = new QCmdArgCStringList(strName,strDescription,strExplanation,strLstDefaultValue,
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
		QCmdArgUINT* pArgUINT = dynamic_cast<QCmdArgUINT*>(pArg);
		if ( pArgUINT ) {
			nValue = pArgUINT->GetValue();
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
		QCmdArgint* pArgUINT = dynamic_cast<QCmdArgint*>(pArg);
		if ( pArgUINT ) {
			nValue = pArgUINT->GetValue();
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
		QCmdArgCString* pArgCString = dynamic_cast<QCmdArgCString*>(pArg);
		if ( pArgCString ) {
			nValue = pArgCString->GetValue();
		}
		else
			retVal = QCmdParseError::ARGUMENT_WRONG_TYPE;
	}
	QCmdParseException::Throw(retVal);
	return retVal;
}

int QCmd::GetArg(QString strName, CStringList & nValue)
{
	nValue.RemoveAll();
	QCmdArg* pArg=NULL;
	int retVal = FindArg(strName,pArg);
	if ( retVal == QCmdParseError::STATUS_OK ) {
		QCmdArgCStringList* pArgCString = dynamic_cast<QCmdArgCStringList*>(pArg);
		if ( pArgCString ) {
			pArgCString->GetValue().CopyTo(nValue);
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
		QCmdArgFileList* pArgCString = dynamic_cast<QCmdArgFileList*>(pArg);
		if ( pArgCString ) {
			pArgCString->GetValue().CopyTo(nValue);
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
		retVal += _T("[-");
		retVal += pCmdOpt->GetShortSyntax();
		retVal += _T("] ");
	}
	
	pos = m_listArguments.GetHeadPosition();
	while( pos ) {
		pCmdArg = m_listArguments.GetNext(pos);
		if ( pCmdArg->GetOptional() ) {
			retVal += _T("[");
			retVal += pCmdArg->GetShortSyntax();
			retVal += _T("] ");
		}
		else
		{
			retVal += _T("<") + pCmdArg->GetShortSyntax() + _T("> ");
		}
	}
	
	
	retVal += _T("\nDescription:\n  ") + GetDescription();
	
	retVal += _T("\nArguments:\n");
	QString str;

	pos = m_listArguments.GetHeadPosition();
	while( pos ) {
		pCmdArg = m_listArguments.GetNext(pos);
		str.Format("  %s -- ",pCmdArg->GetName());
		retVal += str + pCmdArg->GetSyntax();
		retVal += _T("\n");
		str = pCmdArg->GetExplanation();
		if ( !str.IsEmpty() ) {
			retVal += _T("  \t") + str + _T("\n");
		}
	}
	retVal += _T("\nOptions:\n");
	
	pos = m_listOptions.GetHeadPosition();
	while( pos ) {
		pCmdOpt = m_listOptions.GetNext(pos);
		str.Format("  %c -- ",pCmdOpt->GetName());
		retVal += str + pCmdOpt->GetSyntax();
		retVal += _T("\n");
		str = pCmdOpt->GetExplanation();
		if ( !str.IsEmpty() ) {
			retVal += _T("  \t") + str + _T("\n");
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
