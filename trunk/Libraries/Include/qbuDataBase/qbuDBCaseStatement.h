#pragma once

#ifndef QBUDBCASESTATEMENT_H
#define QBUDBCASESTATEMENT_H

#include "qbuDataBase/qbuDatabaseLibraryDefines.h"
#include "qbuBase/qbuObject.h"
#include "qbuDataBase/qbuDBColumnDef.h"
#include "qbuDataBase/qbuDBExpression.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuDataBase_EXPORT qbuDBCaseStatement : public qbuDBExpression
{
	QBU_DECLARE_SUPERCLASS(qbuDBExpression);
public:
	qbuDBCaseStatement();
	qbuDBCaseStatement( const qbuDBCaseStatement & other );
	qbuDBCaseStatement( QString strCaseStatement, bool bEnclose );
	qbuDBCaseStatement( const qbuDBExpression & mainExpr );
	~qbuDBCaseStatement();

	qbuDBCaseStatement& operator=(const qbuDBCaseStatement & other);
	
public:
	bool	setEncloseInParentheses(bool bEnclose);

	bool	addCase(int nValue, QString strText, bool bAutoQuote=true);
	bool	addCase(QString strValue, QString strText, bool bAutoQuote = true);
	bool	addElse(QString strText, bool bAutoQuote = true);

public:
	QString toString(bool *bOK=nullptr) const;

	bool	isValid() const;

private:
	void	copy( const qbuDBCaseStatement & other );
private:
	class qbuPrivate;
	std::unique_ptr<qbuPrivate> m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUDBCASESTATEMENT_H
