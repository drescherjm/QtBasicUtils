#pragma once

#ifndef QBUDBEXPRESSION_H
#define QBUDBEXPRESSION_H

#include "qbuBase/qbuObject.h"

struct qbuDBColDef;

/////////////////////////////////////////////////////////////////////////////////////////

class qbuDBExpression : public qbuObject
{
	QBU_DECLARE_SUPERCLASS(qbuObject);
public:
	qbuDBExpression();
	qbuDBExpression(const qbuDBExpression & other);
	qbuDBExpression(const qbuDBColDef & colDef0);
	~qbuDBExpression();

	qbuDBExpression& operator=(const qbuDBExpression & other);

public:
	virtual QString toString(bool *bOK = nullptr) const;

	virtual bool	isValid() const;
	virtual bool	isEmpty() const;

public:
	static qbuDBExpression CAST(QString strCol, QString strTableAlias = QString(), QString castAs = QString("INT"));
	static qbuDBExpression date(QString strCol, QString strTableAlias = QString());
	static qbuDBExpression datetime(QString strCol, QString strTableAlias = QString());
	static qbuDBExpression strftime(QString strFormat, QString strDateCol, QString strTableAlias = {}, QString strModifier = {});
	static qbuDBExpression unary_function(QString strFunction,QString strCol, QString strTableAlias = QString());
	static qbuDBExpression unary_function(QString strFunction, const qbuDBColDef & colDef );
	static qbuDBExpression COALESCE(QStringList lstCols, QString strTableAlias);
	static qbuDBExpression function(QString strFunction, QStringList slCols, QString strTableAlias = QString());
	static qbuDBExpression fromExpressionString(QString strExpression); // This does not auto quote

private:
	void	copy(const qbuDBExpression & other);

private:
	class qbuPrivate;
	std::unique_ptr<qbuPrivate> m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUDBEXPRESSION_H
