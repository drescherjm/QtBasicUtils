#ifndef __USERPROPPTR_H__
#define __USERPROPPTR_H__

#include <QObject>
#include <QVariant>

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
protected:
	UserProperty*		m_pProp;
};

}; //namespace QTUTILS

/////////////////////////////////////////////////////////////////////////////////////////

Q_DECLARE_METATYPE(QTUTILS::UserPropPtr)

#endif //__USERPROPPTR_H__