#include "qbuDatabasePCH.h"

#include "qbuDataBase/qbuDBCaseStatement.h"
#include <QStringList>

/////////////////////////////////////////////////////////////////////////////////////////

class qbuDBCaseStatement::qbuPrivate
{
public:
	qbuPrivate();

public:
	typedef QPair<int,QString>	CasePair;
	typedef QList<CasePair>		CasePairList;

public:
	bool	isValid();

	bool	handleAutoQuote(QString & strVal);

public:
	bool			m_bEncloseInParentheses;
	QString			m_strCaseMainExpr;
	CasePairList	m_lstCasePairs;

};

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCaseStatement::qbuPrivate::qbuPrivate() : m_bEncloseInParentheses(false)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBCaseStatement::qbuPrivate::isValid()
{
	bool retVal = !m_strCaseMainExpr.isEmpty();
	if (retVal) {
		retVal = !m_lstCasePairs.isEmpty();
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBCaseStatement::qbuPrivate::handleAutoQuote( QString & strVal )
{
	bool retVal = true;

	QChar singleQuote = '\'';

	QString strTmp = strVal.trimmed();
	if (!strTmp.isEmpty() && !strTmp.startsWith(singleQuote) && !strTmp.endsWith(singleQuote)) {
		strVal = strTmp.prepend(singleQuote).append(singleQuote);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuDBCaseStatement::toString( bool *bOK ) const
{
	QString retVal;

	bool bValid = m_pPrivate->isValid();
	if (bValid) {

		retVal = "CASE " + m_pPrivate->m_strCaseMainExpr + " ";

		foreach(qbuPrivate::CasePair pair,m_pPrivate->m_lstCasePairs) {
			retVal.append(QString(" WHEN %1 THEN %2 ")
				.arg(pair.first)
				.arg(pair.second));
		}

		retVal.append(" END");
	}

	if (bOK != nullptr) {
		*bOK = bValid;
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCaseStatement::qbuDBCaseStatement()
{
	m_pPrivate = new qbuPrivate;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCaseStatement::qbuDBCaseStatement( const qbuDBCaseStatement & other ) : m_pPrivate (new qbuPrivate)
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCaseStatement::qbuDBCaseStatement( QString strCaseStatement, bool bEnclose ) : m_pPrivate (new qbuPrivate)
{
	m_pPrivate->m_strCaseMainExpr = strCaseStatement;
	m_pPrivate->m_bEncloseInParentheses = bEnclose;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCaseStatement::qbuDBCaseStatement( const qbuDBExpression & mainExpr ) : m_pPrivate (new qbuPrivate)
{
	m_pPrivate->m_strCaseMainExpr = mainExpr.toString();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCaseStatement::~qbuDBCaseStatement()
{
	delete m_pPrivate;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBCaseStatement::setEncloseInParentheses( bool bEnclose )
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		m_pPrivate->m_bEncloseInParentheses = bEnclose;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDBCaseStatement::copy( const qbuDBCaseStatement & other )
{
	m_pPrivate->m_bEncloseInParentheses = other.m_pPrivate->m_bEncloseInParentheses;
	m_pPrivate->m_strCaseMainExpr = other.m_pPrivate->m_strCaseMainExpr;
	m_pPrivate->m_lstCasePairs = other.m_pPrivate->m_lstCasePairs;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBCaseStatement::isValid() const
{
	return (m_pPrivate != nullptr) ? m_pPrivate->isValid() : false;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCaseStatement& qbuDBCaseStatement::operator=( const qbuDBCaseStatement & other )
{
	if ( &other != this ) {
		copy(other);
	}
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBCaseStatement::addCase( int nValue, QString strText, bool bAutoQuote )
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {

		if (bAutoQuote) {
			retVal = m_pPrivate->handleAutoQuote(strText);
		}

		m_pPrivate->m_lstCasePairs.push_back(qbuPrivate::CasePair(nValue,strText));
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////