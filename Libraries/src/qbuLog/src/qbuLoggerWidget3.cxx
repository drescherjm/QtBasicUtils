#include "qbuLogPCH.h"

#include "qbuLog/qbuLog.h"
#include "qbuLog/qbuLoggerModel.h"
#include "qbuLog/qbuLoggerWidget2FileNameDelagate.h"
#include "qbuLog/qbuLoggerWidget3.h"
#include "qbuLog/ui_qbuLoggerWidget2.h"
#include <QColor>
#include <QDateTime>
#include <QHeaderView>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QTableWidgetItem>
#include <QTimer>
#include <limits>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LogFilter : public QSortFilterProxyModel {
public:
	LogFilter(QObject* parent = 0);

public:
	virtual bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;

public:
	void setMask(uint32_t nMask);

protected:
	uint32_t m_nMask;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LogFilter::LogFilter(QObject* parent /*= 0*/) : QSortFilterProxyModel(parent), m_nMask{QxtLogger::AllLevels} {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool LogFilter::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const {
	bool retVal = (m_nMask == QxtLogger::AllLevels);

	if (!retVal) {
		QModelIndex index = sourceModel()->index(source_row, qbuLoggerModel::CT_LEVEL, source_parent);

		QVariant    vt = sourceModel()->data(index, Qt::UserRole);

		if (vt.canConvert<int>()) {
			QxtLogger::LogLevel level = static_cast<QxtLogger::LogLevel>(vt.toUInt());

			retVal = ((level & m_nMask) != 0);
		}
	}

	return retVal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LogFilter::setMask(uint32_t nMask) {
	if (m_nMask != nMask) {
		m_nMask = nMask;
		invalidateFilter();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class qbuLoggerWidget3::qbuPrivate {
public:
	qbuPrivate();

public:
	void        setupLogLevelModel(QStandardItemModel* pModel);
	void        setChecked(QStandardItemModel* pModel, QxtLogger::LogLevel nLevel, bool bChecked);
	QModelIndex getIndexForLevel(QStandardItemModel* pModel, QxtLogger::LogLevel nLevel) const;

	uint32_t    getMaskFromChecked(QStandardItemModel* pModel) const;

	void        updateMasks();
	void        setupStatsWidget(QTableWidget* pTableWidgetStats);
	void        updateStats(QTableWidget* pTableWidgetStats);

public:
	Ui::qbuLoggerWidget2 ui;
	bool                 m_bFirst;
	qbuLoggerModel*      m_pLoggerModel;
	QStandardItemModel   m_modelShow;
	QStandardItemModel   m_modelJump;
	uint32_t             m_ShowMask;
	uint32_t             m_JumpMask;
	LogFilter*           m_pLogFilter;
	
	// Debounce: accumulate dirty row range between event-loop cycles
	int     m_nPendingStart;
	int     m_nPendingEnd;
	QTimer* m_pUpdateTimer;
	int     m_nLastSearchRow{-1}; // -1 = no active search position
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerWidget3::qbuPrivate::qbuPrivate()
    : m_bFirst{true}, m_pLoggerModel{}, m_pLogFilter{}, m_nPendingStart{std::numeric_limits<int>::max()},
      m_nPendingEnd{-1}, m_pUpdateTimer{} {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::qbuPrivate::setupLogLevelModel(QStandardItemModel* pModel) {
	pModel->setColumnCount(1);

	for (auto nLogLevel :
	     {QxtLogger::TraceLevel, QxtLogger::DebugLevel, QxtLogger::InfoLevel, QxtLogger::WarningLevel,
	      QxtLogger::ErrorLevel, QxtLogger::CriticalLevel, QxtLogger::FatalLevel, QxtLogger::WriteLevel}) {

		QStandardItem* item = new QStandardItem(QxtLogger::logLevelToString(nLogLevel));
		item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
		item->setData(Qt::Checked, Qt::CheckStateRole);
		item->setData(nLogLevel, Qt::UserRole);

		switch (nLogLevel) {
		case QxtLogger::NoLevels:
			break;
		case QxtLogger::TraceLevel:
			break;
		case QxtLogger::DebugLevel:
			break;
		case QxtLogger::InfoLevel:
			break;
		case QxtLogger::WarningLevel:

#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
			item->setData(QVariant(QColor("Orange")), Qt::BackgroundColorRole);
#else
			// Replace Qt::BackgroundColorRole with Qt::BackgroundRole
			item->setData(QVariant(QColor("Orange")), Qt::BackgroundRole);
#endif
			break;
		case QxtLogger::ErrorLevel:
			break;
		case QxtLogger::CriticalLevel:
		case QxtLogger::FatalLevel:

#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
			item->setData(QVariant(QColor(Qt::red)), Qt::BackgroundColorRole);
#else
			// Replace Qt::BackgroundColorRole with Qt::BackgroundRole
			item->setData(QVariant(QColor(Qt::red)), Qt::BackgroundRole);
#endif
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::qbuPrivate::setupStatsWidget(QTableWidget* pTableWidgetStats) {
	int nRow = 0;
	for (auto nLogLevel :
	     {QxtLogger::TraceLevel, QxtLogger::DebugLevel, QxtLogger::InfoLevel, QxtLogger::WarningLevel,
	      QxtLogger::ErrorLevel, QxtLogger::CriticalLevel, QxtLogger::FatalLevel, QxtLogger::WriteLevel}) {
		pTableWidgetStats->insertRow(pTableWidgetStats->rowCount());
		pTableWidgetStats->setItem(nRow++, 0, new QTableWidgetItem(QxtLogger::logLevelToString(nLogLevel)));
	}

	int nExtra = pTableWidgetStats->height() - pTableWidgetStats->horizontalHeader()->height() -
	             pTableWidgetStats->viewport()->height();

	int nHeight = pTableWidgetStats->horizontalHeader()->height() +
	              pTableWidgetStats->rowHeight(0) * pTableWidgetStats->rowCount() + 4;

	int nParentHeight = pTableWidgetStats->parentWidget()->height();

	pTableWidgetStats->setMinimumHeight(std::min(nHeight, nParentHeight));

	auto pHeader = pTableWidgetStats->horizontalHeader();
	pHeader->setSectionResizeMode(0, QHeaderView::Stretch);
	pHeader->setSectionResizeMode(1, QHeaderView::Interactive);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::qbuPrivate::updateStats(QTableWidget* pTableWidgetStats) {
	int nRow = 0;
	for (auto nLogLevel :
	     {QxtLogger::TraceLevel, QxtLogger::DebugLevel, QxtLogger::InfoLevel, QxtLogger::WarningLevel,
	      QxtLogger::ErrorLevel, QxtLogger::CriticalLevel, QxtLogger::FatalLevel, QxtLogger::WriteLevel}) {
		pTableWidgetStats->setItem(
		    nRow++, 1, new QTableWidgetItem(QString::number(m_pLoggerModel->getMessageTypeCountsByLevel(nLogLevel)))
		);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::qbuPrivate::setChecked(QStandardItemModel* pModel, QxtLogger::LogLevel nLevel, bool bChecked) {
	if (pModel != nullptr) {

		QModelIndex index = getIndexForLevel(pModel, nLevel);
		pModel->setData(index, bChecked ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QModelIndex qbuLoggerWidget3::qbuPrivate::getIndexForLevel(QStandardItemModel* pModel, QxtLogger::LogLevel nLevel)
    const {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint32_t qbuLoggerWidget3::qbuPrivate::getMaskFromChecked(QStandardItemModel* pModel) const {
	uint32_t retVal{};

	for (int nRow = 0; nRow < pModel->rowCount(); ++nRow) {

		QModelIndex index = pModel->index(nRow, 0);

		QVariant    vt = pModel->data(index, Qt::CheckStateRole);

		if (vt.canConvert<int>() && (vt.value<int>() == Qt::Checked)) {
			retVal |= pModel->data(index, Qt::UserRole).toUInt();
		}
	}

	return retVal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::qbuPrivate::updateMasks() {
	m_ShowMask = getMaskFromChecked(&m_modelShow);
	m_JumpMask = getMaskFromChecked(&m_modelJump);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerWidget3::qbuLoggerWidget3(QWidget* parent /*= 0*/)
    : Superclass(parent), m_pPrivate{std::make_unique<qbuPrivate>()} {
	m_pPrivate->ui.setupUi(this);
	adjustSize();

	m_pPrivate->setupLogLevelModel(&m_pPrivate->m_modelShow);
	m_pPrivate->setupLogLevelModel(&m_pPrivate->m_modelJump);

	m_pPrivate->ui.listViewShow->setModel(&m_pPrivate->m_modelShow);
	m_pPrivate->ui.listViewJump->setModel(&m_pPrivate->m_modelJump);

	for (auto nLogLevel : {QxtLogger::TraceLevel, QxtLogger::DebugLevel, QxtLogger::InfoLevel, QxtLogger::WriteLevel}) {
		m_pPrivate->setChecked(&m_pPrivate->m_modelJump, nLogLevel, false);
	}

	m_pPrivate->updateMasks();

	m_pPrivate->setupStatsWidget(m_pPrivate->ui.tableWidgetStats);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerWidget3::~qbuLoggerWidget3() {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::setLoggerModel(qbuLoggerModel* pModel) {
	m_pPrivate->m_pLoggerModel = pModel;

	QTableView* pTableView = m_pPrivate->ui.tableView;

	if (pTableView) {

		m_pPrivate->m_pLogFilter = new LogFilter(this);
		m_pPrivate->m_pLogFilter->setSourceModel(pModel);
		m_pPrivate->m_pLogFilter->setSortRole(Qt::UserRole);
		pTableView->setModel(m_pPrivate->m_pLogFilter);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::initialize() {
	QTableView* pTableView = m_pPrivate->ui.tableView;

	if (pTableView) {

		if (m_pPrivate->m_pLoggerModel == nullptr) {
			setLoggerModel(new qbuLoggerModel(this));
		}

		QAbstractItemModel* pModel = pTableView->model();

		connect(
		    pModel, SIGNAL(rowsInserted(const QModelIndex&, int, int)), SLOT(rowsInserted(const QModelIndex&, int, int))
		);

		pTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

		auto* pDelegate = new qbuLoggerWidget2FileNameDelagate(this);
		pTableView->setItemDelegateForColumn(qbuLoggerModel::CT_FILENAME, pDelegate);

		// Single click connection replaces all per-row persistent editors.
		connect(pTableView, &QAbstractItemView::clicked, [pDelegate, pTableView](const QModelIndex& index) {
			pDelegate->onViewClicked(pTableView, index);
		});

		// Invalidate row height cache when the message column is resized,
		// since word-wrap means height depends on available width.
		connect(
		    pTableView->horizontalHeader(), &QHeaderView::sectionResized,
		    [this, pTableView](int logicalIndex, int /*oldSize*/, int /*newSize*/) {
			    if (logicalIndex == qbuLoggerModel::CT_MESSAGE) {
				    // Invalidate all cached heights in the source model.
				    int nRows = m_pPrivate->m_pLoggerModel->rowCount();
				    for (int i = 0; i < nRows; ++i) {
					    m_pPrivate->m_pLoggerModel->setRowHeight(i, -1);
				    }
				    // Re-measure all visible rows immediately.
				    QModelIndex tl = pTableView->indexAt(pTableView->viewport()->rect().topLeft());
				    QModelIndex br = pTableView->indexAt(pTableView->viewport()->rect().bottomRight());
				    if (tl.isValid() && br.isValid()) {
					    updateRowHeights(tl.row(), br.row());
				    }
			    }
		    }
		);

		connect(m_pPrivate->ui.lineEditSearch, &QLineEdit::textChanged, [this](const QString&) {
			m_pPrivate->m_nLastSearchRow = -1;
		});

		QHeaderView* pHeader = pTableView->horizontalHeader();
		if (pHeader) {
			pHeader->setStretchLastSection(true);
		}

		// Debounce timer: coalesces rapid rowsInserted bursts into a single
		// updateRowHeights pass once the event loop drains.
		m_pPrivate->m_pUpdateTimer = new QTimer(this);
		m_pPrivate->m_pUpdateTimer->setSingleShot(true);
		m_pPrivate->m_pUpdateTimer->setInterval(0);
		connect(m_pPrivate->m_pUpdateTimer, &QTimer::timeout, this, &qbuLoggerWidget3::flushPendingRowHeights);

		// Size any rows already present in the model (e.g. when a pre-populated
		// model is set before initialize() is called).
		int nRows = pTableView->model()->rowCount();
		if (nRows > 0) {
			updateRowHeights(0, nRows - 1);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QxtLoggerEngine* qbuLoggerWidget3::getLoggerEngine() const {
	QxtLoggerEngine* retVal = nullptr;

	// qbuLoggerModel* pModel = qobject_cast<qbuLoggerModel*>(m_pPrivate->ui.tableView->model());

	if (m_pPrivate->m_pLoggerModel) {
		retVal = m_pPrivate->m_pLoggerModel->getLoggerEngine();
	}

	return retVal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::rowsInserted(const QModelIndex& parent, int start, int end) {
	// Accumulate the dirty range — multiple rapid insertions collapse into one.
	m_pPrivate->m_nPendingStart = std::min(m_pPrivate->m_nPendingStart, start);
	m_pPrivate->m_nPendingEnd   = std::max(m_pPrivate->m_nPendingEnd, end);
	m_pPrivate->m_pUpdateTimer->start(); // no-op if already running
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::flushPendingRowHeights() {
	int start = m_pPrivate->m_nPendingStart;
	int end   = m_pPrivate->m_nPendingEnd;

	// Reset before calling updateRowHeights in case it triggers re-entrancy.
	m_pPrivate->m_nPendingStart = std::numeric_limits<int>::max();
	m_pPrivate->m_nPendingEnd   = -1;

	if (start <= end) {
		updateRowHeights(start, end);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::updateRowHeights(int nStartingRow, int nEndingRow) {
	QTableView*     pTableView   = m_pPrivate->ui.tableView;
	qbuLoggerModel* pSourceModel = m_pPrivate->m_pLoggerModel;
	LogFilter*      pFilter      = m_pPrivate->m_pLogFilter;

	if (!pTableView || !pSourceModel || !pFilter)
		return;

	for (int proxyRow = nStartingRow; proxyRow <= nEndingRow; ++proxyRow) {

		QModelIndex proxyIdx  = pFilter->index(proxyRow, qbuLoggerModel::CT_MESSAGE);
		QModelIndex sourceIdx = pFilter->mapToSource(proxyIdx);

		if (!sourceIdx.isValid())
			continue;

		// Skip rows whose height is already known — avoids redundant delegate
		// layout passes when the same row is visited more than once (e.g.
		// after a record-limit trim resets the cache).
		if (pSourceModel->rowHeight(sourceIdx.row()) > 0)
			continue;

		QSize sz         = pTableView->sizeHintForIndex(proxyIdx);
		int   nMinHeight = qMax(pTableView->verticalHeader()->sectionSizeHint(proxyRow), 40);
		int   nHeight    = qMax(sz.height() + 6, nMinHeight);

		// Cache in the source model. This also emits dataChanged(SizeHintRole)
		// which keeps the view correct if a row is later re-shown after filtering.
		pSourceModel->setRowHeight(sourceIdx.row(), nHeight);

		pTableView->verticalHeader()->resizeSection(proxyRow, nHeight);
	}

	if (m_pPrivate->m_bFirst && pTableView->model()->rowCount() > 0) {
		pTableView->resizeColumnToContents(qbuLoggerModel::CT_DATE);
		pTableView->resizeColumnToContents(qbuLoggerModel::CT_LEVEL);
		pTableView->resizeColumnToContents(qbuLoggerModel::CT_FILENAME);

		int nWidth = pTableView->columnWidth(qbuLoggerModel::CT_DATE) * 0.80;
		pTableView->setColumnWidth(qbuLoggerModel::CT_DATE, nWidth);

		m_pPrivate->m_bFirst = false;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::on_pushButtonOptions_clicked() {
	auto pStacked = m_pPrivate->ui.stackedWidget;

	if (pStacked) {
		pStacked->setCurrentIndex(1);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::on_pushButtonStats_clicked() {
	auto pStacked = m_pPrivate->ui.stackedWidget;
	if (pStacked) {
		m_pPrivate->updateStats(m_pPrivate->ui.tableWidgetStats);
		pStacked->setCurrentIndex(2);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::on_pushButtonLog_clicked() {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::searchText(bool bForward) {
	QTableView* pTableView = m_pPrivate->ui.tableView;
	QLineEdit*  pSearch    = m_pPrivate->ui.lineEditSearch;
	LogFilter*  pFilter    = m_pPrivate->m_pLogFilter;

	if (!pTableView || !pSearch || !pFilter)
		return;

	QString strTerm = pSearch->text().trimmed();
	if (strTerm.isEmpty())
		return;

	int nRows = pFilter->rowCount();
	if (nRows == 0)
		return;

	// Start one past the current position so repeated presses advance.
	int nStart = m_pPrivate->m_nLastSearchRow;
	if (nStart < 0) {
		// No active search — begin from current selection or top/bottom.
		QModelIndexList sel = pTableView->selectionModel()->selectedRows();
		nStart              = sel.isEmpty() ? (bForward ? -1 : nRows) : sel.first().row();
	}

	int nStep = bForward ? 1 : -1;
	int nRow  = nStart + nStep;

	for (int i = 0; i < nRows; ++i, nRow += nStep) {
		// Wrap around.
		if (nRow >= nRows)
			nRow = 0;
		if (nRow < 0)
			nRow = nRows - 1;

		QModelIndex idx    = pFilter->index(nRow, qbuLoggerModel::CT_MESSAGE);
		QString     strMsg = pFilter->data(idx, Qt::DisplayRole).toString();

		if (strMsg.contains(strTerm, Qt::CaseInsensitive)) {
			m_pPrivate->m_nLastSearchRow = nRow;
			pTableView->selectRow(nRow);
			pTableView->scrollTo(idx, QAbstractItemView::PositionAtCenter);
			return;
		}
	}

	// No match found — reset position so next search starts fresh.
	m_pPrivate->m_nLastSearchRow = -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::on_toolButtonSearchDown_clicked() {
	// If there is text in the search box, do a text search.
	// Otherwise fall through to severity jump using the Jump mask.
	if (!m_pPrivate->ui.lineEditSearch->text().trimmed().isEmpty()) {
		searchText(/*forward=*/true);
		return;
	}
	jumpToSeverity(/*forward=*/true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::on_toolButtonSearchUp_clicked() {
	if (!m_pPrivate->ui.lineEditSearch->text().trimmed().isEmpty()) {
		searchText(/*forward=*/false);
		return;
	}
	jumpToSeverity(/*forward=*/false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::jumpToSeverity(bool bForward) {
	QTableView* pTableView = m_pPrivate->ui.tableView;
	if (!pTableView) return;

	QAbstractItemModel*  pModel    = pTableView->model();
	QItemSelectionModel* pSelected = pTableView->selectionModel();
	if (!pModel || !pSelected) return;

	int nRows = pModel->rowCount();
	if (nRows == 0) return;

	// Determine starting row from current selection.
	int nPos = bForward ? -1 : nRows;
	if (pSelected->hasSelection()) {
		QModelIndexList selection = pSelected->selectedRows(0);
		if (!selection.isEmpty()) {
			nPos = selection.first().row();
		}
	}

	int nStep = bForward ? 1 : -1;

	for (int nRow = nPos + nStep; bForward ? (nRow < nRows) : (nRow >= 0); nRow += nStep) {
		QModelIndex index = pModel->index(nRow, qbuLoggerModel::CT_LEVEL);
		QVariant    vt    = pModel->data(index, Qt::UserRole);
		if (vt.canConvert<int>()) {
			if ((vt.toUInt() & m_pPrivate->m_JumpMask) != 0) {
				pSelected->select(index, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
				pTableView->scrollTo(index, QAbstractItemView::EnsureVisible);
				return;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QStringList qbuLoggerWidget3::getVisibleColumns() const {
	QStringList retVal;

	QTableView* pTableView = m_pPrivate->ui.tableView;

	if (pTableView) {

		for (int i = 0; i < pTableView->model()->columnCount(); i++) {
			if (!pTableView->isColumnHidden(i)) {
				retVal.append(pTableView->model()->headerData(i, Qt::Horizontal).toString());
			}
		}
	}

	return retVal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QStringList& qbuLoggerWidget3::getAllColumns() const {
	static QStringList retVal;

	if (retVal.isEmpty()) {

		QTableView* pTableView = m_pPrivate->ui.tableView;

		if (pTableView && (pTableView->model() != nullptr)) {

			for (int i = 0; i < pTableView->model()->columnCount(); i++) {
				retVal.append(pTableView->model()->headerData(i, Qt::Horizontal).toString());
			}
		}
	}

	return retVal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool qbuLoggerWidget3::hideColumnByName(QString strColumnName, bool bHide) {
	QTableView* pTableView = m_pPrivate->ui.tableView;

	bool        retVal = ((pTableView != nullptr) && (pTableView->model() != nullptr));
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool qbuLoggerWidget3::isColumnHidden(QString strColumnName) const {
	QTableView* pTableView = m_pPrivate->ui.tableView;

	bool        retVal = (pTableView == nullptr);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
