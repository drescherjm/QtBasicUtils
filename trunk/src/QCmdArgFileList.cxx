#include "QCmdArgFileList.h"
#include "QCmdParseError.h"
#include "QCmdArgBasicBase.h"

namespace QTUTILS {

	/////////////////////////////////////////////////////////////////////////////////////////

	QCmdArgFileList::QCmdArgFileList(QString strName, QString strDescription, QString strExplanation,
		QCmdLineFileList strLstDefaultValue, CMDSTRVERIFY pFnVerify ): 
	QCmdArgBasicBase<QCmdLineFileList>( strName, strDescription,strExplanation, strLstDefaultValue ), 
		m_pFnVerify(pFnVerify)
	{

	}

	/////////////////////////////////////////////////////////////////////////////////////////

	int QCmdArgFileList::ImportData( QString strValue )
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

/////////////////////////////////////////////////////////////////////////////////////////

	void QCmdArgFileList::Initialize()
	{
		m_nValue.clear();

		QStringList::iterator it;

		for(it=m_nDefaultValue.begin(); it != m_nDefaultValue.end();++it) {
			m_nValue.push_back(*it);
		}

		QCmdArgBasicBase<QCmdLineFileList>::Initialize();
	}

	/////////////////////////////////////////////////////////////////////////////////////////

	QString QCmdArgFileList::GetShortSyntax()
	{
		QString retVal;
		retVal = GetName(); 
		retVal += (" [");
		retVal += GetName();
		retVal += ("] [...] .");
		return retVal;
	}

	/////////////////////////////////////////////////////////////////////////////////////////

	QString QCmdArgFileList::GetSyntax()
	{
		QString retVal = GetDescription() + " [";
		
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

	QString QCmdArgFileList::exportCommandString()
	{
		QString retVal;
		if (!isOptional() || !isDefaultValue() ) {
			QStringList strLst = GetValue().m_strListFiles;
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

}; // namespace QTUTILS