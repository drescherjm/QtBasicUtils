#pragma once

#ifndef QBULOGMODELENGINE_H
#define QBULOGMODELENGINE_H

#include <QObject>
#include <QxtLoggerEngine>
#include <qbuBase/qbuMacros.h>
#include <QDateTime>

/////////////////////////////////////////////////////////////////////////////////////////

class /*qbuLog_EXPORT*/ qbuLogModelEngine : public QObject, public QxtLoggerEngine
{
public:
	QBU_DECLARE_SUPERCLASS(QObject);
	Q_OBJECT
public:
	explicit qbuLogModelEngine(QObject *parent = 0);
	virtual  ~qbuLogModelEngine();
private:
	void	initialize();

signals:
	void	logMessage(QDateTime, quint32 level, QString strFileName, quint32 nLine, const QStringList& messages);

protected:
	 virtual void   writeFormatted(QxtLogger::LogLevel level, const QList<QVariant>& messages);
	 virtual void	initLoggerEngine();
	 virtual void	killLoggerEngine();
	 virtual bool	isInitialized() const;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBULOGMODELENGINE_H
