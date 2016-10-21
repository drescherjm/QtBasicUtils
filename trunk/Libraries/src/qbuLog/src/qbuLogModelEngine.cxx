#include "qbuLogPCH.h"

#include "qbuLog/qbuLogModelEngine.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuLogModelEngine::qbuLogModelEngine( QObject *parent /*= 0*/ ) : Superclass(parent)
{
	initialize();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuLogModelEngine::~qbuLogModelEngine()
{

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

			QString strFileName = vt.toString();

			int nIndex = strFileName.lastIndexOf(':');

			strFile = strFileName.left(nIndex);

			if (nIndex > 0) {
				nLineNumber = strFileName.mid(++nIndex).toUInt();
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
