#ifndef __SMDATABASE_H__
#define __SMDATABASE_H__

#include <QSqlDatabase>
#include "smMacros.h"
#include "smStringList.h"

class smDBSettingsTableBase;
class smData;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	This is the base class for all database classes used in the application.
 *
 *
 *	\ingroup smDatabase
 *
 */

class smDatabase : public QSqlDatabase
{
	SM_DECLARE_SUPERCLASS(QSqlDatabase);
public:
	smDatabase();
	smDatabase(const Superclass &other);
	smDatabase &operator=(const Superclass &other);
	virtual ~smDatabase();
public:
	int				getDBSchemaVersion();
	bool			tableExists(QString strTableName, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
	bool			viewExists(QString strTableName, Qt::CaseSensitivity cs = Qt::CaseInsensitive);
	static QString  generateConnectionName(QString strDataBaseName);
public:
	virtual bool	performUpgrade();

	virtual bool	fixKnownProblems();

	// Attach a database file to the connection.
	virtual bool	attachDatabase(QString strDatabaseFileName, QString strDBAlias);

	// Attach a database file to the connection.
	virtual bool	attachDatabase(smDatabase* pDB, QString strDBAlias);

	virtual bool	detachDatabaseByAlias(QString strAlias);
	virtual bool	detachDatabaseByName(QString strDBName);

	virtual bool	isDatabaseAttached(QString strDatabaseFileName, QString & strDBAlias);

	// Returns true if the database needs upgraded to a new schema.
	virtual bool	needsUpgrade(int nSchema=-2);

	// Returns true if the database has a connection string.
	virtual bool	hasConnection();

	virtual bool	verifyDBSchema();
	virtual	smDBSettingsTableBase*	getSettingsTable() =0;

	virtual	QString	getDefaultAttachName()=0;

	virtual bool	createTemporaryViews(smData* pData);

protected:
	
	virtual int		getApplicationSchemaVersion();
	virtual bool	upgradeDB(int nOldSchema, int nNewSchema);
	virtual bool	preUpgradeDB(int nOldSchema, int nNewSchema);
	virtual bool	createSettingsTable();
	virtual bool	setDBSchemaVersion(int nSchema);
	virtual bool	verifyCoverage(smStringList & lstSucceeded, smStringList & lstFailed);
protected:
	smDatabase(const smDatabase &other);
	smDatabase &operator=(const smDatabase &other);

private:
	class smPrivate;
	smPrivate*		m_pPrivate;
	void	copy(const smDatabase & other);
	void	destroy();

};

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMDATABASE_H__
