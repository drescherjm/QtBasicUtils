#ifndef __SMDATABASE_H__
#define __SMDATABASE_H__

#include <QSqlDatabase>
#include "qbuMacros.h"
#include "smStringList.h"

class qbuDBSettingsTableBase;
class qbuData;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	This is the base class for all database classes used in the application.
 *
 *
 *	\ingroup qbuDatabase
 *
 */

class qbuDatabase : public QSqlDatabase
{
	QBU_DECLARE_SUPERCLASS(QSqlDatabase);
public:
	qbuDatabase();
	qbuDatabase(const Superclass &other);
	qbuDatabase &operator=(const Superclass &other);
	virtual ~qbuDatabase();
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
	virtual bool	attachDatabase(qbuDatabase* pDB, QString strDBAlias);

	virtual bool	detachDatabaseByAlias(QString strAlias);
	virtual bool	detachDatabaseByName(QString strDBName);

	virtual bool	isDatabaseAttached(QString strDatabaseFileName, QString & strDBAlias);

	// Returns true if the database needs upgraded to a new schema.
	virtual bool	needsUpgrade(int nSchema=-2);

	// Returns true if the database has a connection string.
	virtual bool	hasConnection();

	virtual bool	verifyDBSchema();
	virtual	qbuDBSettingsTableBase*	getSettingsTable() =0;

	virtual	QString	getDefaultAttachName()=0;

	virtual bool	createTemporaryViews(qbuData* pData);

protected:
	
	virtual int		getApplicationSchemaVersion();
	virtual bool	upgradeDB(int nOldSchema, int nNewSchema);
	virtual bool	preUpgradeDB(int nOldSchema, int nNewSchema);
	virtual bool	createSettingsTable();
	virtual bool	setDBSchemaVersion(int nSchema);
	virtual bool	verifyCoverage(smStringList & lstSucceeded, smStringList & lstFailed);
protected:
	qbuDatabase(const qbuDatabase &other);
	qbuDatabase &operator=(const qbuDatabase &other);

private:
	class qbuPrivate;
	qbuPrivate*		m_pPrivate;
	void	copy(const qbuDatabase & other);
	void	destroy();

};

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMDATABASE_H__
