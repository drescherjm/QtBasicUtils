
#include "qbuGUIDev1MainWindow.h"
#include <QApplication>
#include "qbuLog\qbuLog.h"

/////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	qbuGUIDev1MainWindow window;
	window.show();
	
	QLOG_INFO() << "Logging from " << __FUNCTION__;

	return app.exec();
}

/////////////////////////////////////////////////////////////////////////////////////////
