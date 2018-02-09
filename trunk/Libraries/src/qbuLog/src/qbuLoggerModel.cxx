#include "qbuLogPCH.h"
#include "qbuLog/qbuLoggerModel.h"

#include <qxtlogger.h>

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

typedef std::deque<logData>		LogQueue;

/////////////////////////////////////////////////////////////////////////////////////////

struct BufferUpdates
{
	LogQueue				m_holdQueue;
	QDateTime				m_dtLastSync;
	QTimer					m_timer;
};

/////////////////////////////////////////////////////////////////////////////////////////

class qbuLoggerModel::qbuPrivate
{
public:
	qbuPrivate();
public:
	typedef boost::bimaps::bimap<QString, int>	FileNameMap;
	typedef FileNameMap::value_type				FileNameMapEntry;
    

public:
	quint32 getFileNameIndex(const QString & strFileName);
	QString lookupFileNameFromIndex(quint32 nIndex) const;


    bool        reachedRecordLimit() const;
    bool        calculateRowsToRemove(LogQueue::const_iterator & start, LogQueue::const_iterator & finish, 
        quint32 & nRemove) const;
    quint32     resizeQueue(qbuLoggerModel* pPublic);


	bool		isTimerStarted();
	void		startTimerIfNeeded(qbuLoggerModel* pPublic, int nIndex, QDateTime & dtMsg);
	void		setupTimer(qbuLoggerModel* pPublic);

