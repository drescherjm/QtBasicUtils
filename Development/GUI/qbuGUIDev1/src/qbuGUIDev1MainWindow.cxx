#include "qbuGUIDev1MainWindow.h"
#include "qbuLog/qbuLoggerModel.h"
#include <QxtLogger>
#include "qbuLog/qbuLog.h"
#include "qbuLog/qbuLoggerWidget2.h"
#include <QTimer>
#include <time.h>
//#include <time.inl>
#include <array>
#include <random>
#include "qbuLog/qbuLoggerWidget3.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuGUIDev1MainWindow::qbuGUIDev1MainWindow(QWidget *parent /*= 0*/, Qt::WindowFlags flags /*= 0*/) : Superclass(parent,flags)
{
	setupUi(this);

	qbuLoggerModel* pModel = new qbuLoggerModel(this);
	pModel->setRecordLimit(50);

	qxtLog->addLoggerEngine("LogTableModel", pModel->getLoggerEngine());
	tableView->setModel(pModel);

	QHeaderView* pHeader = tableView->horizontalHeader();
	if (pHeader) {
		pHeader->setStretchLastSection(true);
	}

	pModel = new qbuLoggerModel(this);
	pModel->setRecordLimit(100);
	qbuLoggerWidget2* pWidget = new qbuLoggerWidget2(this);
	pWidget->setModel(pModel);
	pWidget->initialize();

	qxtLog->addLoggerEngine("LogWidget2", pWidget->getLoggerEngine());

	tabWidget->addTab(pWidget, QString("LogWidget2"));

	pModel = new qbuLoggerModel(this);
	pModel->setRecordLimit(100);
	qbuLoggerWidget3* pWidget3 = new qbuLoggerWidget3(this);
	pWidget3->setLoggerModel(pModel);
	pWidget3->initialize();

	qxtLog->addLoggerEngine("LogWidget3", pWidget3->getLoggerEngine());

	tabWidget->addTab(pWidget3, QString("LogWidget3"));
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuGUIDev1MainWindow::on_actionTestLog0_triggered()
{
	QLOG_INFO() << "This is a test!" << "Lets add multiple rows. " << "How about a very long row! Test Test Test Test Test! What will happen? I am not sure.";
	QLOG_INFO() << "This is test2.";

	QLOG_WARN() << "Lets see a warning.";
	QLOG_CRIT() << "Testing..";
}

/////////////////////////////////////////////////////////////////////////////////////////

QxtLogger::LogLevel generateRandomLogLevel()
{
	static std::array< QxtLogger::LogLevel, 8>  g_levels {
		QxtLogger::TraceLevel,
		QxtLogger::DebugLevel, 
		QxtLogger::InfoLevel, 
		QxtLogger::WarningLevel, 
		QxtLogger::ErrorLevel, 
		QxtLogger::CriticalLevel, 
		QxtLogger::FatalLevel, 
		QxtLogger::WriteLevel };
	
   static std::random_device rd;
   static std::mt19937 g(rd());

	std::shuffle(g_levels.begin(),g_levels.end(),g);

	return g_levels[0];
}

/////////////////////////////////////////////////////////////////////////////////////////

QString generateInfoMessage()
{
	QString retVal;

	int nVal = rand() % 4;
	switch (nVal)
	{
	case 0:
		retVal = "This is a test!";
		break;
	case 1:
		retVal = "[DATABASE]\nINSERT OR REPLACE INTO Forms(FORMID, FORMINSERTDATE, FORMNAME, FORMOBJECTNAME, FORMTYPEID) \nVALUES(21, \'2017-12-17T23:12:41\', \'Patient and Exam Information\', \'rfProject101TechnologistPatientInfoWidget\', 2);";
		break;
	case 2:
		retVal = "This is a test!";
		break;
	case 3:
		retVal = "This is a test!";
		break;
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuGUIDev1MainWindow::generateLogDataTimer()
{
   // qxtLog->stream(static_cast<QxtLogger::LogLevel>(rand() % 7)) << "This is a test!";

	QxtLogger::LogLevel level = generateRandomLogLevel();

	switch (level) {
	case QxtLogger::InfoLevel:
		QLOG_INFO() << generateInfoMessage();
		break;
	case QxtLogger::CriticalLevel:
		QLOG_CRIT() << "Something really bad happened!" << "Should I be worried?";
		break;
	case QxtLogger::WarningLevel:
		QLOG_WARN() << "What is this warning about?";
		break;
	case QxtLogger::TraceLevel:
		QLOG_TRACE() << "John was debugging!";
		break;
	case QxtLogger::ErrorLevel:
		QLOG_ERROR() << "Some type of error occurred.";
		break;
	case QxtLogger::DebugLevel:
		QLOG_DEBUG() << "John was debugging!" << "What is the difference between TRACE and DEBUG again?";
		break;
	case QxtLogger::WriteLevel:
		QLOG_WRITE() << "Lets write something" << "I don't understand the randomization here!";
		break;
	case QxtLogger::FatalLevel:
		QLOG_FATAL() << "Should we exit the program?"
			<< "I don't know"
			<< "Lets generate some more data instead."
			<< "Why should I generate data if there is a FATAL error?"
			<< "I don't know but keep going.";
		break;
	default:
		qxtLog->log(level, QVariantList() << "What is this!" << "Level=" <<level);
	}
   
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuGUIDev1MainWindow::on_actionToggleRandomData_triggered()
{
	QTimer* pTimer = findChild<QTimer*>();

	if (!pTimer) {
		pTimer = new QTimer(this);
		pTimer->setInterval(40);
		connect(pTimer, SIGNAL(timeout()), this, SLOT(generateLogDataTimer()));

		std::srand(time(NULL));
	}

	if (pTimer) {
		if (pTimer->isActive()) {
			pTimer->stop();
		}
		else {
			pTimer->start();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
