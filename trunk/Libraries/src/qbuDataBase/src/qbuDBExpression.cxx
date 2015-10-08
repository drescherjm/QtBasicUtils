#include "qbuDatabasePCH.h"

#include "qbuDataBase/qbuDBExpression.h"
#include "qbuDataBase/qbuDBColumnDef.h"


/////////////////////////////////////////////////////////////////////////////////////////

class qbuDBExpression::smPrivate
{
public:
	smPrivate();

public:
	bool	isValid();
	void	init( QString strField0, QString strField1, QString strOperator, bool bEnclose);

public:
	bool			m_bEncloseInParentheses;
	QString			m_strExpression;
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression::smPrivate::smPrivate() : m_bEncloseInParentheses(false)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBExpression::smPrivate::isValid()
{
	return !m_strExpression.isEmpty();
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDBExpression::smPrivate::init( QString strField0, QString strField1, QString strOperator, bool bEnclose )
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
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuDBExpression::toString( bool *bOK ) const
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

qbuDBExpression::qbuDBExpression()
{
	m_pPrivate = new smPrivate;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression::qbuDBExpression( const qbuDBExpression & other ) : m_pPrivate (new smPrivate)
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression::qbuDBExpression( QString strExpression, bool bEnclose ) : m_pPrivate (new smPrivate)
{
	m_pPrivate->m_strExpression = strExpression;
	m_pPrivate->m_bEncloseInParentheses = bEnclose;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression::qbuDBExpression( QString strField0, QString strField1, QString strOperator, bool 
	bEnclose )  : m_pPrivate (new smPrivate)
{
	m_pPrivate->init(strField0,strField1,strOperator,bEnclose);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression::qbuDBExpression( const qbuDBColDef & colDef0, QString strField1, QString strOperator, bool bEnclose /*= true */ ) : m_pPrivate (new smPrivate)
{
	m_pPrivate->init(colDef0.getFullName(),strField1,strOperator,bEnclose);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression::qbuDBExpression( const qbuDBColDef & colDef0, const qbuDBColDef & colDef1, QString strOperator, bool bEnclose /*= true */ ) : m_pPrivate (new smPrivate)
{
	m_pPrivate->init(colDef0.getFullName(),colDef1.getFullName(),strOperator,bEnclose);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression::~qbuDBExpression()
{
	delete m_pPrivate;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBExpression::setEncloseInParentheses( bool bEnclose )
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		m_pPrivate->m_bEncloseInParentheses = bEnclose;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDBExpression::copy( const qbuDBExpression & other )
{
	m_pPrivate->m_bEncloseInParentheses = false;
	m_pPrivate->m_strExpression = other.toString();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression qbuDBExpression::AND(const qbuDBExpression & other, bool bEnclose) const
{
	return qbuDBExpression(toString(),other.toString(),"AND",bEnclose);
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression qbuDBExpression::AND( QString strTable0, QString strTable1, const QStringList & lstFields, QString strOperator, bool bEnclose /*= false */ ) const
{
	qbuDBExpression retVal(*this);

	foreach(QString str,lstFields) {
		qbuDBColDef colDef(str);

		qbuDBExpression expr(colDef.addTableAlias(strTable0),colDef.addTableAlias(strTable1),strOperator,bEnclose);

		retVal = retVal.AND(expr,false);
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression qbuDBExpression::AND( const QStringList & lstExpressions, bool bEnclose /*= false */ ) const
{
	qbuDBExpression retVal(*this);

	foreach(QString str,lstExpressions) {
		qbuDBExpression expr(str,false);

		retVal = retVal.AND(expr,false);
	}

	retVal.setEncloseInParentheses(bEnclose);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression qbuDBExpression::OR(const qbuDBExpression & other, bool bEnclose) const
{
	return qbuDBExpression(toString(),other.toString(),"OR",bEnclose);
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression qbuDBExpression::OR( const QStringList & lstExpressions, bool bEnclose /*= false */ ) const
{
	qbuDBExpression retVal(*this);

	foreach(QString str,lstExpressions) {
		qbuDBExpression expr(str,false);

		retVal = retVal.OR(expr,false);
	}

	retVal.setEncloseInParentheses(bEnclose);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBExpression::isValid() const
{
	return (m_pPrivate != nullptr) ? m_pPrivate->isValid() : false;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression& qbuDBExpression::operator=( const qbuDBExpression & other )
{
	if ( &other != this ) {
		copy(other);
	}
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////