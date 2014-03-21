#include "qbuPropertyMap.h"
#include "qbuMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuInfo : public qbuPropertyMap
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
	virtual void				addProperties(PropertyMap * other);
protected:
	virtual void copy(const qbuInfo & other);
private:
	void copy(const PropertyMap * other);
	void destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////

