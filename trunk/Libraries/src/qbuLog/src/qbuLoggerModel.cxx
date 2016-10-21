#include "qbuLogPCH.h"
#include "qbuLog/qbuLoggerModel.h"
#include <QDateTime>
#include <qxtlogger.h>
#include <deque>
#include "qbuLog/qbuLogModelEngine.h"
#include <boost/bimap/bimap.hpp>

/////////////////////////////////////////////////////////////////////////////////////////

struct logData
{
    QDateTime               m_dt;
    QxtLogger::LogLevel     m_level;
    quint32                 m_nFileIndex;
    quint32                 m_nFileLineNumber;
	QStringList             m_strMsg;
};

/////////////////////////////////////////////////////////////////////////////////////////

class qbuLoggerModel::qbuPrivate
{
public:
	typedef boost::bimaps::bimap<QString, int>	FileNameMap;
	typedef FileNameMap::value_type				FileNameMapEntry;
    typedef std::deque<logData>					LogQueue;

public:

	quint32 getFileNameIndex(const QString & strFileName);

public:
    LogQueue				m_queue;
	qbuLogModelEngine		m_engine;
	FileNameMap				m_mapFileNames;
};

/////////////////////////////////////////////////////////////////////////////////////////

quint32 qbuLoggerModel::qbuPrivate::getFileNameIndex(const QString & strFileName)
{
	quint32 retVal;
 	auto it =m_mapFileNames.left.find(strFileName);

	if (it != m_mapFileNames.left.end()) {
		retVal = it->get_right();
	}
	else {
		retVal = m_mapFileNames.size();

		m_mapFileNames.insert(FileNameMapEntry(strFileName, retVal));
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerModel::qbuLoggerModel(QObject* pParent) : m_pPrivate(std::make_unique<qbuPrivate>())
{
	connect(&m_pPrivate->m_engine, SIGNAL(logMessage(QDateTime,QxtLogger::LogLevel, QString, quint32, const QStringList&)), 
		this, SLOT(logMessage(QDateTime, quint32, QString, quint32 nLine, const QStringList&)));
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerModel::~qbuLoggerModel()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerModel::logMessage(QDateTime dt, quint32 level, QString strFileName, quint32 nLine, const QStringList& messages)
{
	int nIndex = m_pPrivate->m_queue.size();

	beginInsertRows(QModelIndex(), nIndex, nIndex);

	logData data;
	data.m_dt = dt;
	data.m_level = static_cast<QxtLogger::LogLevel>(level);
	data.m_nFileLineNumber = nLine;
	data.m_strMsg = messages;
	
	endInsertRows();
}

/////////////////////////////////////////////////////////////////////////////////////////
