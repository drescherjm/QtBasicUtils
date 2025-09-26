#pragma once

#ifndef QBUFILTEREDFILELOGGERENGINE_H
#define QBUFILTEREDFILELOGGERENGINE_H

//#include "qbuLogLibraryDefines.h"

#include <qbuLog/qbuFileLoggerEngine.h>
#include <qbuBase/qbuMacros.h>

/////////////////////////////////////////////////////////////////////////////////////////

class /*qbuLog_EXPORT*/ qbuFilteredFileLoggerEngine : public qbuFileLoggerEngine
{
	QBU_DECLARE_SUPERCLASS(qbuFileLoggerEngine);
public:
	qbuFilteredFileLoggerEngine(const QString &fileName = QString());

public:
	bool	addFilters(int nLevel, QStringList lstFilters);

protected:
	virtual void writeToFile(const QString &level, const QVariantList &messages);
private:
	typedef QMap<int, QStringList> FilterMap;
	FilterMap	m_filterMap;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUFILTEREDFILELOGGERENGINE_H
