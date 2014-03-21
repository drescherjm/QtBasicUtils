#ifndef __SMDBCOLUMNDEF_H__
#define __SMDBCOLUMNDEF_H__

#include <QString>

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\note
 *	Please take note of the addXXX const functions returning qbuDBColDefs. They do 
 *	respect the const and do not change the value of the this object. The returned 
 *	value contains the update.
 */

struct qbuDBColDef
{
public:
	qbuDBColDef(QString strField, QString strAlias);
	qbuDBColDef(QString strField, bool bAutoQuote=true);
	qbuDBColDef( const qbuDBColDef & other );
	qbuDBColDef& operator=(const qbuDBColDef other);
public:
	qbuDBColDef addTableAlias(QString strTableAlias) const;
	qbuDBColDef addAlias(QString strAlias) const;
	qbuDBColDef addName(QString strAlias, bool bAutoQuote=true) const;
	qbuDBColDef addExpression(QString strExpression) const;
public:
	//Get the string that will be suitable for a column-def for a query.
	QString getFullString() const;

	//Return the alias if it exits otherwise the name
	QString getNameOrAlias() const;

	//Return the name and table alias (if that exists) 
	QString getFullName() const;

	//Return only the name 
	QString getNameOnly() const;
private:
	void	copy(const qbuDBColDef & other);
	void	addNameInt(QString strName,bool bAutoQuote);
public:
	QString		m_strName;
	QString		m_strAlias;
	QString		m_strTableAlias;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMDBCOLUMNDEF_H__

