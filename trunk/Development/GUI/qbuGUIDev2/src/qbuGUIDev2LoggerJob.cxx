#include "qbuGUIDev2LoggerJob.h"
#include <QEventLoop>
#include <QxtLogger>
#include "qbuLog\qbuLog.h"

/////////////////////////////////////////////////////////////////////////////////////////

QxtLogger::LogLevel generateRandomLogLevel();
QString generateInfoMessage();

std::atomic<bool> qbuGUIDev2LoggerJob::g_strStartTimer{ true };

/////////////////////////////////////////////////////////////////////////////////////////

void qbuGUIDev2LoggerJob::stopJob()
{
    m_timer.stop();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuGUIDev2LoggerJob::qbuGUIDev2LoggerJob()
{

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(generateLogDataTimer()));
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuGUIDev2LoggerJob::run()
{

    m_timer.start(500);

    QEventLoop loop;

    loop.exec();
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuGUIDev2LoggerJob::generateLogDataTimer()
{

    QxtLogger::LogLevel level = generateRandomLogLevel();

    static int i = 0;

    i++;

    QString strMsg = QString("Thread Message %1: - ").arg(i);

    switch (level) {
    case QxtLogger::InfoLevel:
        QLOG_INFO() << strMsg << generateInfoMessage();
        break;
    case QxtLogger::CriticalLevel:
        QLOG_CRIT() << strMsg << "Something really bad happened!" << "Should I be worried?";
        break;
    case QxtLogger::WarningLevel:
        QLOG_WARN() << strMsg << "What is this warning about?";
        break;
    case QxtLogger::TraceLevel:
        QLOG_TRACE() << strMsg << "John was debugging!";
        break;
    case QxtLogger::ErrorLevel:
        QLOG_ERROR() << strMsg << "Some type of error occurred.";
        break;
    case QxtLogger::DebugLevel:
        QLOG_DEBUG() << strMsg << "John was debugging!" << "What is the difference between TRACE and DEBUG again?";
        break;
    case QxtLogger::WriteLevel:
        QLOG_WRITE() << strMsg << "Lets write something" << "I don't understand the randomization here!";
        break;
    case QxtLogger::FatalLevel:
        QLOG_FATAL() << strMsg << "Should we exit the program?"
            << "I don't know"
            << "Lets generate some more data instead."
            << "Why should I generate data if there is a FATAL error?"
            << "I don't know but keep going.";
        break;
    default:
        qxtLog->log(level, QVariantList() << strMsg << "What is this!" << "Level=" << level);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////\
