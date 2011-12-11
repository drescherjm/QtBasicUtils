#ifndef __SMDBCOLUMNDEF_H__
#define __SMDBCOLUMNDEF_H__

#include <QString>

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\note
 *	Please take note of the addXXX const functions returning smDBColDefs. They do 
 *	respect the const and do not change the value of the this object. The returned 
 *	value contains the update.
 */

struct smDBColDef
{
public:
	smDBColDef(QString strField, QString strAlias);
	smDBColDef(QString strField, bool bAutoQuote=true);
	smDBColDef( const smDBColDef & other );
	smDBColDef& operator=(const smDBColDef other);
public:
	smDBColDef addTableAlias(QString strTableAlias) const;
	smDBColDef addAlias(QString strAlias) const;
	smDBColDef addName(QString strAlias, bool bAutoQuote=true) const;
	smDBColDef addExpression(QString strExpression) const;
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
	void	copy(const smDBColDef & other);
	void	addNameInt(QString strName,bool bAutoQuote);
public:
	QString		m_strName;
	QString		m_strAlias;
	QString		m_strTableAlias;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMDBCOLUMNDEF_H__

