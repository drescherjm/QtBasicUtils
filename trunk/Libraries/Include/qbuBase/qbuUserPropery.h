#pragma once

#ifndef __QBUUSERPROPERY_H__
#define __QBUUSERPROPERY_H__

/////////////////////////////////////////////////////////////////////////////////////////

#include "qbuBase/qbuUpdateTracker.h"
#include <QObject>
#include <QVariant>
#include <QDomElement>
#include <QSharedData>
#include "qbuBase/qbuITKIndent.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuUserProperty : public QObject , public qbuUpdateTracker, public QSharedData
{
	Q_OBJECT
public:
	qbuUserProperty();
	qbuUserProperty(const qbuUserProperty & other);
	qbuUserProperty& operator=(const qbuUserProperty & other);
public:
	virtual QString		toXML(bool bMakeRoot = true,qbuITKIndent indent = qbuITKIndent())=0;
	virtual bool		fromXML(QString strXML)=0;
	virtual bool		fromXML(QDomElement & domElem)=0;
	virtual bool		Load(QString strFile)=0;
	virtual bool		Save(QString strFile)=0;
private:
};

/////////////////////////////////////////////////////////////////////////////////////////

//Q_DECLARE_METATYPE(UserProperty);
Q_DECLARE_METATYPE(qbuUserProperty*);

/////////////////////////////////////////////////////////////////////////////////////////

#endif // __QBUUSERPROPERY_H__