    bool        getLogLevel(const QModelIndex & index, QxtLogger::LogLevel & level) const;
 
public:
    LogQueue				m_queue;
	qbuLogModelEngine*		m_pEngine;
	FileNameMap				m_mapFileNames;
    quint32                 m_nRecordLimit;
	BufferUpdates			m_buffer;		
	uint8_t					m_nUpdateDelay;
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerModel::qbuPrivate::qbuPrivate() : m_pEngine{ new qbuLogModelEngine },
m_nRecordLimit{ 100 * 1024 }, m_nUpdateDelay{5}
{
    // NOTE: Allocate but don't free the logger engine. QxtLog will take ownership!
}

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

bool qbuLoggerModel::qbuPrivate::reachedRecordLimit() const
{
    return ((m_nRecordLimit > 0) && (m_queue.size() > m_nRecordLimit));
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuLoggerModel::qbuPrivate::calculateRowsToRemove(LogQueue::const_iterator & start, LogQueue::const_iterator & finish, quint32 & nRemove) const
{
    bool retVal = reachedRecordLimit();
    if (retVal) {
        nRemove = m_nRecordLimit * 0.10f;

        retVal = (nRemove > 0);
        if (retVal) {
            start = m_queue.begin();
            finish = m_queue.begin() + nRemove;
        }
    }
    return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

quint32 qbuLoggerModel::qbuPrivate::resizeQueue(qbuLoggerModel* pPublic)
{
    quint32 retVal{};

    LogQueue::const_iterator start, finish;

    if (calculateRowsToRemove(start, finish, retVal)) {
        pPublic->beginRemoveRows(QModelIndex(), 0, retVal - 1);

        m_queue.erase(start, finish);

        size_t nSize = m_queue.size();

        pPublic->endRemoveRows();
    }

    return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuLoggerModel::qbuPrivate::isTimerStarted()
{
	return m_buffer.m_timer.isActive();
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerModel::qbuPrivate::startTimerIfNeeded(qbuLoggerModel* pPublic,int nIndex, QDateTime & dtMsg)
{
	if (!isTimerStarted()) {
		m_buffer.m_dtLastSync = dtMsg;
		m_buffer.m_timer.start();
	}
	else if (m_buffer.m_dtLastSync.secsTo(dtMsg) > m_nUpdateDelay) {
		pPublic->synchronize();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerModel::qbuPrivate::setupTimer(qbuLoggerModel* pPublic)
{
	m_buffer.m_timer.setInterval(m_nUpdateDelay * 1000);
	m_buffer.m_timer.setSingleShot(true);
	QObject::connect(&m_buffer.m_timer, SIGNAL(timeout()), pPublic, SLOT(synchronize()));
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuLoggerModel::qbuPrivate::getLogLevel(const QModelIndex & index, QxtLogger::LogLevel & level) const
{
    bool retVal{ ((index.row() < m_queue.size()) && (index.column() < GRID_COLS)) };
    if (retVal) {

        const logData& item = m_queue[index.row()];

        level = item.m_level;

    }
    return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerModel::qbuLoggerModel(QObject* pParent) : m_pPrivate(std::make_unique<qbuPrivate>())
{
	connect(m_pPrivate->m_pEngine, SIGNAL(logMessage(QDateTime, quint32, QString, quint32, const QStringList&)),
		this, SLOT(logMessage(QDateTime, quint32, QString, quint32, const QStringList&)));

	m_pPrivate->setupTimer(this);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerModel::~qbuLoggerModel()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerModel::logMessage(QDateTime dt, quint32 level, QString strFileName, quint32 nLine, const QStringList& messages)
{
	int nIndex = m_pPrivate->m_queue.size();
	
	logData data;
	data.m_dt = dt;
	data.m_level = static_cast<QxtLogger::LogLevel>(level);
	data.m_nFileLineNumber = nLine;
	data.m_strMsg = messages;
	data.m_nFileIndex = m_pPrivate->getFileNameIndex(strFileName);

	m_pPrivate->m_buffer.m_holdQueue.emplace_back(data);

	m_pPrivate->startTimerIfNeeded(this,nIndex, dt);
	
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerModel::synchronize()
{
	int nQueueSize = m_pPrivate->m_buffer.m_holdQueue.size();
	if (nQueueSize > 0) {

		int nIndex = m_pPrivate->m_queue.size();
		int nQueueIndex = nIndex + nQueueSize - 1;
		
		beginInsertRows(QModelIndex(), nIndex, nQueueIndex);

		std::move(begin(m_pPrivate->m_buffer.m_holdQueue), end(m_pPrivate->m_buffer.m_holdQueue), 
			std::back_inserter(m_pPrivate->m_queue));

        m_pPrivate->m_buffer.m_holdQueue.clear();

		m_pPrivate->m_buffer.m_dtLastSync = m_pPrivate->m_queue[nQueueIndex].m_dt;

		endInsertRows();

        emit handleRecordLimit();
	}

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
	QVariant retVal;
	if ((orientation == Qt::Horizontal) && (section >= 0) && (section < GRID_COLS)) {
		if (role == Qt::DisplayRole) {
			retVal = Titles[section];
		}
		else if (role == Qt::SizeHintRole) {
			switch (section)
			{
			case CT_DATE:
				retVal = QSize(100, 20);
				break;
			case CT_LEVEL:
				retVal = QSize(75, 20);
				break;
			default:
				break;
			}
		}
	}
    else {
        retVal = Superclass::headerData(section, orientation, role);
    }

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QVariant qbuLoggerModel::data(const QModelIndex &index, int role /*= Qt::DisplayRole*/) const
{
	QVariant retVal;
    if (role == Qt::UserRole) {
        if (index.column() == CT_LEVEL) {
            if ((index.row() < m_pPrivate->m_queue.size()) && (index.column() < GRID_COLS)) {

                logData& item = m_pPrivate->m_queue[index.row()];

                retVal = item.m_level;
            }
        }
        else {
            retVal = data(index, Qt::DisplayRole);
        }
    }
    else
	if (role == Qt::DisplayRole) {
		if ((index.row() < m_pPrivate->m_queue.size()) && (index.column() < GRID_COLS)) {

			logData& item = m_pPrivate->m_queue[index.row()];

			switch (index.column()) {
			case CT_DATE:
				retVal = item.m_dt.toString("yyyy-MM-dd\nhh:mm:ss");
				break;
			case CT_LEVEL:
				{
					QString str = QxtLogger::logLevelToString(item.m_level);
					retVal = str.remove("Level", Qt::CaseInsensitive);
				}
				break;
// 			case CT_FILENAME:
// 				retVal = QString("%1:%2").arg(m_pPrivate->lookupFileNameFromIndex(item.m_nFileIndex)).arg(item.m_nFileLineNumber);
// 				break;
			case CT_MESSAGE:
				retVal = item.m_strMsg.join("\n\r");
				break;
			}
		}
	}
    else
	if (role == Qt::TextAlignmentRole) {
		logData& item = m_pPrivate->m_queue[index.row()];

		switch (index.column()) {
		case CT_LEVEL:
			retVal = Qt::AlignCenter;
		}

	}
    else
	if ((role == Qt::ToolTipRole) || (role == Qt::EditRole)) {

		logData& item = m_pPrivate->m_queue[index.row()];

		switch (index.column()) {
		case CT_FILENAME:
			retVal = QString("<p style='white-space:pre'>Copy to the clipboard:<br>%1:%2")
                .arg(m_pPrivate->lookupFileNameFromIndex(item.m_nFileIndex))
                .arg(item.m_nFileLineNumber);
			break;
        case CT_MESSAGE:
            retVal = item.m_strMsg.join("<br>");
            break;
		}
	}
    else
        if (role == Qt::BackgroundColorRole) {
            logData& item = m_pPrivate->m_queue[index.row()];

            if (index.column() == CT_LEVEL) {
                switch (item.m_level) {
                case QxtLogger::CriticalLevel:
                case QxtLogger::FatalLevel:
                    retVal = QVariant(QColor(Qt::red));
                    break;
                case QxtLogger::WarningLevel:
                    retVal = QVariant(QColor("Orange"));
                    break;
                }
            }

        }

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QxtLoggerEngine* qbuLoggerModel::getLoggerEngine() const
{
	return m_pPrivate->m_pEngine;
}

/////////////////////////////////////////////////////////////////////////////////////////

Qt::ItemFlags qbuLoggerModel::flags(const QModelIndex &index) const
{
	if (index.column() == CT_FILENAME) {
		return Qt::ItemIsEditable | Superclass::flags(index);
	}
	else
		return Superclass::flags(index);
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerModel::setRecordLimit(quint32 nLimit)
{
    m_pPrivate->m_nRecordLimit = nLimit;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerModel::handleRecordLimit()
{
    if (m_pPrivate->reachedRecordLimit() && m_pPrivate->m_buffer.m_holdQueue.empty()) {

		logData data;

		int nIndex = m_pPrivate->m_queue.size();
        beginInsertRows(QModelIndex(), nIndex, nIndex);

        data.m_dt = QDateTime::currentDateTime();
		QDateTime dt = data.m_dt;
        data.m_level = QxtLogger::InfoLevel;
        data.m_nFileLineNumber = __LINE__;
        data.m_strMsg = QStringList() << "The logger model has reached its record limit." 
            << "The queue will be reduced by removing the first 10% of the records.";
        data.m_nFileIndex = m_pPrivate->getFileNameIndex(__FILE__);

        m_pPrivate->m_queue.emplace_back(data);

        endInsertRows();

        m_pPrivate->resizeQueue(this);
		m_pPrivate->m_buffer.m_dtLastSync = dt;

    }
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerModel::setUpdateDelay(quint8 nSeconds)
{
	if (nSeconds > 0) {
		m_pPrivate->m_nUpdateDelay = nSeconds;
		m_pPrivate->m_buffer.m_timer.setInterval(1000 * nSeconds);
	}
	else {
		m_pPrivate->m_nUpdateDelay = 1;
		m_pPrivate->m_buffer.m_timer.setInterval(250);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuLoggerModel::isLogLevel(const QModelIndex &index, uint32_t nLevel) const
{
    QxtLogger::LogLevel level = QxtLogger::NoLevels;

    bool retVal{ m_pPrivate->getLogLevel(index, level) };
    if (retVal) {
        retVal = ((level & nLevel) == nLevel);
    }
    return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuLoggerModel::getColumnName(Cols col) const
{
	QVariant vt = headerData(col, Qt::Horizontal, Qt::DisplayRole);

	return vt.toString();

}

/////////////////////////////////////////////////////////////////////////////////////////
