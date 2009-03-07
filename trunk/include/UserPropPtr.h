#ifndef __USERPROPPTR_H__
#define __USERPROPPTR_H__

#include <QObject>
#include <QVariant>
#include <QDomElement>
#include <QExplicitlySharedDataPointer>

namespace QTUTILS {

class UserProperty;

/////////////////////////////////////////////////////////////////////////////////////////

class UserPropPtr : public QObject
{
Q_OBJECT
public:
	UserPropPtr();
	UserPropPtr(UserProperty* pProp);
	UserPropPtr(const UserPropPtr & other);
	UserPropPtr& operator=(const UserPropPtr & other);
public:
	bool				isNull();
	QString				toXML(bool bMakeRoot = true);
	bool				fromXML(QString strXML);
	bool				fromXML(QDomElement & domElem);
	UserProperty*		data();
	const UserProperty*	data() const;
	QString				typeName() const; 
private:
	void		copy(const UserPropPtr & other);
	void		destroy();
protected:
	QExplicitlySharedDataPointer<UserProperty>	m_pProp;
};

}; //namespace QTUTILS

/////////////////////////////////////////////////////////////////////////////////////////

Q_DECLARE_METATYPE(QTUTILS::UserPropPtr)

#endif //__USERPROPPTR_H__