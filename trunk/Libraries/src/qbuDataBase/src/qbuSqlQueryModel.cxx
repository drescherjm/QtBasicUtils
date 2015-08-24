#include "qbuDatabasePCH.h"
#include "qbuDataBase/qbuSqlQueryModel.h"
#include "qbuDataBase/qbuSelectQuery.h"
#include "qbuDataBase/qbuDatabase.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuSqlQueryModel::qbuSqlQueryModel( QObject *parent /*= 0*/ ) : Superclass(parent)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuSqlQueryModel::setQuery( qbuSelectQuery* pQuery, std::shared_ptr<qbuDatabase> pDB )
{
	bool bSuccess = ((pQuery != nullptr) && (pDB != nullptr));
	if (bSuccess) {
		QString str;
		bSuccess = pQuery->generateSQL(str);

		if (bSuccess) {
			Superclass::clear();
			Superclass::setQuery(str,*pDB);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
