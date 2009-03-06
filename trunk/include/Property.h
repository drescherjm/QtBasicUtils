#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#include <QVariant>
#include <QDomElement>
#include <QObject>

#include "UserPropPtr.h"

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

class Property : public QObject
{
	Q_OBJECT
public:
	Property();
	virtual ~Property();
	Property(const Property & other);
	Property& operator=(const Property & other);
public:
	const QVariant&		GetData() const;
	QVariant&			SetData(const QVariant&);
	QVariant&			SetData( const UserPropPtr & ptr);
	operator UserPropPtr() const;
public:
	QString		toXML();
	bool		fromXML(QString strXML);
	bool		fromXML(QDomElement & domElem);
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