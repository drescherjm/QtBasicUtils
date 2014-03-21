#include "qbuDataBase/qbuCreateViewQuery.h"
#include "qbuDataBase/qbuException.h"
#include <QDebug>

/////////////////////////////////////////////////////////////////////////////////////////

qbuCreateViewQuery::qbuCreateViewQuery(QSqlDatabase db) : Superclass(db)
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

#ifdef QBU_HAVE_EXCEPTIONS
			throw qbuException(__FILE__,__LINE__,qPrintable(strError),"qbuCreateViewQuery::create");
#else
			qDebug() << qPrintable(strError);
#endif //def QBU_HAVE_EXCEPTIONS

		}

	}
	return retVal;
}

