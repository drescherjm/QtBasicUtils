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
	qbuDBExpression( const qbuDBExpression & other );
	qbuDBExpression( QString strExpression, bool bEnclose = false );
	qbuDBExpression( QString strField0, QString strField1, QString strOperator, bool bEnclose = true  );
	qbuDBExpression( const qbuDBColDef & colDef0, QString strField1, QString strOperator, bool bEnclose = true  );
	qbuDBExpression( const qbuDBColDef & colDef0, const qbuDBColDef & colDef1, QString strOperator, bool bEnclose = true  );
	~qbuDBExpression();

	qbuDBExpression& operator=(const qbuDBExpression & other);

public:
	bool	setEncloseInParentheses(bool bEnclose);

	qbuDBExpression AND( const qbuDBExpression & other, bool bEnclose = false ) const;
	qbuDBExpression AND( QString strTable0, QString strTable1, const QStringList & lstFields, QString strOperator="=",bool bEnclose = false ) const;
	qbuDBExpression AND( const QStringList & lstExpressions, bool bEnclose = false ) const;
	qbuDBExpression OR( const qbuDBExpression & other, bool bEnclose = false ) const;
	qbuDBExpression OR( const QStringList & lstExpressions, bool bEnclose = false ) const;

public:
	virtual QString toString(bool *bOK=nullptr) const;

	virtual bool	isValid() const;

private:
	void	copy( const qbuDBExpression & other );
private:
	class smPrivate;
	smPrivate* m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUDBEXPRESSION_H

