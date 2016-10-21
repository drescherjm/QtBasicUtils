#include "qbuLogPCH.h"
#include "qbuLog/qbuLoggerModel.h"
#include <QDateTime>
#include <qxtlogger.h>
#include <deque>

/////////////////////////////////////////////////////////////////////////////////////////

struct logData
{
    QDateTime               m_dt;
    QxtLogger::LogLevel     m_level;
    quint32                 m_nFileIndex;
    quint32                 m_nFileLineNumber;
    QString                 m_strMsg;
};

/////////////////////////////////////////////////////////////////////////////////////////

class qbuLoggerModel::qbuPrivate
{
public:
    typedef QHash<QString, quint32>  FileNameHash;
    typedef std::deque<logData>      LogQueue;
public:
    LogQueue    m_queue;

};

/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerModel::qbuLoggerModel(QObject* pParent) : m_pPrivate(std::make_unique<qbuPrivate>())
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerModel::~qbuLoggerModel()
{

}

/////////////////////////////////////////////////////////////////////////////////////////
