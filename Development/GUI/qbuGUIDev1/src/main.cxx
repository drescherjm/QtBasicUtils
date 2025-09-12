
#include "qbuGUIDev1MainWindow.h"
#include <QApplication>
#include "qbuLog\qbuLog.h"
#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////////

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)

void myMessageHandler(QtMsgType type, const char *msg)
{
	//in this function, you can write the message to any stream!
	switch (type) {
	case QtDebugMsg:
		QLOG_DEBUG() << QString("qDebug: %1").arg(msg);
		break;
	case QtWarningMsg:
		QLOG_WARN() << QString("qWarning: %1").arg(msg);
		break;
	case QtCriticalMsg:
		QLOG_CRIT() << QString("qCritical: %1").arg(msg);
		break;
	case QtFatalMsg:
		QLOG_FATAL() << QString("qFatal: %1").arg(msg);
		abort();
	}
}

#else

void myMessageHandler(QtMsgType type, const QMessageLogContext & logContext, const QString & msg)
{
	Q_UNUSED(logContext);

	static QString g_strLast;

	bool bLog = (g_strLast != msg);

	//in this function, you can write the message to any stream!
	switch (type) {
	case QtDebugMsg:
		QLOG_DEBUG() << QString("qDebug: %1").arg(msg);
		break;
	case QtWarningMsg:
		if (bLog) {
			QLOG_WARN() << QString("qWarning: %1").arg(msg);
		}
		else {
			std::cerr << qPrintable(msg) << std::endl;
		}
		break;
	case QtCriticalMsg:
		QLOG_CRIT() << QString("qCritical: %1").arg(msg);
		break;
	case QtFatalMsg:
		QLOG_FATAL() << QString("qFatal: %1").arg(msg);
		abort();
	}

	g_strLast = msg;
}

#endif // QT_VERSION < QT_VERSION_CHECK(5, 0, 0)

/////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)   
	qInstallMsgHandler(myMessageHandler);
#else
	qInstallMessageHandler(myMessageHandler);
#endif // QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
	
	QApplication app(argc, argv);
	qbuGUIDev1MainWindow window;
	window.show();
	
	QLOG_INFO() << "Logging from " << __FUNCTION__;

	return app.exec();
}

/////////////////////////////////////////////////////////////////////////////////////////
