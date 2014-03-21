#include "qbuSelectQuery.h"
#include <QStringList>
#include "Property.h"
#include "qbuPropertyMap.h"
#include <QDebug>
#include "qbuDBColumnDefList.h"
#include "qbuException.h"
#include "qbuDatabaseFunctions.h"
#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::g_bDumpQueries = false;

/////////////////////////////////////////////////////////////////////////////////////////

class qbuSelectQuery::qbuPrivate
{
public:
	qbuDBColumnDefList			m_lstSelect;
	qbuDBColumnDefList			m_lstFrom;
	qbuDBColumnDefList			m_lstGroupBy;
	qbuDBColumnDefList			m_lstOrderBy;
	QString						m_strWhereClause;
	QString						m_strHavingClause;
	qbuSelectQuery::SelectOption	m_SelectOption;
public:
	QString		generateCSVList(QStringList lst);
	QString		generateCSVList(QStringList lst, QStringList lstAliases);
	QString		getNextAlias(QStringList lst, QStringList::iterator & it);
};

/////////////////////////////////////////////////////////////////////////////////////////

//This takes a QString lists and inserts commas between each item.

QString qbuSelectQuery::qbuPrivate::generateCSVList(QStringList lst)
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
QString qbuSelectQuery::qbuPrivate::getNextAlias( QStringList lst, QStringList::iterator & it )
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

QString qbuSelectQuery::qbuPrivate::generateCSVList(QStringList lst, QStringList lstAliases)
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

