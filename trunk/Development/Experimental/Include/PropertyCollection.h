#ifndef __PROPERTYCOLLECTION_H__
#define __PROPERTYCOLLECTION_H__

#include "Property.h"
#include <QMap>

namespace QTUTILS {

typedef QMap<QString,Property*> PropertyMap;

class PropertyMap : public Property
{
	Q_OBJECT
public:
	PropertyMap();
	virtual ~PropertyMap();
	PropertyMap(const PropertyMap & other);
	PropertyMap& operator=(const PropertyMap & other);
public:
	typedef PropertyMap::iterator iterator;

	iterator		insert(Property* pProp);
	iterator		insert(Property & prop);
	iterator		begin();
	iterator		end();
public:
	QString			toXML();
protected:
	PropertyMap		m_mapProps;
private:
	void copy( const PropertyMap & other );
	void destroy();
};

}; // namespace QTUTILS

Q_DECLARE_METATYPE(QTUTILS::PropertyMap)

#endif //__PROPERTYCOLLECTION_H__