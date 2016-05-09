#pragma once

#ifndef QBUINFO_H
#define QBUINFO_H

#include "qbuDataBase/qbuDataBaseLibraryDefines.h"
#include "qbuBase/qbuPropertyMap.h"
#include "qbuBase/qbuMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuDataBase_EXPORT qbuInfo : public qbuPropertyMap
{
	QBU_DECLARE_SUPERCLASS(qbuPropertyMap);
	Q_OBJECT
public:
	qbuInfo();
	qbuInfo(const qbuInfo & other);
	qbuInfo& operator=(const qbuInfo & other);
public:
	virtual const QStringList&	getDBFieldNames() const =0;
	virtual bool				isDBField(QString strField) const;
	virtual void				addProperties(const qbuPropertyMap * other);
protected:
	virtual void copy(const qbuInfo & other);
private:
	void copy(const qbuPropertyMap * other);
	void destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUINFO_H
