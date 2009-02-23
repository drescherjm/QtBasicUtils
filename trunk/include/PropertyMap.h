#ifndef __PROPERTYMAP_H__
#define __PROPERTYMAP_H__

#include "Property.h"
#include <QMap>

namespace QTUTILS {

class PropertyMap : public QObject
{
	Q_OBJECT
public:
	PropertyMap();
	virtual ~PropertyMap();
	PropertyMap(const PropertyMap & other);
	PropertyMap& operator=(const PropertyMap & other);
public:
	typedef QMap<QString,Property*> Map;
	typedef Map::iterator iterator;

	iterator		insert(Property* pProp);
	iterator		insert(Property & prop);
	iterator		begin();
	iterator		end();
public:
	QString			toXML();
protected:
	Map				m_mapProps;
private:
	void copy( const PropertyMap & other );
	void destroy();
};

}; // namespace QTUTILS

Q_DECLARE_METATYPE(QTUTILS::PropertyMap)

#endif //__PROPERTYMAP_H__