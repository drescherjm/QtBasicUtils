#include "qbuDatabasePCH.h"

#include "qbuDataBase/qbuDBCondition.h"
#include "qbuDataBase/qbuDBColumnDef.h"


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
	QString			m_strExpression;
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition::qbuPrivate::qbuPrivate() : m_bEncloseInParentheses(false)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBCondition::qbuPrivate::isValid()
{
	return !m_strExpression.isEmpty();
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBCondition::qbuPrivate::isEmpty()
{
	return m_strExpression.isEmpty();
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDBCondition::qbuPrivate::init( QString strField0, QString strField1, QString strOperator, bool bEnclose )
{
	if ( (!strField0.isEmpty()) && (!strField1.isEmpty()) ) {
		m_strExpression = QString("%1 %2 %3").arg(strField0).arg(strOperator).arg(strField1);
		m_bEncloseInParentheses = bEnclose;
	}
	else
	if ( !strField0.isEmpty() ) {
		if ( (strOperator.compare("AND",Qt::CaseInsensitive) == 0) || (strOperator.compare("OR",Qt::CaseInsensitive) == 0) ) {
			m_strExpression = strField0;
			m_bEncloseInParentheses = false;
		}
	}
	else
	if ( !strField1.isEmpty() ) {
		if ( (strOperator.compare("AND",Qt::CaseInsensitive) == 0) || (strOperator.compare("OR",Qt::CaseInsensitive) == 0) ) {
			m_strExpression = strField1;
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

		retVal = m_pPrivate->m_strExpression;

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
	m_pPrivate->m_strExpression = strExpression;
	m_pPrivate->m_bEncloseInParentheses = bEnclose;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCondition::qbuDBCondition( QString strField0, QString strField1, QString strOperator, bool 
	bEnclose )  : m_pPrivate (new qbuPrivate)
{
	m_pPrivate->init(strField0,strField1,strOperator,bEnclose);
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
	m_pPrivate->m_strExpression = other.toString();
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

/////////////////////////////////////////////////////////////////////////////////////////