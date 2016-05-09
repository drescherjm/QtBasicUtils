#pragma once

#ifndef QBUINFOALL_H
#define QBUINFOALL_H

#include "qbuDataBase/qbuInfo.h"

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	Unlike other qbuInfo based classes this one does not restrict the contents to only
 *	items in the getDBFieldNames during copies.
 *
 */

class qbuDataBase_EXPORT qbuInfoAll : public qbuInfo
{
	QBU_DECLARE_SUPERCLASS(qbuInfo);
//	Q_OBJECT
public:
	qbuInfoAll();
	qbuInfoAll(const qbuInfo & other);
	qbuInfoAll& operator=(const qbuInfo & other);
public:
	virtual const QStringList&	getDBFieldNames() const;
protected:
	virtual void copy(const qbuInfo & other);
private:
	void copy(const qbuPropertyMap * other);
	void destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUINFOALL_H
