#ifndef __USERPROPERY_H__
#define __USERPROPERY_H__

/////////////////////////////////////////////////////////////////////////////////////////

#include "QUpdateTracker.h"
#include <QObject>
#include <QVariant>
#include <QDomElement>
#include <QSharedData>

/////////////////////////////////////////////////////////////////////////////////////////

namespace QTUTILS {

class UserProperty : public QObject , public QTUTILS::QUpdateTracker, public QSharedData
{
	Q_OBJECT
public:
	UserProperty();
	UserProperty(const UserProperty & other);
	UserProperty& operator=(const UserProperty & other);
public:
	virtual QString		toXML(bool bMakeRoot = true)=0;
	virtual bool		fromXML(QString strXML)=0;
	virtual bool		fromXML(QDomElement & domElem)=0;
	virtual bool		Load(QString strFile)=0;
	virtual bool		Save(QString strFile)=0;
private:
};

}; //namespace QTUTILS

//Q_DECLARE_METATYPE(QTUTILS::UserProperty);
Q_DECLARE_METATYPE(QTUTILS::UserProperty*);

#endif //__USERPROPERY_H__
