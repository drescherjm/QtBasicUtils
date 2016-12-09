#include "qbuDatabasePCH.h"
#include "qbuDataBase/qbuDeleteQuery.h"
#include "qbuBase/qbuProperty.h"
#include "qbuBase/qbuPropertyMap.h"
#include "qbuDataBase/qbuDBColumnDefList.h"
#include "qbuBase/qbuException.h"
#include "qbuDataBase/qbuDatabaseFunctions.h"

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDeleteQuery::g_bDumpQueries = false;

/////////////////////////////////////////////////////////////////////////////////////////

class qbuDeleteQuery::qbuPrivate
{
public:
	qbuDBColumnDefList			m_lstFrom;
	QString						m_strWhereClause;
public:
	QString		generateCSVList(QStringList lst);
	QString		generateCSVList(QStringList lst, QStringList lstAliases);
	QString		getNextAlias(QStringList lst, QStringList::iterator & it);
};

/////////////////////////////////////////////////////////////////////////////////////////

//This takes a QString lists and inserts commas between each item.

QString qbuDeleteQuery::qbuPrivate::generateCSVList(QStringList lst)
{
	QString retVal;
	QStringList::iterator it = lst.begin();
	retVal.push_back(QString("%1").arg(doubleQuoteIfNecissary(*it)));
	for(++it;it != lst.end();++it) {
		retVal.push_back(QString(", %1").arg(doubleQuoteIfNecissary(*it)));	
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////


// NOTE: it is advanced after alias is retrieved if not at the end
QString qbuDeleteQuery::qbuPrivate::getNextAlias( QStringList lst, QStringList::iterator & it )
{
	QString retVal;
	if (it != lst.end()) {
		QString str = *it;
		if (!str.isEmpty()) {
			retVal = " AS ";
			retVal.append(doubleQuoteIfNecissary(str));
		}
		it++;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This takes a QString lists and inserts commas between each item. And supports aliases
 */

QString qbuDeleteQuery::qbuPrivate::generateCSVList(QStringList lst, QStringList lstAliases)
{
	QString retVal;
	QStringList::iterator it = lst.begin();
	QStringList::iterator itAlias = lstAliases.begin();
	retVal.push_back(QString("%1%2")
		.arg(doubleQuoteIfNecissary(*it))
		.arg(getNextAlias(lstAliases,itAlias)));
	for(++it;it != lst.end();++it) {
		retVal.push_back(QString(", %1%2")
			.arg(doubleQuoteIfNecissary(*it))
			.arg(getNextAlias(lstAliases,itAlias)));	
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDeleteQuery::qbuDeleteQuery( std::shared_ptr<QSqlDatabase> pDB ) : Superclass(pDB)
{
	m_pPrivate = new qbuPrivate();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDeleteQuery::~qbuDeleteQuery()
{
	delete m_pPrivate;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDeleteQuery::addFromField( QString strField,QString strAlias/*=QString()*/)
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		qbuDBColDef col(strField,strAlias);
		m_pPrivate->m_lstFrom.push_back(col);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////


/**
 *	\brief
 *	This member adds a nested select query in the from field. 
 */

bool qbuDeleteQuery::addFromField( qbuDeleteQuery & nestedQuery,QString strAlias )
{
	bool retVal;
	QString strNested;
	retVal = nestedQuery.generateSQL(strNested);
	if (retVal) {
		strNested.prepend(" ( ");
		strNested.append(" ) ");
		retVal = addFromField(strNested,strAlias);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDeleteQuery::generateQuery()
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		QString strQuery;
		retVal = generateSQL(strQuery);
		if (retVal) {
			strQuery.append(";");
			retVal = prepare(strQuery);
			if (!retVal) {
				// Some SQL error occurred
				//qDebug() << "Failed prepare a query " << qPrintable(strQuery) << lastError();

				QString strError = QString("ERROR: Failed prepare a query %1 %2")
					.arg(strQuery)
					.arg(lastError().text());

#ifdef SM_HAVE_EXCEPTIONS
				throw qbuException(__FILE__,__LINE__,qPrintable(strError),"qbuDeleteQuery::generateQuery");
#else
				qDebug() << qPrintable(strError);
#endif //def SM_HAVE_EXCEPTIONS

			}

			if (g_bDumpQueries) {
				std::cout << "Dumping Query:" << std::endl << qPrintable(strQuery) << std::endl;
			}

		}

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDeleteQuery::setWhereClause( QString strWhere )
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		m_pPrivate->m_strWhereClause = strWhere;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDeleteQuery::appendWhereExpression( QString strExpression )
{
	bool retVal = (m_pPrivate != nullptr);

	if (retVal) {
		retVal = !strExpression.isEmpty();

		if (retVal) {
			if (!m_pPrivate->m_strWhereClause.isEmpty()) {
				m_pPrivate->m_strWhereClause.append(" AND ");
			}
			m_pPrivate->m_strWhereClause.append(strExpression);
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDeleteQuery::appendWhereExpression( const qbuDBCondition & expr )
{
	QString strExpr;
	bool retVal;
	strExpr = expr.toString(&retVal);
	if (retVal) {
		retVal = appendWhereExpression(strExpr);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief 
 *  This member generates the SQL for the current query and returns that in the
 *	string strSQL.
 *	
 */

bool qbuDeleteQuery::generateSQL( QString & strSQL )
{
	bool retVal;

	QString strFrom   = m_pPrivate->m_lstFrom.toString();
	retVal = !strFrom.isEmpty();
	if (retVal) {

		QString strQuery = QString("DELETE FROM %1")
			.arg(strFrom);

		if (!m_pPrivate->m_strWhereClause.isEmpty()) {
			strQuery.append(" WHERE ");
			strQuery.append(m_pPrivate->m_strWhereClause);
		}

		if (retVal) {
			strSQL = strQuery;
		}

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDeleteQuery::go()
{
	return generateQuery() && exec();
}

