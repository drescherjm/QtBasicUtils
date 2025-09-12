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
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget2::initialize()
{
	qbuLoggerModel* pModel = qobject_cast<qbuLoggerModel*>(model());

    if (pModel == nullptr) {
        pModel = dynamic_cast<qbuLoggerModel*>(model());
    }

    if (pModel == nullptr) {
        pModel = new qbuLoggerModel(this);
	    setModel(pModel);
    }
  
    setSelectionBehavior(QAbstractItemView::SelectRows);

	setItemDelegateForColumn(qbuLoggerModel::CT_FILENAME, new qbuLoggerWidget2FileNameDelagate(this));

    //verticalHeader()->setVisible(true);
		
	QHeaderView* pHeader = horizontalHeader();
	if (pHeader) {
		pHeader->setStretchLastSection(true);
	}

    int nRows = model()->rowCount();

    for (int i = 0; i < nRows; ++i) {
        openPersistentEditor(model()->index(i, qbuLoggerModel::CT_FILENAME, QModelIndex()));
        //resizeRowToContents(i);
    }

    emit updateRowHeights(0, nRows);

}

/////////////////////////////////////////////////////////////////////////////////////////

QxtLoggerEngine* qbuLoggerWidget2::getLoggerEngine() const
{
	QxtLoggerEngine* retVal = nullptr;

	qbuLoggerModel* pModel = qobject_cast<qbuLoggerModel*>(model());

	if (pModel) {
		retVal = pModel->getLoggerEngine();
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget2::rowsInserted(const QModelIndex &parent, int start, int end)
{
	Superclass::rowsInserted(parent, start, end);

    emit updateRowHeights(start, end);
	
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget2::updateRowHeights(int nStartingRow, int nEndingRow)
{
    for (int i = nStartingRow; i <= nEndingRow; ++i) {
        openPersistentEditor(model()->index(i, qbuLoggerModel::CT_FILENAME, QModelIndex()));
        //resizeRowToContents(i);
        QSize sz = sizeHintForIndex(model()->index(i, qbuLoggerModel::CT_MESSAGE));
        int nMinHeight = qMax(verticalHeader()->sectionSizeHint(nEndingRow), 40); // 40 = Min size of the File Icon column

        verticalHeader()->resizeSection(i, qMax(sz.height() + 3, nMinHeight)); // 3 = space for borders + grid
    }

    if (m_bFirst) {
        resizeColumnToContents(qbuLoggerModel::CT_DATE);
        resizeColumnToContents(qbuLoggerModel::CT_LEVEL);
        resizeColumnToContents(qbuLoggerModel::CT_FILENAME);

        int nWidth = columnWidth(qbuLoggerModel::CT_DATE) * 0.80;

        setColumnWidth(qbuLoggerModel::CT_DATE, nWidth);

        m_bFirst = false;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
