#pragma once

#ifndef __QBUPROPERTY_H__
#define __QBUPROPERTY_H__

#include <QVariant>
#include <QDomElement>
#include <QObject>

#include "qbuBase/qbuUserPropPtr.h"
#include "qbuBase/qbuUpdateTracker.h"
#include <iosfwd>
#include "qbuBase/qbuITKIndent.h"
#include <QTextStream>

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	A Property is an extended QVariant that allows for importing and exporting to and 
 *  from XML. It's most useful with the two collection classes (PropertyMap and PropertyList) 
 *  that are designed to hold 0 or more Properties.
 *
 *  \sa PropertyMap, PropertyList
 */

class qbuProperty : public QObject, public qbuUpdateTracker
{
	Q_OBJECT
public:
	qbuProperty();
	virtual ~qbuProperty();
	qbuProperty(const qbuProperty & other);
	qbuProperty& operator=(const qbuProperty & other);

	bool	  operator==(const qbuProperty & other) const;
public:
	const QVariant&		GetData() const;
	QVariant&			SetData(const QVariant&);
	QVariant&			SetData( const qbuUserPropPtr & ptr);
	operator qbuUserPropPtr() const;
public:
	QString		toXML(qbuITKIndent indent = qbuITKIndent());
	bool		fromXML(QString strXML);
	bool		fromXML(QDomElement & domElem);
	bool		Load(QString strFile);
	bool		Save(QString strFile);
	void		Print(std::ostream & st, qbuITKIndent indent = qbuITKIndent());
	void		Print(QTextStream & st, qbuITKIndent indent = qbuITKIndent());

private:
	void		copy( const qbuProperty & other );
	void		destroy();
protected:
	QVariant	m_vt;
};

/////////////////////////////////////////////////////////////////////////////////////////

Q_DECLARE_METATYPE(qbuProperty);

/////////////////////////////////////////////////////////////////////////////////////////

#endif // __QBUPROPERTY_H__

