#include "qbuLogPCH.h"

#include "qbuLog/qbuFileLoggerEngine.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuFileLoggerEngine::qbuFileLoggerEngine(const QString &fileName /*= QString()*/) :
	Superclass(fileName)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuFileLoggerEngine::writeToFile(const QString &level, const QVariantList &messages)
{
	QVariantList msg;
	foreach(const QVariant& vt, messages)
	{
		if (containsNewLine(vt)) {
			msg.append(splitOutNewLines(vt));
		}
		else
		{
			msg.append(vt);
		}
	}

	Superclass::writeToFile(level, msg);
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuFileLoggerEngine::containsNewLine(const QVariant & vt) const
{
	bool retVal = vt.canConvert<QString>();
	if (retVal) {
		retVal = vt.toString().contains('\n');
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QVariantList qbuFileLoggerEngine::splitOutNewLines(const QVariant & vt) const
{
	QVariantList retVal;
	if (vt.canConvert<QString>()) {
		QString str = vt.toString();

		QStringList sl = str.split('\n');

		foreach(QString strItem,sl)
		{
			retVal.append(strItem);
		}

	}
	else
	{
		retVal.append(vt);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////
