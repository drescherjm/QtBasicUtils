#include "QCmdOptQStringList.h"
#include "QCmdParseError.h"
#include "QCmdOptBasicBase.h"

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdOptQStringList::QCmdOptQStringList(QChar ch, QString strDescription, QString strExplanation,
		QStringList strLstDefaultValue, CMDSTRVERIFY pFnVerify ): 
	QCmdOptBasicBase<QStringList>( ch, strDescription,strExplanation, strLstDefaultValue ), 
		m_pFnVerify(pFnVerify)
	{

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

	void QCmdOptQStringList::Initialize()
	{
		m_nValue.clear();

		QStringList::iterator it;

		for(it=m_nDefaultValue.begin(); it != m_nDefaultValue.end();++it) {
			m_nValue.push_back(*it);
		}

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
		}
		for(; it != m_nDefaultValue.end();++it) {
			retVal += (" ") + *it;
		}
	
		retVal += ("]");
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

}; // namespace QTUTILS