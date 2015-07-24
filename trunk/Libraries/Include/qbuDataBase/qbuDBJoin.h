#pragma once

#ifndef SMDBJOIN_H
#define SMDBJOIN_H

#include "smDatabaseLibraryDefines.h"
#include "smObject.h"
#include "smDBConstants.h"
#include "smDBExpression.h"

/////////////////////////////////////////////////////////////////////////////////////////

class smDatabase_EXPORT smDBJoin : public smObject
{
	SM_DECLARE_SUPERCLASS(smObject);
public:
	smDBJoin();
	smDBJoin(const smDBJoin & other);
	smDBJoin(smdb::JoinFlag jf,QString strSource, QString strAlias=QString());
	smDBJoin& operator=(const smDBJoin & other);
	~smDBJoin();
public:

public:
	bool		setJoinFlag(smdb::JoinFlag jf);
	bool		setJoinSource(QString strSource, QString strAlias=QString());
	bool		setAllowEmptyExpression(bool bAllowEmpty);

public:
	bool		appendExpression(const smDBExpression & dbExpression);

public:
	smDBJoin	addExpression(const smDBExpression & dbExpression) const;
	smDBJoin	addJoinFlag(smdb::JoinFlag jf) const;
	smDBJoin	addJoinSource(QString strSource, QString strAlias=QString()) const;
	smDBJoin	addAllowEmptyExpression(bool bAllow) const;

public:
	QString toString(bool *bOK=nullptr) const;

private:
	void	copy( const smDBJoin & other );

private:
	class smPrivate;
	smPrivate* m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // SMDBJOIN_H

