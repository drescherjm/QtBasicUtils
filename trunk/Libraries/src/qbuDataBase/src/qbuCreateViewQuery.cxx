#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuCreateViewQuery.h"
#include "qbuDataBase/qbuDatabase.h"
#include "qbuDataBase/qbuSelectQuery.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuCreateViewQuery::qbuCreateViewQuery(std::shared_ptr<qbuDatabase> pDB) : Superclass(pDB)
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuCreateViewQuery::~qbuCreateViewQuery()
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuCreateViewQuery::create( QString strViewName, QString strViewQuery, bool bTempView )
{
	bool retVal = !strViewQuery.isEmpty();
	if (retVal) {

		QString	CREATE_VIEW;
		
		if (!bTempView) {
			CREATE_VIEW = QString("CREATE VIEW %1 AS %2;").arg(strViewName).arg(strViewQuery);
		}
		else
		{
			CREATE_VIEW = QString("CREATE TEMPORARY VIEW %1 AS %2;").arg(strViewName).arg(strViewQuery);
		}
		
		
		retVal = exec(CREATE_VIEW);
		if(retVal)
		{
			qDebug() << "View" << qPrintable(strViewName) << "created";
		}
		else
		{
			QString strError = QString("%1 %2 %3 \n %4")
				.arg("Failed to create view")
				.arg(strViewName)
				.arg(lastError().text())
				.arg(strViewQuery);

#ifdef QBU_DB_USES_EXCEPTIONS
			throw qbuException(__FILE__,__LINE__,qPrintable(strError),"qbuCreateViewQuery::create");
#else
			databaseError(strError);

#endif //def QBU_DB_USES_EXCEPTIONS

		}

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuCreateViewQuery::create(QString strViewName, qbuSelectQuery& query, bool bTempView /*= false*/)
{
	QString strSelectQuery;
	bool retVal = query.generateSQL(strSelectQuery);
	if (retVal) {
		retVal = create(strViewName, strSelectQuery, bTempView);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////
