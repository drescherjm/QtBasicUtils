#ifndef __USERPROPERY_H__
#define __USERPROPERY_H__

/////////////////////////////////////////////////////////////////////////////////////////

#include <QObject>
#include "QUpdateTracker.h"

/////////////////////////////////////////////////////////////////////////////////////////

//namespace QTUTILS {

class UserProperty : public QObject, public QTUTILS::QUpdateTracker
{
public:
	UserProperty();
	UserProperty(const UserProperty & other);
	UserProperty& operator=(const UserProperty & other);
private:
};

//}; //namespace QTUTILS
Q_DECLARE_METATYPE(UserProperty)

#endif //__USERPROPERY_H__