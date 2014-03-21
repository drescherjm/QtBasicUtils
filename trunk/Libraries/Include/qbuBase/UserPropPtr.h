#ifndef __USERPROPPTR_H__
#define __USERPROPPTR_H__

#include "UserPropery.h"
#include <QObject>
#include <QVariant>
#include <QDomElement>
#include <QExplicitlySharedDataPointer>

namespace QTUTILS {



/////////////////////////////////////////////////////////////////////////////////////////

class UserPropPtr : public QObject
{
Q_OBJECT
public:
        typedef QExplicitlySharedDataPointer<UserProperty> SharedPtr;
public:
	UserPropPtr();
	UserPropPtr(UserProperty* pProp, bool bAutoDelete=true);
	UserPropPtr(const UserPropPtr & other);
	UserPropPtr& operator=(const UserPropPtr & other);
	UserPropPtr(SharedPtr & other);
public:
	bool					isNull() const;
	QString					toXML(bool bMakeRoot = true,qbuITKIndent indent = qbuITKIndent());
	bool					fromXML(QString strXML);
	bool					fromXML(QDomElement & domElem);
	UserProperty*			data();
	SharedPtr				GetPtr();
	const UserProperty*		data() const;
	QString					typeName() const; 
	bool					willAutoDelete() const;
private:
	void					copy(const UserPropPtr & other);
	void					destroy();
protected:
	SharedPtr			m_pProp;
	UserProperty*		m_pPropRaw;
};

}; //namespace QTUTILS

/////////////////////////////////////////////////////////////////////////////////////////

Q_DECLARE_METATYPE(UserPropPtr)

#endif //__USERPROPPTR_H__
