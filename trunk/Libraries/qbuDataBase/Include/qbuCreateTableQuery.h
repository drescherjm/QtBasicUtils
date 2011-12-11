#include "qbuQuery.h"

class qbuDatabase;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This class helps in creating database queries.
 *
 *	\ingroup qbuDatabase
 *
*/

class smCreateTableQuery : public qbuQuery
{
public:
	typedef qbuQuery Superclass;
public:
	smCreateTableQuery(QSqlDatabase db);
	virtual ~smCreateTableQuery();
public:
	bool	addColumn(QString strCoumnName,QString strDataType,QString strConstraint=QString());
	bool	addPKColumn(QString strCoumnName,QString strDataType,QString strConstraint /*=QString("NOT NULL")*/);
	
	// Note this is only the column definitions.
	QString generateColumnsQueryString();
private:
	class	qbuPrivate;
	qbuPrivate*		m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

