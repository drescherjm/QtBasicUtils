#pragma once

#ifndef QBUDBJOIN_H
#define QBUDBJOIN_H

#include "qbuBase/qbuObject.h"
#include "qbuDataBase/qbuDBConstants.h"
#include "qbuDataBase/qbuDBCondition.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuDBJoin : public qbuObject
{
	QBU_DECLARE_SUPERCLASS(qbuObject);
public:
	qbuDBJoin();
	qbuDBJoin(const qbuDBJoin & other);
	qbuDBJoin(qbudb::JoinFlag jf,QString strSource, QString strAlias=QString());
	qbuDBJoin& operator=(const qbuDBJoin & other);
	~qbuDBJoin();
public:

public:
	bool		setJoinFlag(qbudb::JoinFlag jf);
	bool		setJoinSource(QString strSource, QString strAlias=QString());
	bool		setAllowEmptyExpression(bool bAllowEmpty);
	bool		setUSINGFields(const QStringList & lstFields);

public:
	bool		appendExpression(const qbuDBCondition & dbExpression);

public:
	qbuDBJoin	addExpression(const qbuDBCondition & dbExpression) const;
	qbuDBJoin	addJoinFlag(qbudb::JoinFlag jf) const;
	qbuDBJoin	addJoinSource(QString strSource, QString strAlias=QString()) const;
	qbuDBJoin	addAllowEmptyExpression(bool bAllow) const;
	qbuDBJoin	addUSINGFields(const QStringList & lstFields) const;

public:
	QString toString(bool *bOK=nullptr) const;

private:
	void	copy( const qbuDBJoin & other );

private:
	class qbuPrivate;
	qbuPrivate* m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUDBJOIN_H
