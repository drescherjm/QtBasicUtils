#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuDBCaseStatement.h"
#include <QStringList>

/////////////////////////////////////////////////////////////////////////////////////////

class qbuDBCaseStatement::qbuPrivate
{
public:
	qbuPrivate();

public:
	typedef QPair<QString,QString>	CasePair;
	typedef QList<CasePair>		CasePairList;

public:
	bool	isValid();

	bool	handleAutoQuote(QString & strVal);

public:
	bool			m_bEncloseInParentheses;
	QString			m_strCaseMainExpr;
	CasePairList	m_lstCasePairs;
	QString			m_strElse;
	bool			m_bHasANULL;

};

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCaseStatement::qbuPrivate::qbuPrivate() : m_bEncloseInParentheses(false), 
	m_bHasANULL(false)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBCaseStatement::qbuPrivate::isValid()
{
	bool retVal = !m_lstCasePairs.isEmpty();
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

		if (!m_pPrivate->m_bHasANULL) {
			retVal = "CASE " + m_pPrivate->m_strCaseMainExpr + " ";

			for(const qbuPrivate::CasePair& pair : m_pPrivate->m_lstCasePairs) {
				retVal.append(QString(" WHEN %1 THEN %2 ")
					.arg(pair.first)
					.arg(pair.second));
			}

			if (!m_pPrivate->m_strElse.isEmpty()) {
				retVal.append(QString(" ELSE %1 ").arg(m_pPrivate->m_strElse));
			}

			retVal.append(" END");
		}
		else {

			// Construct case as follows: CASE WHEN X IS NULL THEN 'x' WHEN X=SomeVal THEN 'y' WHEN X=SomeOtherVal THEN 'z' END
			retVal = "CASE ";

			for(const qbuPrivate::CasePair& pair : m_pPrivate->m_lstCasePairs) {

				if (!pair.first.contains("NULL", Qt::CaseInsensitive)) {
					retVal.append(QString(" WHEN %3=%1 THEN %2 ")
						.arg(pair.first)
						.arg(pair.second)
						.arg(m_pPrivate->m_strCaseMainExpr));
				}
				else {
					retVal.append(QString(" WHEN %3 %1 THEN %2 ")
						.arg(pair.first)
						.arg(pair.second)
						.arg(m_pPrivate->m_strCaseMainExpr));
				}
			}

			if (!m_pPrivate->m_strElse.isEmpty()) {
				retVal.append(QString(" ELSE %1 ").arg(m_pPrivate->m_strElse));
			}

			retVal.append(" END");
		}

	}

	if (bOK != nullptr) {
		*bOK = bValid;
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1600
qbuDBCaseStatement::qbuDBCaseStatement() : m_pPrivate{std::make_unique<qbuPrivate>()}
#else
qbuDBCaseStatement::qbuDBCaseStatement() : m_pPrivate(new qbuPrivate)
#endif 
{

}

/////////////////////////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1600
qbuDBCaseStatement::qbuDBCaseStatement(const qbuDBCaseStatement & other) : m_pPrivate{ std::make_unique<qbuPrivate>() }
#else
qbuDBCaseStatement::qbuDBCaseStatement(const qbuDBCaseStatement & other) : m_pPrivate(new qbuPrivate)
#endif
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1600
qbuDBCaseStatement::qbuDBCaseStatement(QString strCaseStatement, bool bEnclose) : m_pPrivate{ std::make_unique<qbuPrivate>() }
#else
qbuDBCaseStatement::qbuDBCaseStatement(QString strCaseStatement, bool bEnclose) : m_pPrivate( new qbuPrivate )
#endif
{
	m_pPrivate->m_strCaseMainExpr = strCaseStatement;
	m_pPrivate->m_bEncloseInParentheses = bEnclose;
}

/////////////////////////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1600
qbuDBCaseStatement::qbuDBCaseStatement(const qbuDBCondition & mainExpr) : m_pPrivate{ std::make_unique<qbuPrivate>() }
#else
qbuDBCaseStatement::qbuDBCaseStatement(const qbuDBCondition & mainExpr) : m_pPrivate ( new qbuPrivate )
#endif
{
	m_pPrivate->m_strCaseMainExpr = mainExpr.toString();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBCaseStatement::~qbuDBCaseStatement()
{
	/*delete m_pPrivate;*/
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
	m_pPrivate->m_strElse = other.m_pPrivate->m_strElse;
	m_pPrivate->m_bHasANULL = other.m_pPrivate->m_bHasANULL;
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

		m_pPrivate->m_lstCasePairs.push_back(qbuPrivate::CasePair(QString::number(nValue),strText));
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBCaseStatement::addCase(QString strValue, QString strText, bool bAutoQuote /*= true*/)
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {

		if (bAutoQuote) {
			retVal = m_pPrivate->handleAutoQuote(strText);
		}

		m_pPrivate->m_lstCasePairs.push_back(qbuPrivate::CasePair(strValue, strText));
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBCaseStatement::addElse(QString strText, bool bAutoQuote /*= true*/)
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {

		if (bAutoQuote) {
			retVal = m_pPrivate->handleAutoQuote(strText);
		}

		m_pPrivate->m_strElse = strText;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBCaseStatement::addNULLCase(QString strText, bool bAutoQuote /*= true*/)
{
	m_pPrivate->m_bHasANULL = true;

	return addCase("IS NULL", strText, bAutoQuote);
}

/////////////////////////////////////////////////////////////////////////////////////////
