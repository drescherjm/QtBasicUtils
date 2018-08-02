#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuCreateViewQuery.h"
#include <QDebug>
#include <QSqlError>

/////////////////////////////////////////////////////////////////////////////////////////

qbuCreateViewQuery::qbuCreateViewQuery(std::shared_ptr<QSqlDatabase> pDB) : Superclass(pDB)
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
			QString strError = QString("%1 %2 %3")
				.arg("Failed to create view")
				.arg(strViewName)
				.arg(lastError().text());

#ifdef QBU_DB_USES_EXCEPTIONS
			throw qbuException(__FILE__,__LINE__,qPrintable(strError),"qbuCreateViewQuery::create");
#else
			qDebug() << qPrintable(strError);
#endif //def QBU_DB_USES_EXCEPTIONS

		}

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////
