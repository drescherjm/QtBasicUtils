#include "qbuLogPCH.h"

#include "qbuLog/qbuLogModelEngine.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuLogModelEngine::qbuLogModelEngine( QObject *parent /*= 0*/ ) : Superclass(parent)
{
	initialize();
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLogModelEngine::initLoggerEngine()
{
    return; // Should work out of the box!
}

/////////////////////////////////////////////////////////////////////////////////////////

/*!
    \reimp
 */
void qbuLogModelEngine::killLoggerEngine()
{
    return; // I do nothing.
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuLogModelEngine::isInitialized() const
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLogModelEngine::initialize()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLogModelEngine::writeFormatted( QxtLogger::LogLevel level, const QList<QVariant>& messages )
{
	QDateTime dt = QDateTime::currentDateTime();
	
	QString strFile;

	QStringList lstMsg;

	quint32 nLineNumber = 0;

	bool bFirst = true;

	foreach(QVariant vt, messages) {
		if (bFirst) {

			QStringList sl = vt.toString().split(":");
			if (!sl.isEmpty()) {
				strFile = sl.first();
				sl.pop_front();
				if (!sl.isEmpty()) {
					nLineNumber = sl.front().toUInt();
				}

			}
			
			bFirst = false;
		}
		else
		{
			lstMsg << vt.toString();
		}
		
	}

	if (!lstMsg.isEmpty()) {
		emit logMessage(dt,level, strFile, nLineNumber, lstMsg);
	}

}

/////////////////////////////////////////////////////////////////////////////////////////
