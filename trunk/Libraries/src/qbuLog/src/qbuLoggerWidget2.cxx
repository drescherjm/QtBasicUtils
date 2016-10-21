#include "qbuLogPCH.h"

#include "qbuLog/qbuLoggerWidget2.h"
#include <QTableWidgetItem>
#include <QDateTime>
#include <QHeaderView>
#include <QColor>
#include "qbuLog/qbuLoggerModel.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerWidget2::qbuLoggerWidget2( QWidget *parent /*= 0*/ ) : Superclass(parent)
{
	initialize();
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget2::initialize()
{
	
	qbuLoggerModel* pModel = new qbuLoggerModel(this);
	setModel(pModel);


	QHeaderView* pHeader = horizontalHeader();
	if (pHeader) {
		pHeader->setStretchLastSection(true);
	}
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

	resizeRowToContents(end);
}

/////////////////////////////////////////////////////////////////////////////////////////
