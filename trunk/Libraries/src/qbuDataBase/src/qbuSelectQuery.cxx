#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuSelectQuery.h"
#include "qbuBase/qbuProperty.h"
#include "qbuBase/qbuPropertyMap.h"
#include "qbuDataBase/qbuDBColumnDefList.h"
#include "qbuDataBase/qbuDatabaseFunctions.h"
#include "qbuDataBase/qbuDBJoin.h"


#include "qbuLog/qbuLog.h"

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::g_bDumpQueries = false;

/////////////////////////////////////////////////////////////////////////////////////////

class qbuSelectQuery::smPrivate
{
public:
	qbuDBColumnDefList			m_lstSelect;
	qbuDBColumnDefList			m_lstFrom;
	QStringList					m_lstJOIN;
	qbuDBColumnDefList			m_lstGroupBy;
	qbuDBColumnDefList			m_lstOrderBy;
	QString						m_strWhereClause;
	QString						m_strHavingClause;
	qbuSelectQuery::SelectOption	m_SelectOption;
public:
	QString		generateCSVList(QStringList lst);
	QString		generateCSVList(QStringList lst, QStringList lstAliases);
	QString		getNextAlias(QStringList lst, QStringList::iterator & it);
	void		handleOrderByASC(qbuDBColDef &col, OrderByOption order);
};

/////////////////////////////////////////////////////////////////////////////////////////

//This takes a QString lists and inserts commas between each item.

