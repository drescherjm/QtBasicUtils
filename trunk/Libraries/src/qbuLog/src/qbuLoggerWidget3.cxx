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

class qbuLoggerWidget3::qbuPrivate
{
public:
    qbuPrivate();
public:
    void    setupLogLevelModel(QStandardItemModel* pModel);
  
public:
    Ui::qbuLoggerWidget2    ui;
    bool                    m_bFirst;
    qbuLoggerModel*         m_pLoggerModel;
    QStandardItemModel      m_modelShow;
    QStandardItemModel      m_modelJump;
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerWidget3::qbuPrivate::qbuPrivate() : m_bFirst{ true }, m_pLoggerModel{}
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
        pModel->appendRow(item);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerWidget3::qbuLoggerWidget3(QWidget *parent /*= 0*/) : Superclass(parent), m_pPrivate{std::make_unique<qbuPrivate>()}
{
    m_pPrivate->ui.setupUi(this);
    m_pPrivate->setupLogLevelModel(&m_pPrivate->m_modelShow);
    m_pPrivate->setupLogLevelModel(&m_pPrivate->m_modelJump);
    
    m_pPrivate->ui.listViewShow->setModel(&m_pPrivate->m_modelShow);
    m_pPrivate->ui.listViewJump->setModel(&m_pPrivate->m_modelJump);
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

        QSortFilterProxyModel* pSortModel = new QSortFilterProxyModel(this);
        pSortModel->setSourceModel(pModel);
        pSortModel->setSortRole(Qt::UserRole);
        pTableView->setModel(pSortModel);
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
        int nIndex = (pStacked->currentIndex() + 1) % pStacked->count();
        pStacked->setCurrentIndex(nIndex);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////