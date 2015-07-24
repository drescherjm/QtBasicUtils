#pragma once

#ifndef QBUDBSETTINGSTABLEBASE_H
#define QBUDBSETTINGSTABLEBASE_H

#include "qbuDatabase/qbuTable.h"
#include "qbuBase/qbuMacros.h"
#include <stdint.h>
#include <memory>

class qbuDBSettingInfo;

/////////////////////////////////////////////////////////////////////////////////////////

class qbuDBSettingsTableBase : public qbuTable
{
	friend class qbuDatabase;
	QBU_DECLARE_SUPERCLASS(qbuTable);
public:
	typedef qbuDBSettingInfo InfoClass;

	enum Names {
		SCHEMA_VERSION, 
		CASE_LAST_SEEN_MINIMUM_DAYS,
		ALLOW_TRUTH_ENTRY,
		CASE_VIEW_TIMEOUT_IGNORE_CASE_COUNT,
		SETUP_SCHEMA_VERSION,
		ALLOW_READER_REVIEW,
		READER_DEFAULT_PASSWORD,
	};

	qbuDBSettingsTableBase(std::shared_ptr<qbuDatabase> pDB);
public:
	virtual bool		upgradeTable(int nOldSchema, int nNewSchema);
	virtual qbuInfo*	createInfoClass() const;
	virtual QString		getTableName() const;
	virtual	int			getDBSchemaVersion();
	virtual	bool		setDBSchemaVersion( int nSchema );
	virtual	int			getMinimumDaysBetweenViewingCase();
	virtual	bool		setMinimumDaysBetweenViewingCase( quint8 nDays );
	virtual	QString		getVariableName(int nVariable);
	virtual bool		getAllowTruthEntry();
	virtual bool		setAllowTruthEntry(bool bAllow);
	virtual uint8_t		getNumberOfCompletedCasesToIgnoreViewTimeout();
	virtual	bool		setNumberOfCompletedCasesToIgnoreViewTimeout( uint8_t nCases );
	virtual bool		getAllowReaderReview();
	virtual bool		setAllowReaderReview(bool bAllow);

	virtual	int			getSetupSchemaVersion();
	virtual	bool		setSetupSchemaVersion( int nSchema );

	virtual QString		getReaderDefaultPIN();
	
public:
	bool	addSetting(qbuDBSettingInfo* pSettingInfo);
	
	// Find record using the RatingTypeID
	bool	lookupSetting(qbuDBSettingInfo* pSettingInfo);
protected:
	virtual bool	createTable( int nSchema );
	virtual bool	insertInitialValues(int nSchema);
	

public:
	static const	QString		g_strTable;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUDBSETTINGSTABLEBASE_H
