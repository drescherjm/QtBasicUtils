#include "qbuGUIDev1MainWindow.h"
#include "qbuLog\qbuLoggerModel.h"
#include <QxtLogger>
#include "qbuLog\qbuLog.h"
#include "qbuLog\qbuLoggerWidget2.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuGUIDev1MainWindow::qbuGUIDev1MainWindow(QWidget *parent /*= 0*/, Qt::WindowFlags flags /*= 0*/) : Superclass(parent,flags)
{
	setupUi(this);

	qbuLoggerModel* pModel = new qbuLoggerModel(this);

	qxtLog->addLoggerEngine("LogTableModel", pModel->getLoggerEngine());
	tableView->setModel(pModel);

	QHeaderView* pHeader = tableView->horizontalHeader();
	if (pHeader) {
		pHeader->setStretchLastSection(true);
	}

	qbuLoggerWidget2* pWidget = new qbuLoggerWidget2(this);
	qxtLog->addLoggerEngine("LogWidget2", pWidget->getLoggerEngine());

	tabWidget->addTab(pWidget, QString("LogWidget"));
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuGUIDev1MainWindow::on_actionTestLog0_triggered()
{
	QLOG_INFO() << "This is a test!";
	QLOG_INFO() << "This is test2.";

	QLOG_WARN() << "Lets see a warning.";
}

/////////////////////////////////////////////////////////////////////////////////////////
