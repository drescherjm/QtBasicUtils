#pragma once

#ifndef QBUDBEXPRESSION_H
#define QBUDBEXPRESSION_H

#include "qbuBase/qbuObject.h"

struct qbuDBColDef;

/////////////////////////////////////////////////////////////////////////////////////////

class qbuDBCondition : public qbuObject
{
	QBU_DECLARE_SUPERCLASS(qbuObject);	

public:
	enum NullExpr{ IS_NULL, 
		IS_NOT_NULL
	};
public:
	qbuDBCondition();
	qbuDBCondition( const qbuDBCondition & other );
	qbuDBCondition( QString strExpression, bool bEnclose = false );
	qbuDBCondition( QString strField0, QString strField1, QString strOperator, bool bEnclose = true  );
	qbuDBCondition( const qbuDBColDef & colDef0, QString strField1, QString strOperator, bool bEnclose = true  );
	qbuDBCondition( const qbuDBColDef & colDef0, const qbuDBColDef & colDef1, QString strOperator, bool bEnclose = true  );
	qbuDBCondition( const qbuDBColDef & colDef0, NullExpr nullExpr);
	~qbuDBCondition();
	
	qbuDBCondition& operator=(const qbuDBCondition & other);

public:
	bool	setEncloseInParentheses(bool bEnclose);

	qbuDBCondition AND( const qbuDBCondition & other, bool bEnclose = false ) const;
	qbuDBCondition AND( QString strTable0, QString strTable1, const QStringList & lstFields, QString strOperator="=",bool bEnclose = false ) const;
	qbuDBCondition AND( const QStringList & lstExpressions, bool bEnclose = false ) const;
	qbuDBCondition OR( const qbuDBCondition & other, bool bEnclose = false ) const;
	qbuDBCondition OR( const QStringList & lstExpressions, bool bEnclose = false ) const;

	//qbuDBCondition IN(const qbuDBCondition & other, QStringList slValues, bool bEnclose = true) const;

public:
	virtual QString toString(bool *bOK=nullptr) const;

	virtual bool	isValid() const;
	virtual bool	isEmpty() const;

private:
	void	copy( const qbuDBCondition & other );
private:
	class qbuPrivate;
	qbuPrivate* m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUDBEXPRESSION_H

