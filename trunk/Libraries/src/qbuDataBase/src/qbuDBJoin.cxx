#include "qbuDatabasePCH.h"

#include "qbuDataBase/qbuDBJoin.h"
#include "qbuDataBase/qbuDBColumnDef.h"
#include "qbuDataBase/qbuDatabaseFunctions.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuDBJoin::smPrivate 
{
public:
	smPrivate(qbuDBJoin* pPublic);

public:
	bool isNaturalJoin();
	bool isSingleSource();
	bool isValid();

	QString getJoinString();
	QString toString();

public:
	qbuDBJoin*			m_pPublic;
	QString				m_strSource;
	QString				m_strAlias;
	qbudb::JoinFlag		m_JoinFlag;
	QStringList			m_lstExpressions;
	QStringList			m_lstUsing;
	bool				m_bAllowEmptyExpression;
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBJoin::smPrivate::smPrivate(qbuDBJoin* pPublic) : m_pPublic(pPublic), 
	m_JoinFlag(qbudb::JF_DEFAULT), m_bAllowEmptyExpression(false)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBJoin::smPrivate::isNaturalJoin()
{
	bool retVal;
	switch(m_JoinFlag) {
	case qbudb::JF_NATURAL_CROSS_JOIN:
	case qbudb::JF_NATURAL_JOIN:
	case qbudb::JF_NATURAL_LEFT_JOIN:
	case qbudb::JF_NATURAL_LEFT_OUTER_JOIN:
		retVal = true;
		break;
	default:
		retVal = false;
		break;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBJoin::smPrivate::isValid()
{
	bool retVal;

	retVal = ( (isNaturalJoin() || isSingleSource())  && m_lstExpressions.isEmpty()) || 
		(!(isNaturalJoin() || isSingleSource()) && ( !m_lstExpressions.isEmpty() || m_bAllowEmptyExpression) );

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBJoin::smPrivate::isSingleSource()
{
	return m_JoinFlag == qbudb::JF_SINGLE_SOURCE;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuDBJoin::smPrivate::toString()
{
	QString retVal;

	if (isSingleSource()) {
		retVal = qbuDBColDef(m_strSource,m_strAlias).getFullString();
	}
	else
	if (isNaturalJoin()) {
		retVal = getJoinString() + qbuDBColDef(m_strSource,m_strAlias).getFullString();
	}
	else
	{
		qbuDBExpression expr = qbuDBExpression().AND(m_lstExpressions);

		QString strExpr = expr.toString();

		if (!strExpr.simplified().isEmpty()) {
			retVal = getJoinString() + qbuDBColDef(m_strSource).addAlias(m_strAlias).getFullString() + " ON\n  " + strExpr + " ";
		}
		else
		{
			retVal = getJoinString() + qbuDBColDef(m_strSource).addAlias(m_strAlias).getFullString();
			if (!m_lstUsing.isEmpty()) {
				retVal += QString(" USING \n   ( %1 ) ").arg(m_lstUsing.join(","));
			}
					
		}

	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuDBJoin::smPrivate::getJoinString()
{
	QString retVal;
	
	switch(m_JoinFlag) {
	case qbudb::JF_JOIN:
		retVal = "JOIN ";
		break;
	case qbudb::JF_CROSS_JOIN:
		retVal = "CROSS JOIN ";
		break;
	case qbudb::JF_LEFT_JOIN:
		retVal = "LEFT JOIN ";
		break;
	case qbudb::JF_LEFT_OUTER_JOIN:
		retVal = "LEFT OUTER JOIN ";
		break;
	case qbudb::JF_NATURAL_JOIN:
		retVal = "NATURAL JOIN ";
		break;
	case qbudb::JF_NATURAL_CROSS_JOIN:
		retVal = "NATURAL CROSS JOIN ";
		break;
	case qbudb::JF_NATURAL_LEFT_OUTER_JOIN:
		retVal = "NATURAL LEFT OUTER JOIN ";
		break;
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBJoin::qbuDBJoin() : m_pPrivate( new smPrivate(this)) 
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBJoin::qbuDBJoin( const qbuDBJoin & other )  : m_pPrivate(new smPrivate(this)) 
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBJoin::qbuDBJoin( qbudb::JoinFlag jf,QString strSource, QString strAlias )  : m_pPrivate( new smPrivate(this)) 
{
	m_pPrivate->m_strSource = strSource;
	m_pPrivate->m_strAlias = strAlias;
	m_pPrivate->m_JoinFlag = jf;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBJoin::~qbuDBJoin()
{
	delete m_pPrivate;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBJoin::setJoinFlag( qbudb::JoinFlag jf )
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		m_pPrivate->m_JoinFlag = jf;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuDBJoin::toString( bool *bOK/*=nullptr*/ ) const
{
	QString retVal;

	bool bVal = m_pPrivate->isValid();

	if (bVal) {
		retVal = m_pPrivate->toString();
	}
	
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBJoin::appendExpression( const qbuDBExpression & dbExpression )
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

void qbuDBJoin::copy( const qbuDBJoin & other )
{
	m_pPrivate->m_JoinFlag = other.m_pPrivate->m_JoinFlag;
	m_pPrivate->m_lstExpressions = other.m_pPrivate->m_lstExpressions;
	m_pPrivate->m_strSource = other.m_pPrivate->m_strSource;
	m_pPrivate->m_strAlias = other.m_pPrivate->m_strAlias;
	m_pPrivate->m_bAllowEmptyExpression = other.m_pPrivate->m_bAllowEmptyExpression;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBJoin qbuDBJoin::addExpression( const qbuDBExpression & dbExpression ) const
{
	qbuDBJoin retVal(*this);

	retVal.appendExpression(dbExpression);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBJoin qbuDBJoin::addJoinFlag( qbudb::JoinFlag jf ) const
{
	qbuDBJoin retVal(*this);

	retVal.setJoinFlag(jf);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBJoin qbuDBJoin::addJoinSource( QString strSource, QString strAlias/*=QString()*/ ) const
{
	qbuDBJoin retVal(*this);

	retVal.setJoinSource(strSource,strAlias);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBJoin::setJoinSource( QString strSource, QString strAlias/*=QString()*/ )
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		m_pPrivate->m_strSource = strSource;
		m_pPrivate->m_strAlias = strAlias;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBJoin::setAllowEmptyExpression( bool bAllowEmpty )
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		m_pPrivate->m_bAllowEmptyExpression = bAllowEmpty;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBJoin qbuDBJoin::addAllowEmptyExpression( bool bAllow ) const
{
	qbuDBJoin retVal(*this);

	retVal.setAllowEmptyExpression(bAllow);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBJoin qbuDBJoin::addUSINGFields(const QStringList & lstFields) const
{
	qbuDBJoin retVal(*this);

	retVal.setUSINGFields(lstFields);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBJoin::setUSINGFields(const QStringList & lstFields)
{
	bool retVal = m_pPrivate->m_lstExpressions.isEmpty();

	foreach (QString str,lstFields) {
		m_pPrivate->m_lstUsing << quoteSQLObjectNameIfNecissary(str);
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////
