#ifndef __PROPERTY_H__
#define __PROPERTY_H__

//#include "xrvariant.h"
#include <QVariant>
#include <QObject>

namespace QTUTILS {

class Property : public QObject
{
	Q_OBJECT
public:
	Property();
	virtual ~Property();
	Property(const Property & other);
	Property& operator=(const Property & other);
public:
	QVariant&	GetData();
	QString		toXML();
private:
	void copy( const Property & other );
	void destroy();
protected:
	QVariant	m_vt;
};

}; // namespace QTUTILS

Q_DECLARE_METATYPE(QTUTILS::Property);

#endif //__PROPERTY_H__