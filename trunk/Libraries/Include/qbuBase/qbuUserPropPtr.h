#pragma once

#ifndef QBUUSERPROPPTR_H
#define QBUUSERPROPPTR_H

#include "qbuBase/qbuUserPropery.h"
#include <QObject>
#include <QVariant>
#include <QExplicitlySharedDataPointer>

class QDomElement;

/////////////////////////////////////////////////////////////////////////////////////////

class qbuUserPropPtr : public QObject
{
Q_OBJECT
public:
        typedef QExplicitlySharedDataPointer<qbuUserProperty> SharedPtr;
public:
	qbuUserPropPtr();
	qbuUserPropPtr(qbuUserProperty* pProp, bool bAutoDelete=true);
	qbuUserPropPtr(const qbuUserPropPtr & other);
	qbuUserPropPtr& operator=(const qbuUserPropPtr & other);
	qbuUserPropPtr(SharedPtr & other);
public:
	bool					isNull() const;
	QString					toXML(bool bMakeRoot = true,qbuITKIndent indent = qbuITKIndent());
	bool					fromXML(QString strXML);
	bool					fromXML(QDomElement & domElem);
	qbuUserProperty*			data();
	SharedPtr				GetPtr();
	const qbuUserProperty*		data() const;
	QString					typeName() const; 
	bool					willAutoDelete() const;
private:
	void					copy(const qbuUserPropPtr & other);
	void					destroy();
protected:
	SharedPtr			m_pProp;
	qbuUserProperty*		m_pPropRaw;
};

/////////////////////////////////////////////////////////////////////////////////////////

Q_DECLARE_METATYPE(qbuUserPropPtr)

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUUSERPROPPTR_H
