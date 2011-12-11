#include "qbuDBBasePCH.h"
#include "smCreateViewQuery.h"
#include "smException.h"

/////////////////////////////////////////////////////////////////////////////////////////

smCreateViewQuery::smCreateViewQuery(QSqlDatabase db) : Superclass(db)
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////

smCreateViewQuery::~smCreateViewQuery()
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////

bool smCreateViewQuery::create( QString strViewName, QString strViewQuery, bool bTempView )
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

#ifdef QBU_HAVE_EXCEPTIONS
			throw smException(__FILE__,__LINE__,qPrintable(strError),"smCreateViewQuery::create");
#else
			qDebug() << qPrintable(strError);
#endif //def QBU_HAVE_EXCEPTIONS

		}

	}
	return retVal;
}

