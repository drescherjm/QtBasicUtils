#pragma once

#ifndef QBUDBCOLUMNDEF_H
#define QBUDBCOLUMNDEF_H

#include <QObject>
#include <QString>
#include <QFlags>

/////////////////////////////////////////////////////////////////////////////////////////

class qbuDBCondition;
class qbuDBExpression;

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	\note
*	Please take note of the addXXX const functions returning smDBColDefs. They do
*	respect the const and do not change the value of the this object. The returned
*	value contains the update.
*/

struct qbuDBColDef : public QObject
{	
	friend class qbuDBExpression;
	Q_OBJECT
public:
	enum Option {
		OP_NO_CODE       = 0,
		OP_AUTO_QUOTE    = 1,
		OP_IS_EXPRESSION = 2,
		OP_DESCENDING    = 4,
	};

	Q_DECLARE_FLAGS(Options, Option);

public:
	qbuDBColDef(const qbuDBExpression & expr, QString strAlias);
	qbuDBColDef(const qbuDBCondition & expr, QString strAlias);
	qbuDBColDef(QString strField, QString strAlias);
	qbuDBColDef(QString strField, Options op = OP_AUTO_QUOTE);
	qbuDBColDef(const qbuDBColDef & other);
	qbuDBColDef& operator=(const qbuDBColDef other);

public:
	qbuDBColDef addTableAlias(QString strTableAlias) const;
	qbuDBColDef addAlias(QString strAlias) const;
	qbuDBColDef addName(QString strAlias, Options op = OP_AUTO_QUOTE) const;
	qbuDBColDef addExpression(QString strExpression) const;

public:
	void	setTableAlias(QString strTableAlias);
	void	setAlias(QString strAlias);

public:
	//Get the string that will be suitable for a column-def for a query.
	QString getFullString() const;

	//Return the alias if it exits otherwise the name
	QString getNameOrAlias() const;

	//Return the name and table alias (if that exists) 
	QString getFullName() const;

	//Return only the name 
	QString getNameOnly() const;

	//Return only the alias
	QString getAlias() const;

	bool	isExpression() const;
	bool	hasAlias() const;

private:
	qbuDBColDef();
	void	copy(const qbuDBColDef & other);
	void	addNameInt(QString strName);
public:
	QString		m_strName;
	QString		m_strAlias;
	QString		m_strTableAlias;
	Options		m_options;
};

/////////////////////////////////////////////////////////////////////////////////////////

Q_DECLARE_OPERATORS_FOR_FLAGS(qbuDBColDef::Options);

#endif // QBUDBCOLUMNDEF_H
