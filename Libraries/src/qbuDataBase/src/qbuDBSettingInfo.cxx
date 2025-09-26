#include "qbuDataBasePCH.h"
#include "qbuDataBase/qbuDBSettingInfo.h"
#include "qbuBase/qbuProperty.h"
#include "qbuDataBase/qbuDatabaseMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////

QBU_IMPLEMENT_INFO_HELPERS(qbuDBSettingInfo);
QBU_IMPLEMENT_INFO_CONSTRUCTOR_DESTRUCTOR(qbuDBSettingInfo);

/////////////////////////////////////////////////////////////////////////////////////////

const QString qbuDBSettingInfo::g_strSettingName("Name");
const QString qbuDBSettingInfo::g_strSettingValue("Value");

/////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SA_GET(qbuDBSettingInfo,SettingValue,QString,qbuDBSettingInfo::g_strSettingValue);

/////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SA_SET(qbuDBSettingInfo,SettingName,QString,qbuDBSettingInfo::g_strSettingName);
IMPLEMENT_SA_SET(qbuDBSettingInfo,SettingValue,QString,qbuDBSettingInfo::g_strSettingValue);

/////////////////////////////////////////////////////////////////////////////////////////

const QStringList& qbuDBSettingInfo::getDBFieldNames() const
{
	static QStringList strLstFields;
	if (strLstFields.isEmpty()) {
		strLstFields = QStringList() <<
			qbuDBSettingInfo::g_strSettingName <<
			qbuDBSettingInfo::g_strSettingValue;
	}
	return strLstFields;
}

