#pragma once

#ifndef QBUWIDGETENABLEDSIGNALEMITTER_H
#define QBUWIDGETENABLEDSIGNALEMITTER_H

#include <QObject>
#include "qbuBase/qbuMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuWidgetEnabledSignalEmitter : public QObject
{
	QBU_DECLARE_SUPERCLASS(QObject);
	Q_OBJECT
public:
	explicit qbuWidgetEnabledSignalEmitter(QObject* pParent = nullptr);

signals:
	void	enabledChange(bool bEnable);

protected:
	bool	eventFilter(QObject* obj, QEvent* event) override;

};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUWIDGETENABLEDSIGNALEMITTER_H
