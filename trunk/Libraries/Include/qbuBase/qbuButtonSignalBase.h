#pragma once

#ifndef QBUBUTTONSIGNALBASE_H
#define QBUBUTTONSIGNALBASE_H

#include <QObject>
#include <qbuBase/qbuMacros.h>
#include "qbuBase/qbuBaseLibraryDefines.h"
#include <memory>

class QAbstractButton;

/////////////////////////////////////////////////////////////////////////////////////////

class qbuBase_EXPORT qbuButtonSignalBase : public QObject
{
	Q_OBJECT
	QBU_DECLARE_SUPERCLASS(QObject)
public:
	explicit qbuButtonSignalBase(QObject* pParent);

public:
	virtual bool isChecked() = 0;

signals:
	void toggled(bool);

public slots:
	void sendValue();
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUBUTTONSIGNALBASE_H
