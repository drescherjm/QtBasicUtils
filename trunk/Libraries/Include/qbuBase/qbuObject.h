#pragma once

#ifndef QBUOBJECT_H
#define QBUOBJECT_H


#include <QObject>
#include "qbuBase/qbuMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuObject : public QObject
{
	QBU_DECLARE_SUPERCLASS(QObject);
	Q_OBJECT
public:
	explicit qbuObject(QObject* pParent = nullptr);
public:
	void		appendLastError(QString strLastError);
	void		setLastError(QString strLastError);
	QString		getLastError();
	void		prependLastError( QString strLastError );
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUOBJECT_H

