#pragma once

#ifndef QBULOG_H
#define QBULOG_H

//#include "qbuLogLibraryDefines.h"

#define QBULOG_DATABASE_TYPE "DATABASE"

#include <QString>
#include <QxtLogger>
#include <cassert>

bool isDebuggerPresent();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#define DEBUG_BREAK()                                                                                                  \
	do {                                                                                                               \
		if (isDebuggerPresent())                                                                                       \
			__debugbreak();                                                                                            \
	} while (0)
#elif defined(__clang__)
#define DEBUG_BREAK()                                                                                                  \
	do {                                                                                                               \
		if (isDebuggerPresent())                                                                                       \
			__builtin_debugtrap();                                                                                     \
	} while (0)
#elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
#define DEBUG_BREAK()                                                                                                  \
	do {                                                                                                               \
		if (isDebuggerPresent())                                                                                       \
			__asm__ volatile("int $0x03");                                                                             \
	} while (0)
#elif defined(__GNUC__) && defined(__aarch64__)
#define DEBUG_BREAK()                                                                                                  \
	do {                                                                                                               \
		if (isDebuggerPresent())                                                                                       \
			__asm__ volatile("brk #0");                                                                                \
	} while (0)
#elif defined(__GNUC__) && defined(__arm__)
#define DEBUG_BREAK()                                                                                                  \
	do {                                                                                                               \
		if (isDebuggerPresent())                                                                                       \
			__asm__ volatile("bkpt #0");                                                                               \
	} while (0)
#else
#include <csignal>
#define DEBUG_BREAK()                                                                                                  \
	do {                                                                                                               \
		if (isDebuggerPresent())                                                                                       \
			raise(SIGTRAP);                                                                                            \
	} while (0)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QString logFileName(QString strFile, int nLine);

#define QLOG_WARN_ASSERT() assert(false); qxtLog->warning() << logFileName(__FILE__,__LINE__)
#define QLOG_WARN_BREAK()  DEBUG_BREAK(); qxtLog->warning() << logFileName(__FILE__,__LINE__)
#define QLOG_WARN() qxtLog->warning() << logFileName(__FILE__,__LINE__)
#define QLOG_INFO() qxtLog->info() << logFileName(__FILE__,__LINE__)
#define QLOG_CRIT() qxtLog->critical() << logFileName(__FILE__,__LINE__)
#define QLOG_FATAL() qxtLog->fatal() << logFileName(__FILE__,__LINE__)
#define QLOG_ERROR() qxtLog->error() << logFileName(__FILE__,__LINE__)
#define QLOG_TRACE() qxtLog->trace() << logFileName(__FILE__,__LINE__)
#define QLOG_WRITE() qxtLog->write() << logFileName(__FILE__,__LINE__)
#define QLOG_DEBUG() qxtLog->debug() << logFileName(__FILE__,__LINE__)
#define QLOG_DATABASE() qxtLog->write() << logFileName(__FILE__,__LINE__) << QBULOG_DATABASE_TYPE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // QBULOG_H

