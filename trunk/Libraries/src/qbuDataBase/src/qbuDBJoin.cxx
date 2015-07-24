#include "smDatabasePCH.h"

#include "smDBJoin.h"
#include <QStringList>
#include <QString>
#include "smDBColumnDef.h"

/////////////////////////////////////////////////////////////////////////////////////////

class smDBJoin::smPrivate 
{
public:
	smPrivate(smDBJoin* pPublic);

public:
	bool isNaturalJoin();
	bool isSingleSource();
	bool isValid();

	QString getJoinString();
	QString toString();

public:
	smDBJoin*			m_pPublic;
	QString				m_strSource;
	QString				m_strAlias;
	smdb::JoinFlag		m_JoinFlag;
	QStringList			m_lstExpressions;
	bool				m_bAllowEmptyExpression;
};

/////////////////////////////////////////////////////////////////////////////////////////

smDBJoin::smPrivate::smPrivate(smDBJoin* pPublic) : m_pPublic(pPublic), 
	m_JoinFlag(smdb::JF_DEFAULT), m_bAllowEmptyExpression(false)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

bool smDBJoin::smPrivate::isNaturalJoin()
{
	bool retVal;
	switch(m_JoinFlag) {
	case smdb::JF_NATURAL_CROSS_JOIN:
	case smdb::JF_NATURAL_JOIN:
	case smdb::JF_NATURAL_LEFT_JOIN:
	case smdb::JF_NATURAL_LEFT_OUTER_JOIN:
		retVal = true;
		break;
	default:
		retVal = false;
		break;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool smDBJoin::smPrivate::isValid()
{
	bool retVal;

	retVal = ( (isNaturalJoin() || isSingleSource())  && m_lstExpressions.isEmpty()) || 
		(!(isNaturalJoin() || isSingleSource()) && ( !m_lstExpressions.isEmpty() || m_bAllowEmptyExpression) );

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool smDBJoin::smPrivate::isSingleSource()
{
	return m_JoinFlag == smdb::JF_SINGLE_SOURCE;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString smDBJoin::smPrivate::toString()
{
	QString retVal;

	if (isSingleSource()) {
		retVal = smDBColDef(m_strSource,m_strAlias).getFullString();
	}
	else
	if (isNaturalJoin()) {
		retVal = getJoinString() + smDBColDef(m_strSource,m_strAlias).getFullString();
	}
	else
	{
		smDBExpression expr = smDBExpression().AND(m_lstExpressions);

		QString strExpr = expr.toString();

		if (!strExpr.simplified().isEmpty()) {
			retVal = getJoinString() + smDBColDef(m_strSource,m_strAlias).getFullString() + " ON " + strExpr + " ";
		}
		else
		{
			retVal = getJoinString() + smDBColDef(m_strSource,m_strAlias).getFullString();
		}

	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString smDBJoin::smPrivate::getJoinString()
{
	QString retVal;
	
	switch(m_JoinFlag) {
	case smdb::JF_JOIN:
		retVal = "JOIN ";
		break;
	case smdb::JF_CROSS_JOIN:
		retVal = "CROSS JOIN ";
		break;
	case smdb::JF_LEFT_JOIN:
		retVal = "LEFT JOIN ";
		break;
	case smdb::JF_LEFT_OUTER_JOIN:
		retVal = "LEFT OUTER JOIN ";
		break;
	case smdb::JF_NATURAL_JOIN:
		retVal = "NATURAL JOIN ";
		break;
	case smdb::JF_NATURAL_CROSS_JOIN:
		retVal = "NATURAL CROSS JOIN ";
		break;
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

smDBJoin::smDBJoin() : m_pPrivate( new smPrivate(this)) 
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////

smDBJoin::smDBJoin( const smDBJoin & other )  : m_pPrivate(new smPrivate(this)) 
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

smDBJoin::smDBJoin( smdb::JoinFlag jf,QString strSource, QString strAlias )  : m_pPrivate( new smPrivate(this)) 
{
	m_pPrivate->m_strSource = strSource;
	m_pPrivate->m_strAlias = strAlias;
	m_pPrivate->m_JoinFlag = jf;
}

/////////////////////////////////////////////////////////////////////////////////////////

smDBJoin::~smDBJoin()
{
	delete m_pPrivate;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool smDBJoin::setJoinFlag( smdb::JoinFlag jf )
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		m_pPrivate->m_JoinFlag = jf;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString smDBJoin::toString( bool *bOK/*=nullptr*/ ) const
{
	QString retVal;

	bool bVal = m_pPrivate->isValid();

	if (bVal) {
		retVal = m_pPrivate->toString();
	}
	
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool smDBJoin::appendExpression( const smDBExpression & dbExpression )
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		QString strTemp = dbExpression.toString(&retVal);
		if (retVal) {
			retVal = !strTemp.isEmpty();
			if (retVal) {
				m_pPrivate->m_lstExpressions.append(strTemp);
			}
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void smDBJoin::copy( const smDBJoin & other )
{
	m_pPrivate->m_JoinFlag = other.m_pPrivate->m_JoinFlag;
	m_pPrivate->m_lstExpressions = other.m_pPrivate->m_lstExpressions;
	m_pPrivate->m_strSource = other.m_pPrivate->m_strSource;
	m_pPrivate->m_strAlias = other.m_pPrivate->m_strAlias;
	m_pPrivate->m_bAllowEmptyExpression = other.m_pPrivate->m_bAllowEmptyExpression;
}

/////////////////////////////////////////////////////////////////////////////////////////

smDBJoin smDBJoin::addExpression( const smDBExpression & dbExpression ) const
{
	smDBJoin retVal(*this);

	retVal.appendExpression(dbExpression);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

smDBJoin smDBJoin::addJoinFlag( smdb::JoinFlag jf ) const
{
	smDBJoin retVal(*this);

	retVal.setJoinFlag(jf);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

smDBJoin smDBJoin::addJoinSource( QString strSource, QString strAlias/*=QString()*/ ) const
{
	smDBJoin retVal(*this);

	retVal.setJoinSource(strSource,strAlias);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool smDBJoin::setJoinSource( QString strSource, QString strAlias/*=QString()*/ )
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		m_pPrivate->m_strSource = strSource;
		m_pPrivate->m_strAlias = strAlias;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool smDBJoin::setAllowEmptyExpression( bool bAllowEmpty )
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		m_pPrivate->m_bAllowEmptyExpression = bAllowEmpty;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

smDBJoin smDBJoin::addAllowEmptyExpression( bool bAllow ) const
{
	smDBJoin retVal(*this);

	retVal.setAllowEmptyExpression(bAllow);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////
