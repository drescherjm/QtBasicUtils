#pragma once

#ifndef QBULOGGERWIDGET_H
#define QBULOGGERWIDGET_H

//#include "qbuLogLibraryDefines.h"
#include <QTableWidget>
#include <QxtLoggerEngine>
#include <qbuBase/qbuMacros.h>

/////////////////////////////////////////////////////////////////////////////////////////

class /*qbuLog_EXPORT*/ qbuLoggerWidget : public QTableWidget, public QxtLoggerEngine
{
public:
	QBU_DECLARE_SUPERCLASS(QTableWidget);
	Q_OBJECT
public:
	explicit qbuLoggerWidget(QWidget *parent = 0);
private:
	void	initialize();
protected:
	 virtual void   writeFormatted(QxtLogger::LogLevel level, const QList<QVariant>& messages);
	 virtual void	initLoggerEngine();
	 virtual void	killLoggerEngine();
	 virtual bool	isInitialized() const;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBULOGGERWIDGET_H

