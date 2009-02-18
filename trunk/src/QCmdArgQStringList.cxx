#include "QCmdArgQStringList.h"
#include "QCmdParseError.h"
#include "QCmdArgBasicBase.h"

namespace QTUTILS {

	/////////////////////////////////////////////////////////////////////////////////////////

	QCmdArgQStringList::QCmdArgQStringList(QString strName, QString strDescription, QString strExplanation,
		QStringList strLstDefaultValue, CMDSTRVERIFY pFnVerify ): 
	QCmdArgBasicBase<QStringList>( strName, strDescription,strExplanation, strLstDefaultValue ), 
		m_pFnVerify(pFnVerify)
	{

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
					m_nValue.push_back(strValue);
				}
			}
			else
			{
				m_nValue.push_back(strValue);
				retVal = QCmdParseError::STATUS_OK;
			}
		}

		return retVal;
	}

	void QCmdArgQStringList::Initialize()
	{
		m_nValue.clear();

		QStringList::iterator it;

		for(it=m_nDefaultValue.begin(); it != m_nDefaultValue.end();++it) {
			m_nValue.push_back(*it);
		}

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
		QString retVal;
		QString tempStr = ("%s [");
		retVal.sprintf(tempStr.toAscii(),GetDescription());
		QString str;

		QStringList::iterator it=m_nDefaultValue.begin();

		if (it != m_nDefaultValue.end()) {
			tempStr += *it;
		}
		for(; it != m_nDefaultValue.end();++it) {
			tempStr += (" ") + *it;
		}

		tempStr += ("]");
		return retVal;
	}

	/////////////////////////////////////////////////////////////////////////////////////////

}; // namespace QTUTILS