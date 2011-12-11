#include "smInfo.h"
#include <QList>
#include "smMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief 
 *	This class is used to hold the table column definition.
 *
 *	\details
 *	Currently this class is only with the smTableSchema to hold the database schema.
 *
 *	\ingroup smDatabase
 */

class smTableColumnDef : public smInfo
{
	Q_OBJECT
	SM_DECLARE_SUPERCLASS(smInfo);
public:
	smTableColumnDef();
	smTableColumnDef(const smTableColumnDef & other);
	smTableColumnDef(const Superclass & other);
	smTableColumnDef& operator=(const smTableColumnDef & other);
	smTableColumnDef& operator=(const Superclass & other);
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
	void copy(const smTableColumnDef & other);
	void destroy();
};

typedef QList<smTableColumnDef> smTableColumnDefList;

/////////////////////////////////////////////////////////////////////////////////////////

