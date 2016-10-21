#include "qbuLogPCH.h"
#include "qbuLog/qbuLoggerModel.h"
#include <QDateTime>
#include <qxtlogger.h>
#include <deque>
#include "qbuLog/qbuLogModelEngine.h"
#include <boost/bimap/bimap.hpp>

/////////////////////////////////////////////////////////////////////////////////////////

static QString Titles[] = { "Date", "Level", "File", "Message" };
const int GRID_COLS = sizeof(Titles) / sizeof(Titles[0]);

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

	enum Cols {
		CT_DATE,
		CT_LEVEL,
		CT_FILENAME,
		CT_MESSAGE
	};

public:

	quint32 getFileNameIndex(const QString & strFileName);
	QString lookupFileNameFromIndex(quint32 nIndex) const;

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

QString qbuLoggerModel::qbuPrivate::lookupFileNameFromIndex(quint32 nIndex) const
{
	QString retVal;

	auto it = m_mapFileNames.right.find(nIndex);

	if (it != m_mapFileNames.right.end()) {
		retVal = it->get_left();
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
	data.m_nFileIndex = m_pPrivate->getFileNameIndex(strFileName);

	m_pPrivate->m_queue.emplace_back(data);
	
	endInsertRows();
}

/////////////////////////////////////////////////////////////////////////////////////////

int qbuLoggerModel::rowCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return m_pPrivate->m_queue.size();
}

/////////////////////////////////////////////////////////////////////////////////////////

int qbuLoggerModel::columnCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return GRID_COLS;
}

/////////////////////////////////////////////////////////////////////////////////////////

QVariant qbuLoggerModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
{
	Q_UNUSED(role);

	QVariant retVal;
	
	if (orientation == Qt::Horizontal) {
		if ((section >= 0) && (section < GRID_COLS)) {
			retVal = Titles[section];
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QVariant qbuLoggerModel::data(const QModelIndex &index, int role /*= Qt::DisplayRole*/) const
{
	Q_UNUSED(role);

	QVariant retVal;

	if ( (index.row() < m_pPrivate->m_queue.size()) && (index.column() < GRID_COLS)) {
		
		logData& item = m_pPrivate->m_queue[index.row()];

		switch (index.column()) {
		case qbuPrivate::CT_DATE:
			retVal = item.m_dt;
			break;
		case qbuPrivate::CT_LEVEL:
			retVal = item.m_level;
			break;
		case qbuPrivate::CT_FILENAME:
			retVal = QString("%1:%2").arg(m_pPrivate->lookupFileNameFromIndex(item.m_nFileIndex)).arg(item.m_nFileLineNumber);
			break;
		case  qbuPrivate::CT_MESSAGE:
			retVal = item.m_strMsg;
			break;
		}
	}
	
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////
