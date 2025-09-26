#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuDBCondition.h"
#include "qbuDataBase/qbuDBColumnDef.h"
#include "qbuDataBase/qbuDBExpression.h"
#include "qbuDataBase/qbuDatabaseFunctions.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuDBCondition::qbuPrivate
{
public:
	qbuPrivate();

public:
	bool	isValid();
	void	init( QString strField0, QString strField1, QString strOperator, bool bEnclose);
	bool	isEmpty();
public:
	bool			m_bEncloseInParentheses;
	QString			m_strCondition;
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition::qbuPrivate::qbuPrivate() : m_bEncloseInParentheses(false)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBCondition::qbuPrivate::isValid()
{
	return !m_strCondition.isEmpty();
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBCondition::qbuPrivate::isEmpty()
{
	return m_strCondition.isEmpty();
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDBCondition::qbuPrivate::init( QString strField0, QString strField1, QString strOperator, bool bEnclose )
{
	if ( (!strField0.isEmpty()) && (!strField1.isEmpty()) ) {
		m_strCondition = QString("%1 %2 %3").arg(strField0).arg(strOperator).arg(strField1);
		m_bEncloseInParentheses = bEnclose;
	}
	else
	if ( !strField0.isEmpty() ) {
		if ( (strOperator.compare("AND",Qt::CaseInsensitive) == 0) || (strOperator.compare("OR",Qt::CaseInsensitive) == 0) ) {
			m_strCondition = strField0;
			m_bEncloseInParentheses = false;
		}
	}
	else
	if ( !strField1.isEmpty() ) {
		if ( (strOperator.compare("AND",Qt::CaseInsensitive) == 0) || (strOperator.compare("OR",Qt::CaseInsensitive) == 0) ) {
			m_strCondition = strField1;
			m_bEncloseInParentheses = false;
		}
// 		else if (strOperator.indexOf("NULL") >= 0) {
// 			m_strExpression = QString("%1 %2").arg(strField0).arg(strOperator);
// 			m_bEncloseInParentheses = bEnclose;
// 		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuDBCondition::toString( bool *bOK ) const
{
	QString retVal;

	bool bValid = m_pPrivate->isValid();
	if (bValid) {

		retVal = m_pPrivate->m_strCondition;

		if (m_pPrivate->m_bEncloseInParentheses) {
			retVal = QString(" ( %1 ) ").arg(retVal);
		}

	}

	if (bOK != nullptr) {
		*bOK = bValid;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition::qbuDBCondition()
{
	m_pPrivate = new qbuPrivate;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition::qbuDBCondition( const qbuDBCondition & other ) : m_pPrivate (new qbuPrivate)
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition::qbuDBCondition( QString strExpression, bool bEnclose ) : m_pPrivate (new qbuPrivate)
{
	m_pPrivate->m_strCondition = strExpression;
	m_pPrivate->m_bEncloseInParentheses = bEnclose;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition::qbuDBCondition( QString strField0, QString strField1, QString strOperator, bool 
	bEnclose )  : m_pPrivate (new qbuPrivate)
{
	m_pPrivate->init(strField0,strField1,strOperator,bEnclose);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition::qbuDBCondition(const qbuDBExpression& expr, QString strField1, QString strOperator, bool bEnclose /*= true */) : m_pPrivate(new qbuPrivate)
{

	m_pPrivate->init(addOuterParenthesisIfNecessary(expr.toString()), strField1, strOperator, bEnclose);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition::qbuDBCondition(const qbuDBExpression& expr0, const qbuDBExpression& expr1, QString strOperator, bool bEnclose /*= true */) : m_pPrivate(new qbuPrivate)
{

	m_pPrivate->init(addOuterParenthesisIfNecessary(expr0.toString()), addOuterParenthesisIfNecessary(expr1.toString()), strOperator, bEnclose);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition::qbuDBCondition( const qbuDBColDef & colDef0, QString strField1, QString strOperator, bool bEnclose /*= true */ ) : m_pPrivate (new qbuPrivate)
{
	m_pPrivate->init(colDef0.getFullName(),strField1,strOperator,bEnclose);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition::qbuDBCondition( const qbuDBColDef & colDef0, const qbuDBColDef & colDef1, QString strOperator, bool bEnclose /*= true */ ) : m_pPrivate (new qbuPrivate)
{
	m_pPrivate->init(colDef0.getFullName(),colDef1.getFullName(),strOperator,bEnclose);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition::qbuDBCondition(const qbuDBColDef & colDef0, NullExpr nullExpr) : m_pPrivate(new qbuPrivate)
{
	switch (nullExpr) {
	case IS_NULL:
		m_pPrivate->init(colDef0.getFullName(), "IS NULL", "",true);
		break;
	case IS_NOT_NULL:
		m_pPrivate->init(colDef0.getFullName(), "IS NOT NULL", "", true);
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition::~qbuDBCondition()
{
	delete m_pPrivate;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBCondition::setEncloseInParentheses( bool bEnclose )
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		m_pPrivate->m_bEncloseInParentheses = bEnclose;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDBCondition::copy( const qbuDBCondition & other )
{
	m_pPrivate->m_bEncloseInParentheses = false;
	m_pPrivate->m_strCondition = other.toString();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition qbuDBCondition::AND(const qbuDBCondition & other, bool bEnclose) const
{
	return qbuDBCondition(toString(),other.toString(),"AND",bEnclose);
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition qbuDBCondition::AND( QString strTable0, QString strTable1, const QStringList & lstFields, QString strOperator, bool bEnclose /*= false */ ) const
{
	qbuDBCondition retVal(*this);

	foreach(QString str,lstFields) {
		qbuDBColDef colDef(str);

		qbuDBCondition expr(colDef.addTableAlias(strTable0),colDef.addTableAlias(strTable1),strOperator,bEnclose);

		retVal = retVal.AND(expr,false);
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition qbuDBCondition::AND( const QStringList & lstExpressions, bool bEnclose /*= false */ ) const
{
	qbuDBCondition retVal(*this);

	foreach(QString str,lstExpressions) {
		qbuDBCondition expr(str,false);

		retVal = retVal.AND(expr,false);
	}

	retVal.setEncloseInParentheses(bEnclose);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition qbuDBCondition::OR(const qbuDBCondition & other, bool bEnclose) const
{
	return qbuDBCondition(toString(),other.toString(),"OR",bEnclose);
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition qbuDBCondition::OR( const QStringList & lstExpressions, bool bEnclose /*= false */ ) const
{
	qbuDBCondition retVal(*this);

	foreach(QString str,lstExpressions) {
		qbuDBCondition expr(str,false);

		retVal = retVal.OR(expr,false);
	}

	retVal.setEncloseInParentheses(bEnclose);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBCondition::isValid() const
{
	return (m_pPrivate != nullptr) ? m_pPrivate->isValid() : false;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition& qbuDBCondition::operator=( const qbuDBCondition & other )
{
	if ( &other != this ) {
		copy(other);
	}
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBCondition::isEmpty() const
{
	return (m_pPrivate != nullptr) ? m_pPrivate->isEmpty() : false;
}

///////////////////////////////////////////////////////////////////////////////////////

// qbuDBCondition qbuDBCondition::IN(const qbuDBExpression & expr, QList<uint16_t> lstValues,
// 	bool bEnclose /*= true*/) const
// {
// 	QStringList sl;
// 
// 	for (auto nVal : lstValues) {
// 		sl << QString::number(nVal);
// 	}
// 
// 	return IN(expr, sl, qbuDBColDef::OP_NO_CODE, bEnclose);
// }

///////////////////////////////////////////////////////////////////////////////////////

// qbuDBCondition qbuDBCondition::IN(const qbuDBExpression & expr, QList<int> lstValues,
//     bool bEnclose /*= true*/) const
// {
//     QStringList sl;
// 
//     for (auto nVal : lstValues) {
//         sl << QString::number(nVal);
//     }
// 
//     return IN(expr, sl, qbuDBColDef::OP_NO_CODE, bEnclose);
// }

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition qbuDBCondition::IN(const qbuDBExpression & expr, QStringList slValues, 
	qbuDBColDef::Option op /*= qbuDBColDef::OP_AUTO_QUOTE*/, 
	bool bEnclose /*= true*/) const
{
	

	QString strCondition = expr.toString() + " IN ( ";

	bool bFirst = true;
	foreach(QString strVal, slValues) {
		if (!bFirst) {
			strCondition.append(", ");
		}
		else {
			bFirst = false;
		}

		if (op == qbuDBColDef::OP_AUTO_QUOTE) {
			strCondition.append(singleQuoteIfNecessary(strVal));
		}
		else {
			strCondition.append(strVal);
		}
		
	}

	strCondition.append(" ) ");

	qbuDBCondition retVal(strCondition, bEnclose);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition qbuDBCondition::NOT_IN(const qbuDBExpression& expr, QStringList slValues,
	qbuDBColDef::Option op /*= qbuDBColDef::OP_AUTO_QUOTE*/,
	bool bEnclose /*= true*/) const
{


	QString strCondition = expr.toString() + " NOT IN ( ";

	bool bFirst = true;
	for(const QString& strVal : slValues) {
		if (!bFirst) {
			strCondition.append(", ");
		}
		else {
			bFirst = false;
		}

		if (op == qbuDBColDef::OP_AUTO_QUOTE) {
			strCondition.append(singleQuoteIfNecessary(strVal));
		}
		else {
			strCondition.append(strVal);
		}

	}

	strCondition.append(" ) ");

	qbuDBCondition retVal(strCondition, bEnclose);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition qbuDBCondition::BETWEEN(const qbuDBExpression & expr, QString slLow, QString slHigh, qbuDBColDef::Option op /*= qbuDBColDef::OP_AUTO_QUOTE*/, bool bEnclose /*= true*/) const
{
	QString strCondition = expr.toString() + " BETWEEN ";
		
	if (op == qbuDBColDef::OP_AUTO_QUOTE) {
		strCondition.append(singleQuoteIfNecessary(slLow));
	}
	else {
		strCondition.append(slLow);
	}

	strCondition.append(" AND ");

	if (op == qbuDBColDef::OP_AUTO_QUOTE) {
		strCondition.append(singleQuoteIfNecessary(slHigh));
	}
	else {
		strCondition.append(slHigh);
	}

	strCondition.append(' ');

	qbuDBCondition retVal(strCondition, bEnclose);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition qbuDBCondition::BETWEEN(const qbuDBExpression & expr, int nLow, int nHigh, bool bEnclose /*= true*/) const
{
	return BETWEEN(expr, QString::number(nLow), QString::number(nHigh), qbuDBColDef::OP_NO_CODE, bEnclose);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition qbuDBCondition::NOT(const qbuDBCondition & other)
{
	QString strExpr = removeOuterParenthesis(other.toString().trimmed());
	
	return qbuDBCondition(QString("NOT(%1)").arg(strExpr));
}

/////////////////////////////////////////////////////////////////////////////////////////