QString qbuSelectQuery::smPrivate::generateCSVList(QStringList lst)
{
	QString retVal;
	QStringList::iterator it = lst.begin();
	retVal.push_back(QString("%1").arg(doubleQuoteIfNecissary(*it)));
	for (++it; it != lst.end(); ++it) {
		retVal.push_back(QString(", %1").arg(doubleQuoteIfNecissary(*it)));
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////


// NOTE: it is advanced after alias is retrieved if not at the end
QString qbuSelectQuery::smPrivate::getNextAlias(QStringList lst, QStringList::iterator & it)
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

QString qbuSelectQuery::smPrivate::generateCSVList(QStringList lst, QStringList lstAliases)
{
	QString retVal;
	QStringList::iterator it = lst.begin();
	QStringList::iterator itAlias = lstAliases.begin();
	retVal.push_back(QString("%1%2")
		.arg(doubleQuoteIfNecissary(*it))
		.arg(getNextAlias(lstAliases, itAlias)));
	for (++it; it != lst.end(); ++it) {
		retVal.push_back(QString(", %1%2")
			.arg(doubleQuoteIfNecissary(*it))
			.arg(getNextAlias(lstAliases, itAlias)));
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuSelectQuery::qbuSelectQuery(std::shared_ptr<QSqlDatabase> pDB) : Superclass(pDB),
m_pPrivate(new smPrivate)
{
	setSelectOption(QBU_SELECT_DEFAULT);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuSelectQuery::~qbuSelectQuery()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addSelectField(QString strField, QString strAlias/*=QString()*/, QString strTableAlias)
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {

		qbuDBColDef col = qbuDBColDef(strField, strAlias).addTableAlias(strTableAlias);
		retVal = addSelectField(col);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addSelectField(const qbuDBColDef & colDef)
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		m_pPrivate->m_lstSelect.push_back(colDef);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addSelectField(qbuDBExpression & expression, QString strAlias/*=QString()*/)
{
	return addSelectField(expression.toString(), strAlias);
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addFromField(QString strField, QString strAlias/*=QString()*/)
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		qbuDBColDef col = qbuDBColDef(strField).addAlias(strAlias);
		m_pPrivate->m_lstFrom.push_back(col);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////


/**
*	\brief
*	This member adds a nested select query in the from field.
*/

bool qbuSelectQuery::addFromField(qbuSelectQuery & nestedQuery, QString strAlias)
{
	bool retVal;
	QString strNested;
	retVal = nestedQuery.generateSQL(strNested);
	if (retVal) {
		strNested.prepend(" ( ");
		strNested.append(" ) ");
		retVal = addFromField(strNested, strAlias);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::generateQuery()
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		QString strQuery;
		retVal = generateSQL(strQuery);
		if (retVal) {

			strQuery = strQuery.trimmed();

			if (!strQuery.endsWith(";")) {
				strQuery.append(";");
			}

			retVal = prepare(strQuery);
			if (!retVal) {

				QString strError = QString("ERROR: qbuSelectQuery::generateQuery failed prepare a query:\n%1\n%2")
					.arg(strQuery)
					.arg(lastError().text());

#ifdef QBU_HAVE_EXCEPTIONS
				throw qbuException(__FILE__, __LINE__, qPrintable(strError), "qbuSelectQuery::generateQuery");
#else

				QLOG_CRIT() << QBULOG_DATABASE_TYPE << strError;

#endif //def QBU_HAVE_EXCEPTIONS

			}

			if (g_bDumpQueries) {
				QLOG_INFO() << QBULOG_DATABASE_TYPE << "qbuSelectQuery::generateQuery Dumping Query:" << "\n" << strQuery;
			}

		}
		else
		{
			QLOG_CRIT() << QBULOG_DATABASE_TYPE << "qbuSelectQuery::generateQuery failed to generate the SQL for a query.";
		}

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::setWhereClause(QString strWhere)
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		m_pPrivate->m_strWhereClause = strWhere;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::getRecord(qbuPropertyMap* pPropMap)
{
	bool retVal = (m_pPrivate != nullptr) && (pPropMap != nullptr);
	if (retVal) {
		retVal = isValid();
		if (retVal) {
			int nField = 0;
			foreach(qbuDBColDef col, m_pPrivate->m_lstSelect) {
				if (!isNull(nField)) {
					qbuProperty prop;
					prop.setObjectName(col.getNameOrAlias());
					prop.SetData(value(nField));

					pPropMap->insert(prop);
				}
				nField++;
			}
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

// This is used to set the option that comes just after the select. Currently the options 
bool qbuSelectQuery::setSelectOption(SelectOption option)
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		m_pPrivate->m_SelectOption = option;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::appendWhereExpression(QString strExpression)
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
	else
	{
		QString strMsg = QString("The private pointer is null at %1").arg(__FUNCTION__);
		QLOG_CRIT() << QBULOG_DATABASE_TYPE << strMsg;
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::appendWhereExpression(const qbuDBExpression & expr)
{
	QString strExpr;
	bool retVal;
	strExpr = expr.toString(&retVal);
	if (retVal) {
		retVal = appendWhereExpression(strExpr);
	}
	else
	{
		QString strMessage = QString("%1 failed to generate a WHERE expression.").arg(__FUNCTION__);

		if (strExpr.isEmpty()) {
			strMessage.append(" The expression is empty. ");
		}
		else
		{
			strMessage.append(QString(" The expression is %1").arg(strExpr));
		}
		
		QLOG_CRIT() << QBULOG_DATABASE_TYPE << strMessage;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addSelectFields(const QStringList & lstFields, QString strTableAlias)
{
	bool retVal = !lstFields.isEmpty();

	foreach(QString str, lstFields) {
		qbuDBColDef coldef = qbuDBColDef(str).addTableAlias(strTableAlias);
		if (!addSelectField(coldef)) {
			retVal = false;
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addGroupByField(QString strField, QString strTableAlias)
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		if (!strTableAlias.isEmpty()) {
			strField.prepend(strTableAlias + ".");
		}
		qbuDBColDef col(strField);
		retVal = addGroupByField(col);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addGroupByField(const qbuDBColDef & colDef)
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		qbuDBColDef col(colDef);
		col.m_strAlias.clear();
		m_pPrivate->m_lstGroupBy.push_back(col);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addOrderByField(QString strField, QString strTableAlias, OrderByOption order)
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {

		qbuDBColDef col(strField);

		if (!strTableAlias.isEmpty()) {
			col.setTableAlias(strTableAlias);
		}

		retVal = addOrderByField(col,order);

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addOrderByField(const qbuDBColDef & colDef, OrderByOption order)
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		qbuDBColDef col(colDef);
		col.m_strAlias.clear();
		m_pPrivate->handleOrderByASC(col, order);
		m_pPrivate->m_lstOrderBy.push_back(col);
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

bool qbuSelectQuery::generateSQL(QString & strSQL)
{
	bool retVal;
	QString strSelect = m_pPrivate->m_lstSelect.toString();
	retVal = !strSelect.isEmpty();
	if (retVal) {
		QString strFrom = m_pPrivate->m_lstFrom.toString();
		retVal = !strFrom.isEmpty();
		if (retVal) {
			QString strSelectOption;
			switch (m_pPrivate->m_SelectOption) {
			case QBU_SELECT_DISTINCT:
				strSelectOption = "DISTINCT ";
				break;
			case QBU_SELECT_ALL:
				strSelectOption = "ALL ";
				break;
			}
			QString strQuery = QString("SELECT %1%2 \nFROM %3")
				.arg(strSelectOption)
				.arg(strSelect)
				.arg(strFrom);

			if (!m_pPrivate->m_lstJOIN.isEmpty()) {
				foreach(QString str, m_pPrivate->m_lstJOIN) {
					strQuery.append("\n ");
					strQuery.append(str);
				}
			}

			if (!m_pPrivate->m_strWhereClause.isEmpty()) {
				strQuery.append(" \nWHERE ");
				strQuery.append(m_pPrivate->m_strWhereClause);
			}
			if (!m_pPrivate->m_lstGroupBy.isEmpty()) {
				strQuery.append(" \nGROUP BY ");
				QString strGroupBy = m_pPrivate->m_lstGroupBy.toString();

				if (!m_pPrivate->m_strHavingClause.isEmpty()) {
					strGroupBy.append(QString(" \nHAVING ( %1 ) ").arg(m_pPrivate->m_strHavingClause));
				}
				strQuery.append(strGroupBy);
			}
			if (!m_pPrivate->m_lstOrderBy.isEmpty()) {
				strQuery.append(" \nORDER BY ");
				QString strOrderBy = m_pPrivate->m_lstOrderBy.toString();
				strQuery.append(strOrderBy);
			}

			if (retVal) {
				strSQL = strQuery;
			}
		}
		else
		{
			QLOG_CRIT() << QBULOG_DATABASE_TYPE << "qbuSelectQuery::generateSQL can not generate SQL with no FROM.";
		}
	}
	else
	{
		QLOG_CRIT() << QBULOG_DATABASE_TYPE << "qbuSelectQuery::generateSQL can not generate SQL without an empty selection list.";
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBColumnDefList* qbuSelectQuery::getSelectFields()
{
	return (m_pPrivate != nullptr) ? &m_pPrivate->m_lstSelect : nullptr;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addOrderByFields(const QStringList & lstFields, QString strTableAlias, OrderByOption order)
{
	bool retVal = !lstFields.isEmpty();

	foreach(QString str, lstFields) {
		qbuDBColDef coldef = qbuDBColDef(str).addTableAlias(strTableAlias);

		m_pPrivate->handleOrderByASC(coldef, order);

		if (!addOrderByField(coldef)) {
			retVal = false;
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addGroupByFields(const QStringList & lstFields, QString strTableAlias)
{
	bool retVal = !lstFields.isEmpty();

	foreach(QString str, lstFields) {
		qbuDBColDef coldef = qbuDBColDef(str).addTableAlias(strTableAlias);
		if (!addGroupByField(coldef)) {
			retVal = false;
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	\brief
*	Appends an Having expression.
*	\details
*	This member will fail if you have not added any group by fields.
*/

bool qbuSelectQuery::appendHavingExpression(QString strExpression)
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		retVal = !strExpression.isEmpty();

		if (retVal) {
			retVal = !m_pPrivate->m_lstGroupBy.empty();
			if (retVal) {
				if (!m_pPrivate->m_strHavingClause.isEmpty()) {
					m_pPrivate->m_strHavingClause.append(" AND ");
				}
				m_pPrivate->m_strHavingClause.append(strExpression);
			}
		}

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addJoin(const qbuDBJoin & dbJoin)
{
	bool retVal = (m_pPrivate != nullptr);

	if (retVal) {
		QString strJOIN = dbJoin.toString(&retVal);

		if (retVal && !strJOIN.isEmpty()) {
			m_pPrivate->m_lstJOIN.append(strJOIN);
		}
		else
		{
			QString strMsg = QString("Failed to generate a JOIN. Did you forget to add an expression to the JOIN? "
				"If this is a JOIN that does not require an expression please use setAllowEmptyExpression(true) "
				"to allow an empty expression.");
			QLOG_CRIT() << QBULOG_DATABASE_TYPE << strMsg;
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuSelectQuery::smPrivate::handleOrderByASC(qbuDBColDef &col, OrderByOption order)
{
	switch (order)
	{
	case qbuSelectQuery::QBU_DESC:
		col.m_options |= qbuDBColDef::OP_DESCENDING;
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
