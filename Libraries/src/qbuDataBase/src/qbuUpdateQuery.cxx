#include "qbuDataBasePCH.h"
#include "qbuDataBase/qbuUpdateQuery.h"

#include "qbuBase/qbuProperty.h"
#include "qbuBase/qbuPropertyMap.h"
#include "qbuDataBase/qbuDBColumnDefList.h"
#include "qbuBase/qbuException.h"
#include "qbuDataBase/qbuDatabaseFunctions.h"
#include "qbuBase/qbuStringList.h"

#include "qbuLog/qbuLog.h"

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuUpdateQuery::g_bDumpQueries = false;

/////////////////////////////////////////////////////////////////////////////////////////

class qbuUpdateQuery::qbuPrivate
{
public:
	qbuDBColumnDefList			m_lstFrom;
	qbuStringList				m_lstSet;					
	QString						m_strWhereClause;
public:
	QString		generateCSVList(QStringList lst);
	QString		generateCSVList(QStringList lst, QStringList lstAliases);
	QString		getNextAlias(QStringList lst, QStringList::iterator & it);
};

/////////////////////////////////////////////////////////////////////////////////////////

//This takes a QString lists and inserts commas between each item.

QString qbuUpdateQuery::qbuPrivate::generateCSVList(QStringList lst)
{
	QString retVal;
	QStringList::iterator it = lst.begin();
	retVal.push_back(QString("%1").arg(doubleQuoteIfNecessary(*it)));
	for(++it;it != lst.end();++it) {
		retVal.push_back(QString(", %1").arg(doubleQuoteIfNecessary(*it)));	
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////


// NOTE: it is advanced after alias is retrieved if not at the end
QString qbuUpdateQuery::qbuPrivate::getNextAlias( QStringList lst, QStringList::iterator & it )
{
	QString retVal;
	if (it != lst.end()) {
		QString str = *it;
		if (!str.isEmpty()) {
			retVal = " AS ";
			retVal.append(doubleQuoteIfNecessary(str));
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

QString qbuUpdateQuery::qbuPrivate::generateCSVList(QStringList lst, QStringList lstAliases)
{
	QString retVal;
	QStringList::iterator it = lst.begin();
	QStringList::iterator itAlias = lstAliases.begin();
	retVal.push_back(QString("%1%2")
		.arg(doubleQuoteIfNecessary(*it))
		.arg(getNextAlias(lstAliases,itAlias)));
	for(++it;it != lst.end();++it) {
		retVal.push_back(QString(", %1%2")
			.arg(doubleQuoteIfNecessary(*it))
			.arg(getNextAlias(lstAliases,itAlias)));	
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuUpdateQuery::qbuUpdateQuery( std::shared_ptr<qbuDatabase> pDB ) : Superclass(pDB)
{
	m_pPrivate = new qbuPrivate();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuUpdateQuery::~qbuUpdateQuery()
{
	delete m_pPrivate;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuUpdateQuery::addFromField( QString strField,QString strAlias/*=QString()*/)
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

bool qbuUpdateQuery::addFromField( qbuUpdateQuery & nestedQuery,QString strAlias )
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

bool qbuUpdateQuery::generateQuery()
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

#ifdef QBU_DB_USES_EXCEPTIONS
				throw qbuException(__FILE__,__LINE__,qPrintable(strError),"qbuUpdateQuery::generateQuery");
#else
				databaseError(strError);

#endif //def QBU_DB_USES_EXCEPTIONS

			}

			if (g_bDumpQueries) {
				std::cout << "Dumping Query:" << std::endl << qPrintable(strQuery) << std::endl;
			}

		}

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuUpdateQuery::setWhereClause( QString strWhere )
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		m_pPrivate->m_strWhereClause = strWhere;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuUpdateQuery::appendWhereExpression( QString strExpression )
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

/**
 *	\brief 
 *  This member generates the SQL for the current query and returns that in the
 *	string strSQL.
 *	
 */

bool qbuUpdateQuery::generateSQL( QString & strSQL )
{
	bool retVal;

	QString strFrom   = m_pPrivate->m_lstFrom.toString();
	retVal = (!strFrom.isEmpty() && !m_pPrivate->m_lstSet.isEmpty());
	if (retVal) {

		QString strQuery = QString("UPDATE %1 ")
			.arg(strFrom);

		strQuery.append("SET ");
		strQuery.append(m_pPrivate->m_lstSet.toCSVString());

		if (!m_pPrivate->m_strWhereClause.isEmpty()) {
			strQuery.append(" WHERE ");
			strQuery.append(m_pPrivate->m_strWhereClause);
		}

		if (retVal) {
			strSQL = strQuery;
		}

	}
	else
	{
		if (strFrom.isEmpty()) {
			QLOG_WARN() << QString("In %1 the update query generation will fail because the FROM is empty!").arg(__FUNCTION__);
		}
		if (m_pPrivate->m_lstSet.isEmpty()) {
			QLOG_WARN() << QString("In %1 the update query generation will fail because there is nothing to set!").arg(__FUNCTION__);
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

// bool qbuUpdateQuery::appendWhereExpressions( QStringList & lstWhereFields, qbuPropertyMap* pProps )
// {
// 	bool retVal = (pProps != nullptr);
// 	if (retVal) {
// 		foreach(QString str,lstWhereFields) {
// 			QString strExpr;
// 			retVal = qbuUpdateQuery::genExpr(strExpr,pProps,str);
// 			if (retVal) {
// 				appendWhereExpression(strExpr);
// 			}
// 			else
// 			{
// 				break;
// 			}
// 		}
// 	}
// 
// 	return retVal;
// }

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuUpdateQuery::addSetExpression( QString strExpression )
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {

		// SQLITE does not want set expressions to be delimited by () so we have
		// to remove that.

		strExpression = strExpression.trimmed();
		retVal = (!strExpression.isEmpty());
		if (retVal) {

// 			if ( (strExpression.startsWith('(')) && (strExpression.endsWith(')'))) {
// 				strExpression.chop(1);
// 				strExpression.remove(0,1);
// 			}

			m_pPrivate->m_lstSet.push_back(removeOuterParenthesis(strExpression));
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuUpdateQuery::go()
{
	return generateQuery() && exec();
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuUpdateQuery::addSetExpressions(const QStringList & lstWhereFields, qbuPropertyMap* pProps,
	UpdateExprCode code /*= UE_IGNORE_MISSING_FIELDS*/)
{
	bool retVal = (pProps != nullptr);
	if (retVal) {
		foreach(QString str, lstWhereFields) {
			QString strExpr;
			retVal = genSetExpr(strExpr, pProps, str);
			if (retVal) {
				retVal = addSetExpression(strExpr);
			}
			if (!retVal) {
				switch (code) {
				case UE_FAIL_ON_MISSING_FIELDS:
					retVal = false;
					break;
				case UE_IGNORE_MISSING_FIELDS:
					retVal = true;
					break;
				}
			}
			if (!retVal) {
				break;
			}

		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuUpdateQuery::genSetExpr(QString & strExpr, qbuPropertyMap* pProps, QString strField, QString strTableAlias /*= ""*/)
{
	bool retVal = (pProps != nullptr);
	if (retVal) {
		qbuPropertyMap::iterator it = pProps->find(strField);
		retVal = (it != pProps->end());

		if (retVal) {

			const QString strOperator = QString("=");

			qbuProperty* pProp = *it;
			const QVariant& vt = pProp->GetData();
			retVal = vt.canConvert(QVariant::String);
			if (retVal) {

				switch (vt.type()) {
				case QVariant::String:
					strExpr = genExpr(strField, QString("\'%1\'").arg(vt.toString()), strOperator);
					break;
				case QVariant::Date:
					strExpr = genExpr(strField, QString("date(\'%1\')").arg(vt.toString()), strOperator);
					break;
				case QVariant::DateTime:
					strExpr = genExpr(strField, QString("datetime(\'%1\')").arg(vt.toString()), strOperator);
					break;
				case QVariant::Bool:
					if (vt.toBool()) {
						strExpr = genExpr(strField, QString::number(1), strOperator);
					}
					else
					{
						strExpr = genExpr(strField, QString::number(0), strOperator);
					}
					break;
				default:
					strExpr = genExpr(strField, vt.toString(), strOperator);
					break;
				}

				//strExpr = QString(" ( %1 %2 %3 ) ").arg(strField).arg(strOperator).arg(vt.toString());
			}

		}
	}
	return retVal;
}


/////////////////////////////////////////////////////////////////////////////////////////
