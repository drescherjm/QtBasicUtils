#ifndef __SMINFO_H__
#define __SMINFO_H__

#include "smPropertyMap.h"
#include "smMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////

class smInfo : public smPropertyMap
{
	SM_DECLARE_SUPERCLASS(smPropertyMap);
	Q_OBJECT
public:
	smInfo();
	smInfo(const smInfo & other);
	smInfo& operator=(const smInfo & other);
public:
	virtual const QStringList&	getDBFieldNames() const =0;
	virtual bool				isDBField(QString strField) const;
	virtual void				addProperties(PropertyMap * other);
protected:
	virtual void copy(const smInfo & other);
private:
	void copy(const PropertyMap * other);
	void destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMINFO_H__
