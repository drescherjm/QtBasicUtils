#include "qbuDataBasePCH.h"
#include "qbuDataBase/qbuQuery.h"
#include "qbuBase/qbuPropertyMap.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuQuery::qbuQuery(std::shared_ptr<QSqlDatabase> pDB) : Superclass(pDB)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	This member takes two smDBColDefs and an operator and creates an sql expression as
*  follows: ( first operator second )
*  for example: ( T1.StudyID = T2.StudyID )
*/

QString qbuQuery::genExpr(const qbuDBColDef & first, const qbuDBColDef & second,
	QString strOperator/*=QString("=")*/)
{
	QString retVal;
	QString strFirst = first.getFullName();
	QString strSecond = second.getFullName();
	if ((!strFirst.isEmpty()) && (!strSecond.isEmpty())) {
		retVal = genExpr(strFirst, strSecond, strOperator);
		//retVal = QString("( %1 %2 %3 )").arg(strFirst).arg(strOperator).arg(strSecond);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuQuery::genExpr(const qbuDBColDef & first, QString strSecond, QString strOperator/*=QString("=")*/)
{
	QString retVal;
	QString strFirst = first.getFullName();

	if ((!strFirst.isEmpty()) && (!strSecond.isEmpty())) {
		retVal = genExpr(strFirst, strSecond, strOperator);
		//retVal = QString("( %1 %2 %3 )").arg(strFirst).arg(strOperator).arg(strSecond);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuQuery::genExpr(QString & strExpr, qbuPropertyMap* pProps, QString strField,
	QString strTableAlias/*=""*/, QString strOperator/*=QString("=")*/)
{
	bool retVal = (pProps != nullptr);
	if (retVal) {
		qbuPropertyMap::iterator it = pProps->find(strField);
		retVal = (it != pProps->end());

		if (retVal) {
			qbuProperty* pProp = *it;
			const QVariant& vt = pProp->GetData();
			retVal = vt.canConvert(QVariant::String);
			if (retVal) {
				strExpr = genExpr(strField, vt.toString(), strOperator);
				//strExpr = QString(" ( %1 %2 %3 ) ").arg(strField).arg(strOperator).arg(vt.toString());
			}

		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuQuery::genExpr(QString strFirst, QString strSecond, QString strOperator/*=QString("=")*/)
{
	QString retVal;
	if ((!strFirst.isEmpty()) && (!strSecond.isEmpty())) {
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
*	If you use the qbuQuery::genExpr() members above that would require 3 calls
*	instead of the one with this member.
*	qbuQuery::genExprTableAlias( smStudyInfo::g_strStudyID, "T1","T2" );
*/

QString qbuQuery::genExprTableAlias(QString strField, QString strTA1, QString strTA2, QString strOperator/*=QString("=")*/)
{
	qbuDBColDef colDef1 = qbuDBColDef(strField).addTableAlias(strTA1);
	qbuDBColDef colDef2 = qbuDBColDef(strField).addTableAlias(strTA2);
	return genExpr(colDef1, colDef2, strOperator);
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuQuery::appendWhereExpression(QString strExpression)
{
	QLOG_CRIT() << SMLOG_DATABASE_TYPE << "qbuQuery::appendWhereExpression(QString strExpression) should never be called";
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuQuery::appendWhereExpression(const smDBExpression & expr)
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

bool qbuQuery::appendWhereExpressions(const QStringList & lstWhereFields, qbuPropertyMap* pProps, WhereExprCode code /*= WE_FAIL_ON_MISSING*/)
{

	bool retVal = (pProps != nullptr);
	if (retVal) {
		foreach(QString str, lstWhereFields) {
			QString strExpr;
			retVal = genExpr(strExpr, pProps, str);
			if (retVal) {
				appendWhereExpression(strExpr);
			}
			else
			{
				switch (code) {
				case WE_FAIL_ON_MISSING_FIELDS:
					retVal = false;
					break;
				case WE_IS_NULL_ON_MISSING_FIELDS:
					strExpr = genExpr(str, "IS NULL", "");
					retVal = appendWhereExpression(strExpr);
					break;
				case WE_IGNORE_MISSING_FIELDS:
					retVal = true;
					break;
				}

				if (!retVal) {
					break;
				}

			}
		}
	}

	return retVal;

}

/////////////////////////////////////////////////////////////////////////////////////////

