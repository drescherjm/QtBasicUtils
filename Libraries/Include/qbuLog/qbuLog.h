#pragma once

#ifndef QBULOG_H
#define QBULOG_H

//#include "qbuLogLibraryDefines.h"

#define QBULOG_DATABASE_TYPE "DATABASE"

#include <QString>
#include <QxtLogger>
#include <cassert>

/////////////////////////////////////////////////////////////////////////////////////////

QString logFileName(QString strFile, int nLine);

#define QLOG_WARN_ASSERT() assert(false); qxtLog->warning() << logFileName(__FILE__,__LINE__)
#define QLOG_WARN() qxtLog->warning() << logFileName(__FILE__,__LINE__)
#define QLOG_INFO() qxtLog->info() << logFileName(__FILE__,__LINE__)
#define QLOG_CRIT() qxtLog->critical() << logFileName(__FILE__,__LINE__)
#define QLOG_FATAL() qxtLog->fatal() << logFileName(__FILE__,__LINE__)
#define QLOG_ERROR() qxtLog->error() << logFileName(__FILE__,__LINE__)
#define QLOG_TRACE() qxtLog->trace() << logFileName(__FILE__,__LINE__)
#define QLOG_WRITE() qxtLog->write() << logFileName(__FILE__,__LINE__)
#define QLOG_DEBUG() qxtLog->debug() << logFileName(__FILE__,__LINE__)
#define QLOG_DATABASE() qxtLog->write() << logFileName(__FILE__,__LINE__) << QBULOG_DATABASE_TYPE

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBULOG_H

