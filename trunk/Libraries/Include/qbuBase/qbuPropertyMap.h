#pragma once

#ifndef __QBUPROPERTYMAP_H__
#define __QBUPROPERTYMAP_H__

#include "qbuBase/qbuProperty.h"
#include "qbuBase/qbuUserPropery.h"
#include <QMap>

/////////////////////////////////////////////////////////////////////////////////////////

/**
 * This class defines a map of Properties. The key to the map here is the name of the property  
 * which is added in Property::setObjectName.
 *
 * \sa Property, PropertyList
 */

class qbuPropertyMap : public qbuUserProperty
{
	Q_OBJECT
public:
	qbuPropertyMap();
	virtual ~qbuPropertyMap();
	qbuPropertyMap(const qbuPropertyMap & other);
	qbuPropertyMap& operator=(const qbuPropertyMap & other);
	bool operator==(const qbuPropertyMap & other) const;
public:
	typedef QMap<QString,qbuProperty*> Map;
	typedef Map::iterator iterator;
	typedef Map::const_iterator const_iterator;

	iterator		insert(qbuProperty* pProp);
	iterator		insert(qbuProperty & prop);
	iterator		begin();
	iterator		end();
	const_iterator	begin() const;
	const_iterator	end() const;
	iterator		find(QString strName);
	const_iterator	find(QString strName) const;
	void			clear();
	bool			empty() const;
	int				size() const;
public:
	void			setCaseSensitivity ( Qt::CaseSensitivity cs );
	QString			toXML(bool bMakeRoot = true,qbuITKIndent indent = qbuITKIndent());
	bool			fromXML(QString strXML);
	bool			fromXML(QDomElement & domElem);
	void			CopyProperty(QString strOldName, const qbuPropertyMap & other, QString strNewName="");
	void			MoveProperty(QString strOldName, qbuPropertyMap & other, QString strNewName="");
	bool			EqualSubset(QStringList lstPropNames, const qbuPropertyMap & other);
	bool			RemoveProperty(QString strName);
	bool			RenameProperty(QString strOldName,QString strNewName);
	

	bool			Load(QString strFile);
	bool			Save(QString strFile);
	void			Print(std::ostream & st, qbuITKIndent indent = qbuITKIndent());
	void			Print(QTextStream & st, qbuITKIndent indent = qbuITKIndent());
public:
	virtual	void	addProperties(qbuPropertyMap * other);	
	virtual void	addProperties(const qbuPropertyMap* other);
	virtual	int		RemoveProperties(QStringList lstProperties);

protected:
	virtual void	propertyInserted(qbuProperty * pProp);

protected:
	Map				m_mapProps;
	Qt::CaseSensitivity m_cs;
protected:
	QString			CleanUpName(QString strName) const;
private:
	void			copy( const qbuPropertyMap & other );
	void			destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This member function removes all items from the PropertyMap.
 */

inline void qbuPropertyMap::clear()
{
	destroy();
}

/////////////////////////////////////////////////////////////////////////////////////////

inline bool qbuPropertyMap::empty() const
{
	return m_mapProps.empty();
}

/////////////////////////////////////////////////////////////////////////////////////////

Q_DECLARE_METATYPE(qbuPropertyMap)
Q_DECLARE_METATYPE(qbuPropertyMap*)

/////////////////////////////////////////////////////////////////////////////////////////

#endif // __QBUPROPERTYMAP_H__
