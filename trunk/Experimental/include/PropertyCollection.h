#ifndef __PROPERTYCOLLECTION_H__
#define __PROPERTYCOLLECTION_H__

#include "Property.h"
#include <QMap>

namespace QTUTILS {

typedef QMap<QString,Property*> PropertyMap;

class PropertyCollection : public Property
{
	Q_OBJECT
public:
	PropertyCollection();
	virtual ~PropertyCollection();
	PropertyCollection(const PropertyCollection & other);
	PropertyCollection& operator=(const PropertyCollection & other);
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
	void copy( const PropertyCollection & other );
	void destroy();
};

}; // namespace QTUTILS

Q_DECLARE_METATYPE(QTUTILS::PropertyCollection)

#endif //__PROPERTYCOLLECTION_H__