#pragma once

#ifndef QBULOGGERWIDGET2_H
#define QBULOGGERWIDGET2_H

#include <QWidget>
#include "qbuLog/ui_qbuLoggerWidget2.h"
#include <qbuBase/qbuMacros.h>

class QxtLoggerEngine;

/////////////////////////////////////////////////////////////////////////////////////////

class /*qbuLog_EXPORT*/ qbuLoggerWidget2 : public QWidget,
    public Ui::qbuLoggerWidget2
{
public:
    QBU_DECLARE_SUPERCLASS(QWidget);
	Q_OBJECT
public:
	explicit qbuLoggerWidget2(QWidget *parent = 0);

public:
    void	initialize();

protected:
	void	rowsInserted(const QModelIndex &parent, int start, int end);

public:
	QxtLoggerEngine* getLoggerEngine() const;

private:
	bool	m_bFirst;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBULOGGERWIDGET2_H
