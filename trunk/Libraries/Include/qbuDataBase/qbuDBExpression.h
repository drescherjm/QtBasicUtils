#pragma once

#ifndef QBUDBEXPRESSION_H
#define QBUDBEXPRESSION_H

#include "qbuBase/qbuObject.h"

struct qbuDBColDef;
class qbuDBCondition;

/////////////////////////////////////////////////////////////////////////////////////////

class qbuDBExpression : public qbuObject
{
	QBU_DECLARE_SUPERCLASS(qbuObject);
public:
	qbuDBExpression();
	qbuDBExpression(const qbuDBExpression& other);
	qbuDBExpression(const qbuDBCondition& condition, bool bEnclose);
	qbuDBExpression(const qbuDBColDef& colDef0);
	~qbuDBExpression();

	qbuDBExpression& operator=(const qbuDBExpression& other);

public:
	virtual QString toString(bool* bOK = nullptr) const;

	virtual bool	isValid() const;
	virtual bool	isEmpty() const;

public:
	static qbuDBExpression CAST(QString strCol, QString strTableAlias = QString(), QString castAs = QString("INT"));
	static qbuDBExpression date(QString strCol, QString strTableAlias = {}, const QStringList& lstModifiers = {});
	static qbuDBExpression datetime(QString strCol, QString strTableAlias = {}, const QStringList & lstModifiers = {});
	static qbuDBExpression date_functions(QString strFunction, QString strCol, QString strTableAlias = {}, const QStringList& lstModifiers = {}, 
		QString strFormat = {});
	static qbuDBExpression date_functions(QString strFunction, const qbuDBExpression & expr, const QStringList& lstModifiers = {},
		QString strFormat = {});
	static qbuDBExpression strftime(QString strFormat, QString strDateCol, QString strTableAlias = {}, const QStringList& lstModifiers = {});
	static qbuDBExpression strftime(QString strFormat, const qbuDBExpression & expr, const QStringList& lstModifiers = {});
	static qbuDBExpression unary_function(QString strFunction,QString strCol, QString strTableAlias = QString());
	static qbuDBExpression unary_function(QString strFunction, const qbuDBColDef & colDef );
	static qbuDBExpression COALESCE(QStringList lstCols, QString strTableAlias);
	static qbuDBExpression COALESCE(QList<qbuDBColDef> lstCols);
	static qbuDBExpression function(QString strFunction, QStringList slCols, QString strTableAlias = {});
	static qbuDBExpression fromExpressionString(QString strExpression); // This does not auto quote

private:
	void	copy(const qbuDBExpression & other);

private:
	class qbuPrivate;
	std::unique_ptr<qbuPrivate> m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUDBEXPRESSION_H
