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

private:
	void	copy(const qbuDBExpression & other);

private:
	class qbuPrivate;
	std::unique_ptr<qbuPrivate> m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUDBEXPRESSION_H