qbuSelectQuery::qbuSelectQuery(QSqlDatabase db) : Superclass(db)
{
	m_pPrivate = new qbuPrivate();
	setSelectOption(QBU_SELECT_DEFAULT);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuSelectQuery::~qbuSelectQuery()
{
	delete m_pPrivate;
}


/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addSelectField(QString strField,QString strAlias/*=QString()*/,QString strTableAlias)
{
	bool retVal = (m_pPrivate != NULL);
	if (retVal) {
		
		strAlias = singleQuoteIfNecissary(strAlias);
		qbuDBColDef col = qbuDBColDef(strField,strAlias).addTableAlias(strTableAlias);
		retVal = addSelectField(col);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addSelectField( const qbuDBColDef & colDef )
{
	bool retVal = (m_pPrivate != NULL);
	if (retVal) {
		m_pPrivate->m_lstSelect.push_back(colDef);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addFromField( QString strField,QString strAlias/*=QString()*/)
{
	bool retVal = (m_pPrivate != NULL);
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

bool qbuSelectQuery::addFromField( qbuSelectQuery & nestedQuery,QString strAlias )
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

bool qbuSelectQuery::generateQuery()
{
	bool retVal = (m_pPrivate != NULL);
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

#ifdef QBU_HAVE_EXCEPTIONS
				throw qbuException(__FILE__,__LINE__,qPrintable(strError),"qbuSelectQuery::generateQuery");
#else
				qDebug() << qPrintable(strError);
#endif //def QBU_HAVE_EXCEPTIONS

			}

			if (g_bDumpQueries) {
				std::cout << "Dumping Query:" << std::endl << qPrintable(strQuery) << std::endl;
			}

		}

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::setWhereClause( QString strWhere )
{
	bool retVal = (m_pPrivate != NULL);
	if (retVal) {
		m_pPrivate->m_strWhereClause = strWhere;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::getRecord( qbuPropertyMap* pPropMap )
{
	bool retVal = (m_pPrivate != NULL) && (pPropMap != NULL);
	if (retVal) {
		retVal = isValid();
		if (retVal) {
			int nField=0;
			foreach(qbuDBColDef col,m_pPrivate->m_lstSelect) {
				if (!isNull(nField)) {
					QTUTILS::Property prop;
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
bool qbuSelectQuery::setSelectOption( SelectOption option )
{
	bool retVal = (m_pPrivate != NULL);
	if (retVal) {
		m_pPrivate->m_SelectOption = option;
	}
	return retVal;	
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::appendWhereExpression( QString strExpression )
{
	bool retVal = (m_pPrivate != NULL);

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

bool qbuSelectQuery::addSelectFields( const QStringList & lstFields, QString strTableAlias )
{
	bool retVal = !lstFields.isEmpty();

	foreach(QString str,lstFields) {
		qbuDBColDef coldef = qbuDBColDef(str).addTableAlias(strTableAlias);
		if (!addSelectField(coldef)) {
			retVal = false;
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addGroupByField( QString strField, QString strTableAlias )
{
	bool retVal = (m_pPrivate != NULL);
	if (retVal) {
		if (!strTableAlias.isEmpty()) {
			strField.prepend(strTableAlias+".");
		}
		qbuDBColDef col(strField);
		retVal = addGroupByField(col);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addGroupByField( const qbuDBColDef & colDef )
{
	bool retVal = (m_pPrivate != NULL);
	if (retVal) {
		qbuDBColDef col(colDef);
		col.m_strAlias.clear();
		m_pPrivate->m_lstGroupBy.push_back(col);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addOrderByField( QString strField, QString strTableAlias )
{
	bool retVal = (m_pPrivate != NULL);
	if (retVal) {
		if (!strTableAlias.isEmpty()) {
			strField.prepend(strTableAlias+".");
		}
		qbuDBColDef col(strField);
		retVal = addOrderByField(col);
		
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addOrderByField( const qbuDBColDef & colDef )
{
	bool retVal = (m_pPrivate != NULL);
	if (retVal) {
		qbuDBColDef col(colDef);
		col.m_strAlias.clear();
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

bool qbuSelectQuery::generateSQL( QString & strSQL )
{
	bool retVal;
	QString strSelect = m_pPrivate->m_lstSelect.toString();
	retVal = !strSelect.isEmpty();
	if (retVal) {
		QString strFrom   = m_pPrivate->m_lstFrom.toString();
		retVal = !strFrom.isEmpty();
		if (retVal) {
			QString strSelectOption;
			switch(m_pPrivate->m_SelectOption) {
				case QBU_SELECT_DISTINCT:
					strSelectOption = "DISTINCT ";
					break;
				case QBU_SELECT_ALL:
					strSelectOption = "ALL ";
					break;
			}
			QString strQuery = QString("SELECT %1%2 FROM %3")
				.arg(strSelectOption)
				.arg(strSelect)
				.arg(strFrom);

			if (!m_pPrivate->m_strWhereClause.isEmpty()) {
				strQuery.append(" WHERE ");
				strQuery.append(m_pPrivate->m_strWhereClause);
			}
			if (!m_pPrivate->m_lstGroupBy.isEmpty()) {
				strQuery.append(" GROUP BY ");
				QString strGroupBy = m_pPrivate->m_lstGroupBy.toString();

				if (!m_pPrivate->m_strHavingClause.isEmpty()) {
					strGroupBy.append(QString(" HAVING ( %1 ) ").arg(m_pPrivate->m_strHavingClause));
				}
				strQuery.append(strGroupBy);
			}
			if (!m_pPrivate->m_lstOrderBy.isEmpty()) {
				strQuery.append(" ORDER BY ");
				QString strOrderBy = m_pPrivate->m_lstOrderBy.toString();
				strQuery.append(strOrderBy);
			}
		
			if (retVal) {
				strSQL = strQuery;
			}
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	This member takes two qbuDBColDefs and an operator and creates an sql expression as 
 *  follows: ( first operator second ) 
 *  for example: ( T1.StudyID = T2.StudyID ) 
 */

QString qbuSelectQuery::genExpr( const qbuDBColDef & first, const qbuDBColDef & second,
									 QString strOperator/*=QString("=")*/ )
{
	QString retVal;
	QString strFirst = first.getFullName();
	QString strSecond = second.getFullName();
	if ( (!strFirst.isEmpty()) && (!strSecond.isEmpty()) ) {
		retVal = genExpr(strFirst,strSecond,strOperator);
		//retVal = QString("( %1 %2 %3 )").arg(strFirst).arg(strOperator).arg(strSecond);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuSelectQuery::genExpr( const qbuDBColDef & first, QString strSecond,QString strOperator/*=QString("=")*/ )
{
	QString retVal;
	QString strFirst = first.getFullName();
	
	if ( (!strFirst.isEmpty()) && (!strSecond.isEmpty()) ) {
		retVal = genExpr(strFirst,strSecond,strOperator);
		//retVal = QString("( %1 %2 %3 )").arg(strFirst).arg(strOperator).arg(strSecond);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::genExpr(QString & strExpr, qbuPropertyMap* pProps, QString strField, 
							QString strTableAlias/*=""*/,QString strOperator/*=QString("=")*/ )
{
	bool retVal = (pProps != NULL);
	if (retVal) {
		qbuPropertyMap::iterator it = pProps->find(strField);
		if (it != pProps->end()) {
			QTUTILS::Property* pProp = *it;
			const QVariant& vt =pProp->GetData();
			retVal = vt.canConvert(QVariant::String);
			if (retVal) {
				strExpr = genExpr(strField,vt.toString(),strOperator);
				//strExpr = QString(" ( %1 %2 %3 ) ").arg(strField).arg(strOperator).arg(vt.toString());
			}

		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuSelectQuery::genExpr( QString strFirst, QString strSecond,QString strOperator/*=QString("=")*/ )
{
	QString retVal;
	if ( (!strFirst.isEmpty()) && (!strSecond.isEmpty()) ) {
		retVal = QString(" ( %1 %2 %3 ) ").arg(strFirst).arg(strOperator).arg(strSecond);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This is added to simplify the generation of binary expressions.
 *	\details
 *	This member is best described by an example..
 *	Suppose you wanted to generate the following expression:
 *	( T1.StudyID = T2.StudyID ) 
 *
 *	If you use the qbuSelectQuery::genExpr() members above that would require 3 calls 
 *	instead of the one with this member. 
 *	qbuSelectQuery::genExprTableAlias( qbuStudyInfo::g_strStudyID, "T1","T2" );
 */

QString qbuSelectQuery::genExprTableAlias( QString strField, QString strTA1, QString strTA2, QString strOperator/*=QString("=")*/ )
{
	qbuDBColDef colDef1 = qbuDBColDef(strField).addTableAlias(strTA1);
	qbuDBColDef colDef2 = qbuDBColDef(strField).addTableAlias(strTA2);
	return genExpr(colDef1,colDef2,strOperator);
}


/////////////////////////////////////////////////////////////////////////////////////////

qbuDBColumnDefList* qbuSelectQuery::getSelectFields()
{
	return (m_pPrivate != NULL) ? &m_pPrivate->m_lstSelect : NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addOrderByFields( const QStringList & lstFields, QString strTableAlias )
{
	bool retVal = !lstFields.isEmpty();

	foreach(QString str,lstFields) {
		qbuDBColDef coldef = qbuDBColDef(str).addTableAlias(strTableAlias);
		if (!addOrderByField(coldef)) {
			retVal = false;
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSelectQuery::addGroupByFields( const QStringList & lstFields, QString strTableAlias )
{
	bool retVal = !lstFields.isEmpty();

	foreach(QString str,lstFields) {
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

bool qbuSelectQuery::appendHavingExpression( QString strExpression )
{
	bool retVal = (m_pPrivate != NULL);
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

bool qbuSelectQuery::appendWhereExpressions( QStringList & lstWhereFields, qbuPropertyMap* pProps )
{
	bool retVal = (pProps != NULL);
	if (retVal) {
		foreach(QString str,lstWhereFields) {
			QString strExpr;
			retVal = qbuSelectQuery::genExpr(strExpr,pProps,str);
			if (retVal) {
				appendWhereExpression(strExpr);
			}
			else
			{
				break;
			}
		}
	}

	return retVal;
}



