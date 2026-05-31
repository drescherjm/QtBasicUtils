#pragma once
#ifndef QBUUSERPROPERTY_H
#define QBUUSERPROPERTY_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "qbuBase/qbuITKIndent.h"
#include "qbuBase/qbuUpdateTracker.h"
#include <QDomElement>
#include <QObject>
#include <QSharedData>
#include <QVariant>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class qbuUserProperty : public QObject, public qbuUpdateTracker, public QSharedData {
	Q_OBJECT
public:
	qbuUserProperty();
	qbuUserProperty(const qbuUserProperty& other);
	qbuUserProperty& operator=(const qbuUserProperty& other);
	virtual ~qbuUserProperty();

public:
	virtual QString toXML(bool bMakeRoot = true, qbuITKIndent indent = qbuITKIndent()) = 0;
	virtual bool    fromXML(QString strXML)                                            = 0;
	virtual bool    fromXML(QDomElement& domElem)                                      = 0;
	virtual bool    Load(QString strFile)                                              = 0;
	virtual bool    Save(QString strFile)                                              = 0;

private:
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Q_DECLARE_METATYPE(UserProperty);
Q_DECLARE_METATYPE(qbuUserProperty*);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUUSERPROPERTY_H


