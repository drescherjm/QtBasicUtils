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
	iterator		find(QString strName);
public:
	void			setCaseSensitivity ( Qt::CaseSensitivity cs );
	QString			toXML();
	void			CopyProperty(QString strName, PropertyMap & other);
	void			RemoveProperty(QString strName);
	void			addProperties(PropertyMap * other);
protected:
	Map				m_mapProps;
	Qt::CaseSensitivity m_cs;
protected:
	QString			CleanUpName(QString strName);
private:
	void			copy( const PropertyMap & other );
	void			destroy();
};

}; // namespace QTUTILS

Q_DECLARE_METATYPE(QTUTILS::PropertyMap)

#endif //__PROPERTYMAP_H__