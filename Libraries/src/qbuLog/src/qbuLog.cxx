#include "qbuLogPCH.h"
#include "qbuLog/qbuLog.h"
#include <QRegularExpression>

/////////////////////////////////////////////////////////////////////////////////////////

QString logFileName(QString strFile, int nLine)
{
	QRegularExpression regex(R"(\.\.[/\\])"); // Matches "..\" or "../"
	strFile.remove(regex);
	return QString("%1:%2").arg(strFile).arg(nLine);
}

/////////////////////////////////////////////////////////////////////////////////////////
