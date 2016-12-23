#include "qbuLogPCH.h"

#include "qbuLog/qbuLoggerWidget3.h"
#include <QTableWidgetItem>
#include <QDateTime>
#include <QHeaderView>
#include <QColor>
#include "qbuLog/qbuLoggerModel.h"
#include "qbuLog/qbuLoggerWidget2FileNameDelagate.h"
#include "qbuLog/ui_qbuLoggerWidget2.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuLoggerWidget3::qbuPrivate
{
public:
    qbuPrivate();

public:
    Ui::qbuLoggerWidget2    ui;
    bool                    m_bFirst;
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerWidget3::qbuPrivate::qbuPrivate() : m_bFirst{true}
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerWidget3::qbuLoggerWidget3(QWidget *parent /*= 0*/) : Superclass(parent), m_pPrivate{std::make_unique<qbuPrivate>()}
{
    m_pPrivate->ui.setupUi(this);

    QTableView* pTableView = m_pPrivate->ui.tableView;

    if (pTableView) {
        connect(pTableView, SIGNAL(rowsInserted(const QModelIndex&, int, int)), SIGNAL(rowsInserted(const QModelIndex&, int, int)));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerWidget3::~qbuLoggerWidget3()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::setModel(QAbstractItemModel *model)
{
    QTableView* pTableView = m_pPrivate->ui.tableView;

    if (pTableView) {
        pTableView->setModel(model);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::initialize()
{
    QTableView* pTableView = m_pPrivate->ui.tableView;

    if (pTableView) {
        qbuLoggerModel* pModel = qobject_cast<qbuLoggerModel*>(pTableView->model());

        if (pModel == nullptr) {
            pModel = dynamic_cast<qbuLoggerModel*>(pTableView->model());
        }

        if (pModel == nullptr) {
            pModel = new qbuLoggerModel(this);
            pTableView->setModel(pModel);
        }

        pTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

        pTableView->setItemDelegateForColumn(qbuLoggerModel::CT_FILENAME, new qbuLoggerWidget2FileNameDelagate(this));


        QHeaderView* pHeader = pTableView->horizontalHeader();
        if (pHeader) {
            pHeader->setStretchLastSection(true);
        }

        int nRows = pTableView->model()->rowCount();

        for (int i = 0; i < nRows; ++i) {
            pTableView->openPersistentEditor(pTableView->model()->index(i, qbuLoggerModel::CT_FILENAME, QModelIndex()));
            pTableView->resizeRowToContents(i);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

QxtLoggerEngine* qbuLoggerWidget3::getLoggerEngine() const
{
	QxtLoggerEngine* retVal = nullptr;

    qbuLoggerModel* pModel = qobject_cast<qbuLoggerModel*>(m_pPrivate->ui.tableView->model());

	if (pModel) {
		retVal = pModel->getLoggerEngine();
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget3::rowsInserted(const QModelIndex &parent, int start, int end)
{
    QTableView* pTableView = m_pPrivate->ui.tableView;

    if (pTableView) {
        for (int i = start; i <= end; ++i) {
            pTableView->openPersistentEditor(pTableView->model()->index(i, qbuLoggerModel::CT_FILENAME, QModelIndex()));
            //resizeRowToContents(i);
            QSize sz = pTableView->sizeHintForIndex(pTableView->model()->index(i, qbuLoggerModel::CT_MESSAGE));
            int nMinHeight = qMax(pTableView->verticalHeader()->sectionSizeHint(end), 40); // 40 = Min size of the File Icon column

            pTableView->verticalHeader()->resizeSection(end, qMax(sz.height() + 3, nMinHeight)); // 3 = space for borders + grid
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
