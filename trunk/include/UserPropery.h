#ifndef __USERPROPERY_H__
#define __USERPROPERY_H__

/////////////////////////////////////////////////////////////////////////////////////////

#include <QObject>
#include <QDomElement>
#include "QUpdateTracker.h"

namespace QTUTILS {

class UserProperty : public QObject, public QUpdateTracker
{
public:
	virtual QString		toXML(bool bMakeRoot = true)=0;
	virtual bool		fromXML(QString strXML)=0;
	virtual	bool		fromXML(QDomElement & domElem)=0;
};

}; //namespace QTUTILS

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__USERPROPERY_H__