#include "qbuLogPCH.h"

#include "qbuLog/qbuLoggerWidget2.h"
#include <QTableWidgetItem>
#include <QDateTime>
#include <QHeaderView>
#include <QColor>
#include "qbuLog/qbuLoggerModel.h"
#include "qbuLog/qbuLoggerWidget2FileNameDelagate.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerWidget2::qbuLoggerWidget2(QWidget *parent /*= 0*/) : Superclass(parent), m_bFirst(true)
{
	//initialize();

    connect(tableView,)
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget2::initialize()
{
    qbuLoggerModel* pModel = qobject_cast<qbuLoggerModel*>(tableView->model());

    if (pModel == nullptr) {
        pModel = dynamic_cast<qbuLoggerModel*>(tableView->model());
    }

    if (pModel == nullptr) {
        pModel = new qbuLoggerModel(this);
        tableView->setModel(pModel);
    }
  
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    tableView->setItemDelegateForColumn(qbuLoggerModel::CT_FILENAME, new qbuLoggerWidget2FileNameDelagate(this));

    //verticalHeader()->setVisible(true);
		
    QHeaderView* pHeader = tableView->horizontalHeader();
	if (pHeader) {
		pHeader->setStretchLastSection(true);
	}

    int nRows = tableView->model()->rowCount();

    for (int i = 0; i < nRows; ++i) {
        tableView->openPersistentEditor(tableView->model()->index(i, qbuLoggerModel::CT_FILENAME, QModelIndex()));
        tableView->resizeRowToContents(i);
    }

}

/////////////////////////////////////////////////////////////////////////////////////////

QxtLoggerEngine* qbuLoggerWidget2::getLoggerEngine() const
{
	QxtLoggerEngine* retVal = nullptr;

    qbuLoggerModel* pModel = qobject_cast<qbuLoggerModel*>(tableView->model());

	if (pModel) {
		retVal = pModel->getLoggerEngine();
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget2::rowsInserted(const QModelIndex &parent, int start, int end)
{
    //tableView->rowsInserted(parent, start, end);

    for (int i = start; i <= end; ++i) {
        tableView->openPersistentEditor(tableView->model()->index(i, qbuLoggerModel::CT_FILENAME, QModelIndex()));
        //resizeRowToContents(i);
        QSize sz = tableView->sizeHintForIndex(tableView->model()->index(i, qbuLoggerModel::CT_MESSAGE));
        int nMinHeight = qMax(tableView->verticalHeader()->sectionSizeHint(end), 40); // 40 = Min size of the File Icon column

        tableView->verticalHeader()->resizeSection(end, qMax(sz.height() + 3, nMinHeight)); // 3 = space for borders + grid
    }
    	
    if (m_bFirst) {
        tableView->resizeColumnToContents(qbuLoggerModel::CT_DATE);
        tableView->resizeColumnToContents(qbuLoggerModel::CT_LEVEL);
        tableView->resizeColumnToContents(qbuLoggerModel::CT_FILENAME);

        int nWidth = tableView->columnWidth(qbuLoggerModel::CT_DATE) * 0.80;

        tableView->setColumnWidth(qbuLoggerModel::CT_DATE, nWidth);

		m_bFirst = false;
	}

	
}

/////////////////////////////////////////////////////////////////////////////////////////
