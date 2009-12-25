#ifndef __PROPERTYMAP_H__
#define __PROPERTYMAP_H__

#include "Property.h"
#include "UserPropery.h"
#include <QMap>

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

/**
 * This class defines a map of Properties. The key to the map here is the name of the property  
 * which is added in Property::setObjectName.
 *
 * \sa Property, PropertyList
 */

class PropertyMap : public UserProperty
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
	iterator		begin() const;
	iterator		end() const;
	iterator		find(QString strName) const;
	void			clear();
	bool			empty() const;
public:
	void			setCaseSensitivity ( Qt::CaseSensitivity cs );
	QString			toXML(bool bMakeRoot = true);
	bool			fromXML(QString strXML);
	bool			fromXML(QDomElement & domElem);
	void			CopyProperty(QString strOldName, const PropertyMap & other, QString strNewName="");
	bool			RemoveProperty(QString strName);
	bool			RenameProperty(QString strOldName,QString strNewName);
	void			addProperties(PropertyMap * other);

	bool			Load(QString strFile);
	bool			Save(QString strFile);
protected:
	Map				m_mapProps;
	Qt::CaseSensitivity m_cs;
protected:
	QString			CleanUpName(QString strName) const;
private:
	void			copy( const PropertyMap & other );
	void			destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////

inline void PropertyMap::clear()
{
	destroy();
}

/////////////////////////////////////////////////////////////////////////////////////////

inline bool PropertyMap::empty() const
{
	return m_mapProps.empty();
}

/////////////////////////////////////////////////////////////////////////////////////////

}; // namespace QTUTILS

/////////////////////////////////////////////////////////////////////////////////////////

Q_DECLARE_METATYPE(QTUTILS::PropertyMap)
Q_DECLARE_METATYPE(QTUTILS::PropertyMap*)

#endif //__PROPERTYMAP_H__
