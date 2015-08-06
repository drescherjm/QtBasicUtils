#pragma once

#ifndef QBUFILELOGGERENGINE_H
#define QBUFILELOGGERENGINE_H

#include <QxtBasicFileLoggerEngine>
#include <qbuBase\qbuMacros.h>

/////////////////////////////////////////////////////////////////////////////////////////

class qbuFileLoggerEngine : public QxtBasicFileLoggerEngine
{
	QBU_DECLARE_SUPERCLASS(QxtBasicFileLoggerEngine);
public:
	qbuFileLoggerEngine(const QString &fileName = QString());

protected:
	virtual void writeToFile(const QString &level, const QVariantList &messages);
private:	
	bool	containsNewLine(const QVariant & vt) const;

	QVariantList splitOutNewLines(const QVariant & vt) const;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUFILELOGGERENGINE_H

