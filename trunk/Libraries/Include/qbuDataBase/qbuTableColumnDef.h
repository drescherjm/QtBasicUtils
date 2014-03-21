#include "qbuInfo.h"
#include <QList>
#include "qbuMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief 
 *	This class is used to hold the table column definition.
 *
 *	\details
 *	Currently this class is only with the qbuTableSchema to hold the database schema.
 *
 *	\ingroup qbuDatabase
 */

class qbuTableColumnDef : public qbuInfo
{
	Q_OBJECT
	QBU_DECLARE_SUPERCLASS(qbuInfo);
public:
	qbuTableColumnDef();
	qbuTableColumnDef(const qbuTableColumnDef & other);
	qbuTableColumnDef(const Superclass & other);
	qbuTableColumnDef& operator=(const qbuTableColumnDef & other);
	qbuTableColumnDef& operator=(const Superclass & other);
public:
	bool setName(QString strName);
	bool setType(QString strName);
	bool setNotNull(bool nVal);
	bool setPrimaryKey(bool nVal);
public:
	bool getName(QString & strName);
	bool getType(QString & strName);
	bool getNotNull(bool & nVal);
	bool getPrimaryKey(bool & nVal);
public:
	const QStringList& getDBFieldNames() const;
public:
	static const QString g_strName;
	static const QString g_strType;
	static const QString g_strNotNull;
	static const QString g_strPrimaryKey;

private:
	void copy(const qbuTableColumnDef & other);
	void destroy();
};

typedef QList<qbuTableColumnDef> qbuTableColumnDefList;

/////////////////////////////////////////////////////////////////////////////////////////

