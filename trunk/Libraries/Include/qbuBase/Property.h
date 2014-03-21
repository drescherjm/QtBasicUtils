#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#include <QVariant>
#include <QDomElement>
#include <QObject>

#include "UserPropPtr.h"
#include "QUpdateTracker.h"
#include <iosfwd>
#include "qbuITKIndent.h"
#include <QTextStream>

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	A Property is an extended QVariant that allows for importing and exporting to and 
 *  from XML. It's most useful with the two collection classes (PropertyMap and PropertyList) 
 *  that are designed to hold 0 or more Properties.
 *
 *  \sa PropertyMap, PropertyList
 */

class Property : public QObject, public QTUTILS::QUpdateTracker
{
	Q_OBJECT
public:
	Property();
	virtual ~Property();
	Property(const Property & other);
	Property& operator=(const Property & other);

	bool	  operator==(const Property & other) const;
public:
	const QVariant&		GetData() const;
	QVariant&			SetData(const QVariant&);
	QVariant&			SetData( const UserPropPtr & ptr);
	operator UserPropPtr() const;
public:
	QString		toXML(qbuITKIndent indent = qbuITKIndent());
	bool		fromXML(QString strXML);
	bool		fromXML(QDomElement & domElem);
	bool		Load(QString strFile);
	bool		Save(QString strFile);
	void		Print(std::ostream & st, qbuITKIndent indent = qbuITKIndent());
	void		Print(QTextStream & st, qbuITKIndent indent = qbuITKIndent());

private:
	void		copy( const Property & other );
	void		destroy();
protected:
	QVariant	m_vt;
};

}; // namespace QTUTILS

/////////////////////////////////////////////////////////////////////////////////////////

Q_DECLARE_METATYPE(QTUTILS::Property);

#endif //__PROPERTY_H__
