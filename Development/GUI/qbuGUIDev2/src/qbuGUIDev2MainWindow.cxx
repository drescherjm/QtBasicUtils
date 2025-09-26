#include "qbuGUIDev2MainWindow.h"
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

#include <QThreadPool>
#include "qbuGUIDev2LoggerJob.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuGUIDev2MainWindow::qbuGUIDev2MainWindow(QWidget *parent /*= 0*/, Qt::WindowFlags flags /*= 0*/) : Superclass(parent,flags)
{
	setupUi(this);

	qbuLoggerModel* pModel = new qbuLoggerModel(this);
	pModel->setRecordLimit(1000);
	qbuLoggerWidget3* pWidget3 = new qbuLoggerWidget3(this);

	pWidget3->setLoggerModel(pModel);
	pWidget3->initialize();

	qxtLog->addLoggerEngine("LogWidget3", pWidget3->getLoggerEngine());

	tabWidget->addTab(pWidget3, QString("LogWidget3"));
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuGUIDev2MainWindow::on_actionTestLog0_triggered()
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

void qbuGUIDev2MainWindow::generateLogDataTimer()
{
   // qxtLog->stream(static_cast<QxtLogger::LogLevel>(rand() % 7)) << "This is a test!";

	QxtLogger::LogLevel level = generateRandomLogLevel();

	static int i = 0;

	i++;

	QString strMsg = QString("%1: - ").arg(i);

	switch (level) {
	case QxtLogger::InfoLevel:
		QLOG_INFO() << strMsg << generateInfoMessage();
		break;
	case QxtLogger::CriticalLevel:
		QLOG_CRIT() << strMsg << "Something really bad happened!" << "Should I be worried?";
		break;
	case QxtLogger::WarningLevel:
		QLOG_WARN() << strMsg << "What is this warning about?";
		break;
	case QxtLogger::TraceLevel:
		QLOG_TRACE() << strMsg << "John was debugging!";
		break;
	case QxtLogger::ErrorLevel:
		QLOG_ERROR() << strMsg << "Some type of error occurred.";
		break;
	case QxtLogger::DebugLevel:
		QLOG_DEBUG() << strMsg << "John was debugging!" << "What is the difference between TRACE and DEBUG again?";
		break;
	case QxtLogger::WriteLevel:
		QLOG_WRITE() << strMsg << "Lets write something" << "I don't understand the randomization here!";
		break;
	case QxtLogger::FatalLevel:
		QLOG_FATAL() << strMsg << "Should we exit the program?"
			<< "I don't know"
			<< "Lets generate some more data instead."
			<< "Why should I generate data if there is a FATAL error?"
			<< "I don't know but keep going.";
		break;
	default:
		qxtLog->log(level, QVariantList() << strMsg << "What is this!" << "Level=" <<level);
	}
   
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuGUIDev2MainWindow::on_actionToggleRandomData_triggered()
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

void qbuGUIDev2MainWindow::on_actionToggle_Random_Data_Generation_Job_triggered()
{
    if (QThreadPool::globalInstance()->activeThreadCount() < 1) {
        qbuGUIDev2LoggerJob* pJob = new qbuGUIDev2LoggerJob;

        connect(this, SIGNAL(stopJob()), pJob, SLOT(stopJob()), Qt::DirectConnection);

        QThreadPool::globalInstance()->start(pJob);

    }
    else {
        emit stopJob();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuGUIDev2MainWindow::~qbuGUIDev2MainWindow()
{
    emit stopJob();

    QThreadPool::globalInstance()->waitForDone(5000);
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuGUIDev2MainWindow::on_actionHide_Filename_Column_triggered()
{
	qbuLoggerWidget3* pWidget = findChild<qbuLoggerWidget3*>();

	if (pWidget) {
		QStringList lst = pWidget->getVisibleColumns();

		if (lst.contains("File", Qt::CaseInsensitive)) {
			pWidget->hideColumnByName("File",!pWidget->isColumnHidden("File"));
		}
	}

}

/////////////////////////////////////////////////////////////////////////////////////////
