#pragma once

#ifndef QBUGUIDEV2LOGGERJOB_CXX
#define QBUGUIDEV2LOGGERJOB_CXX

#include <QRunnable>
#include <QObject>
#include <atomic>
#include <QTimer>

/////////////////////////////////////////////////////////////////////////////////////////

class qbuGUIDev2LoggerJob : public QObject, public QRunnable
{
    Q_OBJECT
public:
    qbuGUIDev2LoggerJob();
	virtual ~qbuGUIDev2LoggerJob();

public:
    void run();

public slots:
    void    stopJob();
    void    generateLogDataTimer();

signals:
    void    quit();

public:
    static std::atomic<bool> g_strStartTimer;

    QTimer*  m_pTimer;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUGUIDEV2LOGGERJOB_CXX
