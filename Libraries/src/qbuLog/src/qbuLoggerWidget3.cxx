#include "qbuLogPCH.h"

#include "qbuLog/qbuLoggerWidget3.h"
#include <QTableWidgetItem>
#include <QDateTime>
#include <QHeaderView>
#include <QColor>
#include <QStandardItemModel>
#include "qbuLog/qbuLoggerModel.h"
#include "qbuLog/qbuLoggerWidget2FileNameDelagate.h"
#include "qbuLog/ui_qbuLoggerWidget2.h"
#include <QSortFilterProxyModel>
#include "qbuLog/qbuLog.h"

/////////////////////////////////////////////////////////////////////////////////////////

class LogFilter : public QSortFilterProxyModel
{
public:
    LogFilter(QObject *parent = 0);
public:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
   
public:
    void    setMask(uint32_t nMask);

protected:
    uint32_t    m_nMask;
};

/////////////////////////////////////////////////////////////////////////////////////////

LogFilter::LogFilter(QObject *parent /*= 0*/) : QSortFilterProxyModel(parent), m_nMask{ QxtLogger::AllLevels }
{

}

/////////////////////////////////////////////////////////////////////////////////////////

bool LogFilter::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    bool retVal = (m_nMask == QxtLogger::AllLevels);

    if (!retVal) {
        QModelIndex index = sourceModel()->index(source_row, qbuLoggerModel::CT_LEVEL, source_parent);

        QVariant vt = sourceModel()->data(index, Qt::UserRole);

        if (vt.canConvert<int>()) {
            QxtLogger::LogLevel level = static_cast<QxtLogger::LogLevel>(vt.toUInt());

            retVal = ((level & m_nMask) != 0);
        }

    }

    return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void LogFilter::setMask(uint32_t nMask)
{
    if (m_nMask != nMask) {
        m_nMask = nMask;
        invalidateFilter();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

class qbuLoggerWidget3::qbuPrivate
{
public:
    qbuPrivate();
public:
    void            setupLogLevelModel(QStandardItemModel* pModel);
    void            setChecked(QStandardItemModel* pModel, QxtLogger::LogLevel nLevel, bool bChecked);
    QModelIndex     getIndexForLevel(QStandardItemModel* pModel, QxtLogger::LogLevel nLevel) const;

    uint32_t        getMaskFromChecked(QStandardItemModel* pModel) const;

    void            updateMasks();
    void            setupStatsWidget(QTableWidget* pTableWidgetStats);
    void            updateStats(QTableWidget* pTableWidgetStats);

public:
    Ui::qbuLoggerWidget2    ui;
    bool                    m_bFirst;
    qbuLoggerModel*         m_pLoggerModel;
    QStandardItemModel      m_modelShow;
    QStandardItemModel      m_modelJump;
    uint32_t                m_ShowMask;
    uint32_t                m_JumpMask;
    LogFilter*              m_pLogFilter;
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerWidget3::qbuPrivate::qbuPrivate() : m_bFirst{ true }, m_pLoggerModel{}, m_pLogFilter{}
{

}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::qbuPrivate::setupLogLevelModel(QStandardItemModel* pModel)
{
    pModel->setColumnCount(1);

    for (auto nLogLevel : { QxtLogger::TraceLevel, QxtLogger::DebugLevel,QxtLogger::InfoLevel, QxtLogger::WarningLevel, 
        QxtLogger::ErrorLevel, QxtLogger::CriticalLevel, QxtLogger::FatalLevel, QxtLogger::WriteLevel }) {

        QStandardItem* item = new QStandardItem(QxtLogger::logLevelToString(nLogLevel));
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(Qt::Checked, Qt::CheckStateRole);
        item->setData(nLogLevel, Qt::UserRole);

        switch (nLogLevel)
        {
        case QxtLogger::NoLevels:
            break;
        case QxtLogger::TraceLevel:
            break;
        case QxtLogger::DebugLevel:
            break;
        case QxtLogger::InfoLevel:
            break;
        case QxtLogger::WarningLevel:
            item->setData(QVariant(QColor("Orange")), Qt::BackgroundColorRole);
            break;
        case QxtLogger::ErrorLevel:
            break;
        case QxtLogger::CriticalLevel:
        case QxtLogger::FatalLevel:
            item->setData(QVariant(QColor(Qt::red)), Qt::BackgroundColorRole);
            break;
        case QxtLogger::WriteLevel:
            break;
        case QxtLogger::AllLevels:
            break;
        default:
            break;
        }

        pModel->appendRow(item);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::qbuPrivate::setupStatsWidget(QTableWidget* pTableWidgetStats)
{
    int nRow = 0;
    for (auto nLogLevel : { QxtLogger::TraceLevel, QxtLogger::DebugLevel,QxtLogger::InfoLevel, QxtLogger::WarningLevel,
          QxtLogger::ErrorLevel, QxtLogger::CriticalLevel, QxtLogger::FatalLevel, QxtLogger::WriteLevel }) {
        pTableWidgetStats->insertRow(pTableWidgetStats->rowCount());
        pTableWidgetStats->setItem(nRow++, 0, new QTableWidgetItem( QxtLogger::logLevelToString(nLogLevel)));
    }

    int nExtra = pTableWidgetStats->height() - pTableWidgetStats->horizontalHeader()->height() - 
        pTableWidgetStats->viewport()->height();

    int nHeight = pTableWidgetStats->horizontalHeader()->height()
        + pTableWidgetStats->rowHeight(0) * pTableWidgetStats->rowCount() + 4;

    int nParentHeight = pTableWidgetStats->parentWidget()->height();

    pTableWidgetStats->setMinimumHeight(std::min(nHeight,nParentHeight));

    auto pHeader = pTableWidgetStats->horizontalHeader();
    pHeader->setSectionResizeMode(0, QHeaderView::Stretch);
	pHeader->setSectionResizeMode(1, QHeaderView::Interactive);
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::qbuPrivate::updateStats(QTableWidget* pTableWidgetStats)
{
	int nRow = 0;
	for (auto nLogLevel : { QxtLogger::TraceLevel, QxtLogger::DebugLevel,QxtLogger::InfoLevel, QxtLogger::WarningLevel,
		  QxtLogger::ErrorLevel, QxtLogger::CriticalLevel, QxtLogger::FatalLevel, QxtLogger::WriteLevel }) {
		pTableWidgetStats->setItem(nRow++, 1, new QTableWidgetItem(QString::number(m_pLoggerModel->getMessageTypeCountsByLevel(nLogLevel))));
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::qbuPrivate::setChecked(QStandardItemModel* pModel, QxtLogger::LogLevel nLevel, bool bChecked)
{
    if (pModel != nullptr) {

        QModelIndex index = getIndexForLevel(pModel, nLevel);
        pModel->setData(index, bChecked ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);

    }
}

/////////////////////////////////////////////////////////////////////////////////////////

QModelIndex qbuLoggerWidget3::qbuPrivate::getIndexForLevel(QStandardItemModel* pModel, QxtLogger::LogLevel nLevel) const
{
    QModelIndex retVal;

    if (pModel != nullptr) {
        for (int nRow = 0; nRow < pModel->rowCount(); ++nRow) {

            retVal = pModel->index(nRow, 0);

            QVariant vt = pModel->data(retVal, Qt::UserRole);

            if (vt.canConvert<int>()) {
                QxtLogger::LogLevel level = static_cast<QxtLogger::LogLevel>(vt.value<int>());
                if (level == nLevel) {
                    break;
                }
            }
        }
    }
    return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

uint32_t qbuLoggerWidget3::qbuPrivate::getMaskFromChecked(QStandardItemModel* pModel) const
{
    uint32_t retVal{};

    for (int nRow = 0; nRow < pModel->rowCount(); ++nRow) {

        QModelIndex index = pModel->index(nRow, 0);

        QVariant vt = pModel->data(index, Qt::CheckStateRole);

        if (vt.canConvert<int>() && (vt.value<int>() == Qt::Checked)) {
            retVal |= pModel->data(index, Qt::UserRole).toUInt();
        }
    }

    return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::qbuPrivate::updateMasks()
{
    m_ShowMask = getMaskFromChecked(&m_modelShow);
    m_JumpMask = getMaskFromChecked(&m_modelJump);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerWidget3::qbuLoggerWidget3(QWidget *parent /*= 0*/) : Superclass(parent), m_pPrivate{std::make_unique<qbuPrivate>()}
{
    m_pPrivate->ui.setupUi(this);
    adjustSize();

    m_pPrivate->setupLogLevelModel(&m_pPrivate->m_modelShow);
    m_pPrivate->setupLogLevelModel(&m_pPrivate->m_modelJump);
    
    m_pPrivate->ui.listViewShow->setModel(&m_pPrivate->m_modelShow);
    m_pPrivate->ui.listViewJump->setModel(&m_pPrivate->m_modelJump);

    for (auto nLogLevel : { QxtLogger::TraceLevel, QxtLogger::DebugLevel, QxtLogger::InfoLevel, QxtLogger::WriteLevel }) {
        m_pPrivate->setChecked(&m_pPrivate->m_modelJump, nLogLevel, false);
    }

    m_pPrivate->updateMasks();

    m_pPrivate->setupStatsWidget(m_pPrivate->ui.tableWidgetStats);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerWidget3::~qbuLoggerWidget3()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::setLoggerModel(qbuLoggerModel* pModel)
{
    m_pPrivate->m_pLoggerModel = pModel;

    QTableView* pTableView = m_pPrivate->ui.tableView;

    if (pTableView) {

        m_pPrivate->m_pLogFilter = new LogFilter(this);
        m_pPrivate->m_pLogFilter->setSourceModel(pModel);
        m_pPrivate->m_pLogFilter->setSortRole(Qt::UserRole);
        pTableView->setModel(m_pPrivate->m_pLogFilter);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::initialize()
{
    QTableView* pTableView = m_pPrivate->ui.tableView;

    if (pTableView) {

        if (m_pPrivate->m_pLoggerModel == nullptr) {
            setLoggerModel(new qbuLoggerModel(this));
        }

        QAbstractItemModel* pModel = pTableView->model();

        connect(pModel, SIGNAL(rowsInserted(const QModelIndex&, int, int)), SLOT(rowsInserted(const QModelIndex&, int, int)));

        pTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

        pTableView->setItemDelegateForColumn(qbuLoggerModel::CT_FILENAME, new qbuLoggerWidget2FileNameDelagate(this));
        
        QHeaderView* pHeader = pTableView->horizontalHeader();
        if (pHeader) {
            pHeader->setStretchLastSection(true);
        }

        int nRows = pTableView->model()->rowCount();

        for (int i = 0; i < nRows; ++i) {
            pTableView->openPersistentEditor(pModel->index(i, qbuLoggerModel::CT_FILENAME, QModelIndex()));
        }

        emit updateRowHeights(0, nRows);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

QxtLoggerEngine* qbuLoggerWidget3::getLoggerEngine() const
{
	QxtLoggerEngine* retVal = nullptr;
    
   // qbuLoggerModel* pModel = qobject_cast<qbuLoggerModel*>(m_pPrivate->ui.tableView->model());

	if (m_pPrivate->m_pLoggerModel) {
        retVal = m_pPrivate->m_pLoggerModel->getLoggerEngine();
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::rowsInserted(const QModelIndex &parent, int start, int end)
{
    emit updateRowHeights(start, end);    
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::updateRowHeights(int nStartingRow, int nEndingRow)
{
    QTableView* pTableView = m_pPrivate->ui.tableView;

    if (pTableView) {
        for (int i = nStartingRow; i <= nEndingRow; ++i) {
            pTableView->openPersistentEditor(pTableView->model()->index(i, qbuLoggerModel::CT_FILENAME, QModelIndex()));
            //resizeRowToContents(i);
            QSize sz = pTableView->sizeHintForIndex(pTableView->model()->index(i, qbuLoggerModel::CT_MESSAGE));
            int nMinHeight = qMax(pTableView->verticalHeader()->sectionSizeHint(nEndingRow), 40); // 40 = Min size of the File Icon column

            pTableView->verticalHeader()->resizeSection(i, qMax(sz.height() + 3, nMinHeight)); // 3 = space for borders + grid
        }

        if (m_pPrivate->m_bFirst) {
            pTableView->resizeColumnToContents(qbuLoggerModel::CT_DATE);
            pTableView->resizeColumnToContents(qbuLoggerModel::CT_LEVEL);
            pTableView->resizeColumnToContents(qbuLoggerModel::CT_FILENAME);

            int nWidth = pTableView->columnWidth(qbuLoggerModel::CT_DATE) * 0.80;

            pTableView->setColumnWidth(qbuLoggerModel::CT_DATE, nWidth);

            m_pPrivate->m_bFirst = false;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::on_pushButtonOptions_clicked()
{
    auto pStacked = m_pPrivate->ui.stackedWidget;

    if (pStacked) {
        pStacked->setCurrentIndex(1);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::on_pushButtonStats_clicked()
{
	auto pStacked = m_pPrivate->ui.stackedWidget;
    if (pStacked) {
		m_pPrivate->updateStats(m_pPrivate->ui.tableWidgetStats);
        pStacked->setCurrentIndex(2);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::on_pushButtonLog_clicked()
{
    auto pStacked = m_pPrivate->ui.stackedWidget;
    if (pStacked) {
        if (pStacked->currentIndex() == 1) {
			m_pPrivate->updateMasks();

			if (m_pPrivate->m_pLogFilter) {
				m_pPrivate->m_pLogFilter->setMask(m_pPrivate->m_ShowMask);
			}
        }
        pStacked->setCurrentIndex(0);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::on_toolButtonSearchDown_clicked()
{
    auto pTableView = m_pPrivate->ui.tableView;

	QItemSelectionModel* pSelected = pTableView->selectionModel();
    if (pSelected) {
        int nPos = -1;
        if (pSelected->hasSelection()) {
            QModelIndexList selection = pSelected->selectedRows(0);
            if (!selection.isEmpty()) {
                nPos = selection.first().row();
            }
        }

        auto pModel = pTableView->model();

        for (int nRow = nPos + 1; nRow < pModel->rowCount(); ++nRow) {

            auto index = pModel->index(nRow, qbuLoggerModel::CT_LEVEL);
            auto& vt = pModel->data(index, Qt::UserRole);
            if (vt.canConvert<int>()) {
                int nVal = vt.toInt();
                if ((nVal & m_pPrivate->m_JumpMask) != 0) {
                    pSelected->select(index, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
                    pTableView->scrollTo(index, QAbstractItemView::EnsureVisible);
                    return;
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::on_toolButtonSearchUp_clicked()
{
	auto pTableView = m_pPrivate->ui.tableView;

	QItemSelectionModel* pSelected = pTableView->selectionModel();
	if (pSelected) {
        auto pModel = pTableView->model();
        if (pModel && pModel->rowCount() > 0) {
            int nPos = pModel->rowCount()+1;
            if (pSelected->hasSelection()) {
                QModelIndexList selection = pSelected->selectedRows(0);
                if (!selection.isEmpty()) {
                    nPos = selection.first().row();
                }
            }

            for (int nRow = nPos - 1; nRow>=0; --nRow) {

                auto index = pModel->index(nRow, qbuLoggerModel::CT_LEVEL);
                auto& vt = pModel->data(index, Qt::UserRole);
                if (vt.canConvert<int>()) {
                    int nVal = vt.toInt();
                    if ((nVal & m_pPrivate->m_JumpMask) != 0) {
                        pSelected->select(index, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
                        pTableView->scrollTo(index, QAbstractItemView::EnsureVisible);
                        return;
                    }
                }
            }
        }
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

QStringList qbuLoggerWidget3::getVisibleColumns() const
{
	QStringList retVal;

	QTableView* pTableView = m_pPrivate->ui.tableView;

	if (pTableView) {
		
		for (int i = 0; i < pTableView->model()->columnCount(); i++)
		{
			if (!pTableView->isColumnHidden(i)) {
				retVal.append(pTableView->model()->headerData(i, Qt::Horizontal).toString());
			}
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

const QStringList& qbuLoggerWidget3::getAllColumns() const
{
	static QStringList retVal;

	if (retVal.isEmpty()) {

		QTableView* pTableView = m_pPrivate->ui.tableView;

		if (pTableView && (pTableView->model() != nullptr)) {

			for (int i = 0; i < pTableView->model()->columnCount(); i++)
			{
				retVal.append(pTableView->model()->headerData(i, Qt::Horizontal).toString());
			}
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuLoggerWidget3::hideColumnByName(QString strColumnName, bool bHide)
{
	QTableView* pTableView = m_pPrivate->ui.tableView;

	bool retVal = ((pTableView != nullptr) && (pTableView->model() != nullptr));
	if (retVal) {
		retVal = false;

		for (int i = 0; (i < pTableView->model()->columnCount()) && !retVal; i++) {

			QString strCol = pTableView->model()->headerData(i, Qt::Horizontal).toString();

			retVal = (strCol.compare(strColumnName, Qt::CaseInsensitive) == 0);
			if (retVal) {
				pTableView->setColumnHidden(i, bHide);
			}

		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuLoggerWidget3::isColumnHidden(QString strColumnName) const
{
	QTableView* pTableView = m_pPrivate->ui.tableView;

	bool retVal = (pTableView == nullptr);
	if (!retVal) {
		retVal = (pTableView->model() != nullptr);

		if (retVal) {
			for (int i = 0; (i < pTableView->model()->columnCount()); i++) {

				QString strCol = pTableView->model()->headerData(i, Qt::Horizontal).toString();

				retVal = (strCol.compare(strColumnName, Qt::CaseInsensitive) == 0);
				if (retVal) {
					retVal = pTableView->isColumnHidden(i);
					break;
				}

			}
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////
