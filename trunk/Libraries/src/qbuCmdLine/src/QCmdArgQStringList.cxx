#include "qbuCmdLine/QCmdArgQStringList.h"
#include "qbuCmdLine/QCmdParseError.h"
#include "qbuCmdLine/QCmdArgBasicBase.h"

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdArgQStringList::QCmdArgQStringList(QString strName, QString strDescription, QString strExplanation,
		QStringList strLstDefaultValue, CMDSTRVERIFY pFnVerify ): 
	QCmdArgBasicBase<QStringList>( strName, strDescription,strExplanation, strLstDefaultValue ), 
		m_pFnVerify(pFnVerify),m_bWasDefault(false)
	{

	}

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdArgQStringList::QCmdArgQStringList( const QCmdArgQStringList & other ) :SuperClass(other)
	{
		copy(other);
	}

/////////////////////////////////////////////////////////////////////////////////////////
	void QCmdArgQStringList::Insert(QString strValue)
	{
		// Remove the default value after first non default insert
		if (m_bWasDefault) {
			m_bWasDefault = false;
			m_nValue.clear();
		}

		m_nValue.push_back(strValue);
	}

/////////////////////////////////////////////////////////////////////////////////////////

	int QCmdArgQStringList::ImportData( QString strValue )
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

	void QCmdArgQStringList::Initialize()
	{
		m_nValue.clear();

		QStringList::iterator it;

		for(it=m_nDefaultValue.begin(); it != m_nDefaultValue.end();++it) {
			m_nValue.push_back(*it);
		}

		m_bWasDefault = true;

		QCmdArgBasicBase<QStringList>::Initialize();
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QString QCmdArgQStringList::GetShortSyntax()
	{
		QString retVal;
		retVal = GetName(); 
		retVal += (" [");
		retVal += GetName();
		retVal += ("] [...] .");
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QString QCmdArgQStringList::GetSyntax()
	{
		QString retVal = GetDescription() + " [";

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

	QString QCmdArgQStringList::exportCommandString()
	{
		QString retVal;
		if (!isOptional() || !isDefaultValue() ) {
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

QCmdArgQStringList& QCmdArgQStringList::operator=( const QCmdArgQStringList & other )
{
	SuperClass::operator =(other);

	if ( &other != this ) {
		destroy();
		copy(other);
	}

	return (*this);
}

/////////////////////////////////////////////////////////////////////////////////////////

QCmdArgQStringList* QCmdArgQStringList::Clone()
{
	return new QCmdArgQStringList(*this);
}

/////////////////////////////////////////////////////////////////////////////////////////

void QCmdArgQStringList::copy( const QCmdArgQStringList & other )
{
	m_pFnVerify = other.m_pFnVerify;
	m_bWasDefault = other.m_bWasDefault;
}

/////////////////////////////////////////////////////////////////////////////////////////

void QCmdArgQStringList::destroy()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

}; // namespace QTUTILS
