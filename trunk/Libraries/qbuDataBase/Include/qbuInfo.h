#ifndef __SMINFO_H__
#define __SMINFO_H__

#include "qbuPropertyMap.h"
#include "smMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuInfo : public qbuPropertyMap
{
	SM_DECLARE_SUPERCLASS(qbuPropertyMap);
	Q_OBJECT
public:
	qbuInfo();
	qbuInfo(const qbuInfo & other);
	qbuInfo& operator=(const qbuInfo & other);
public:
	virtual const QStringList&	getDBFieldNames() const =0;
	virtual bool				isDBField(QString strField) const;
	virtual void				addProperties(PropertyMap * other);
protected:
	virtual void copy(const qbuInfo & other);
private:
	void copy(const PropertyMap * other);
	void destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMINFO_H__
