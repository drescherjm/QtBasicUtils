#pragma once

#ifndef QBUDBSETTINGINFO_H
#define QBUDBSETTINGINFO_H

#include "qbuDataBase/qbuInfo.h"
#include "qbuDataBase/qbuDBMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief 
 *	This qbuInfo class is used to retrieve settings from the DBSettings tables of each 
 *	database.
 *
 *	\ingroup qbuDatabase
 */

class qbuDBSettingInfo : public qbuInfo
{
	QBU_DECLARE_INFO_HELPERS(qbuDBSettingInfo, qbuInfo);
public:
	bool setSettingName(QString strName);	
	bool setSettingValue(QString strValue);
public:
	bool getSettingName(QString & strName);
	bool getSettingValue(QString & strValue);
public:
	virtual const QStringList& getDBFieldNames() const;
public:
	static const QString g_strSettingName;	
	static const QString g_strSettingValue;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUDBSETTINGINFO_H
