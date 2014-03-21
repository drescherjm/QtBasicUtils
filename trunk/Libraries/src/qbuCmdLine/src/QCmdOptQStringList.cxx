#include "qbuCmdLine/QCmdOptQStringList.h"
#include "qbuCmdLine/QCmdParseError.h"
#include "qbuCmdLine/QCmdOptBasicBase.h"



/////////////////////////////////////////////////////////////////////////////////////////

QCmdOptQStringList::QCmdOptQStringList(QString strName, QString strDescription, QString strExplanation,
	QStringList strLstDefaultValue, CMDSTRVERIFY pFnVerify ): 
QCmdOptBasicBase<QStringList>( strName, strDescription,strExplanation, strLstDefaultValue ), 
	m_pFnVerify(pFnVerify),m_bWasDefault(false)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

QCmdOptQStringList::QCmdOptQStringList( const QCmdOptQStringList & other ) : SuperClass(other)
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

QCmdOptQStringList& QCmdOptQStringList::operator=( const QCmdOptQStringList & other ) 
{
	SuperClass::operator =(other);

	if ( &other != this ) {
		destroy();
		copy(other);
	}

	return (*this);
}

/////////////////////////////////////////////////////////////////////////////////////////

void QCmdOptQStringList::Insert(QString str)
{
	// Remove the default value after first non default insert
	if (m_bWasDefault) {
		m_bWasDefault = false;
		m_nValue.clear();
	}
	m_nValue.push_back(str);
}

/////////////////////////////////////////////////////////////////////////////////////////
int QCmdOptQStringList::ImportData( QString strValue )
{
	int retVal;

	QString strTemp = strValue.trimmed();

	if ( strTemp.isEmpty() ) {
		retVal = QCmdParseError::PARAM_MISSING_DATA;
	}
	else
	{
		if ( m_pFnVerify != NULL ) {
			retVal = (*m_pFnVerify)(strValue,m_nValue.size());
			if ( retVal == QCmdParseError::STATUS_OK ) {
				Insert(strValue);
			}
		}
		else
		{
			Insert(strValue);
			retVal = QCmdParseError::STATUS_OK;
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void QCmdOptQStringList::Initialize()
{
	m_nValue.clear();

	QStringList::iterator it;

	for(it=m_nDefaultValue.begin(); it != m_nDefaultValue.end();++it) {
		m_nValue.push_back(*it);
	}

	m_bWasDefault = true;

	QCmdOptBasicBase<QStringList>::Initialize();
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmdOptQStringList::GetShortSyntax()
{
	QString retVal;
	retVal = GetName(); 
	retVal += (" [");
	retVal += GetName();
	retVal += ("] [...] .");
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmdOptQStringList::GetSyntax()
{
	QString retVal = GetDescription() + " [";
	QString str;

	QStringList::iterator it=m_nDefaultValue.begin();

	if (it != m_nDefaultValue.end()) {
		retVal += *it;
		it++;
	}
	for(; it != m_nDefaultValue.end();++it) {
		retVal += (" ") + *it;
	}

	retVal += ("]");
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmdOptQStringList::exportCommandString()
{
	QString retVal;
	if (!isDefaultValue() ) {
		retVal += exportOptionName();
		QStringList strLst = GetValue();
		if (!strLst.isEmpty()) {
			foreach(QString str,strLst) {
				retVal += str + " ";
			}
		}
		retVal += ".";

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void QCmdOptQStringList::copy( const QCmdOptQStringList & other )
{
	m_pFnVerify = other.m_pFnVerify;
	m_bWasDefault = other.m_bWasDefault;
}

/////////////////////////////////////////////////////////////////////////////////////////

void QCmdOptQStringList::destroy()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

QCmdOptQStringList* QCmdOptQStringList::Clone()
{
	return new QCmdOptQStringList(*this);
}

/////////////////////////////////////////////////////////////////////////////////////////
