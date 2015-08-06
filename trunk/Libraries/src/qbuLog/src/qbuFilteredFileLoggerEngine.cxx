#include "qbuLogPCH.h"

#include "qbuLog/qbuFilteredFileLoggerEngine.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuFilteredFileLoggerEngine::qbuFilteredFileLoggerEngine(const QString &fileName /*= QString()*/) :
	Superclass(fileName)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuFilteredFileLoggerEngine::writeToFile(const QString &level, const QVariantList &messages)
{
	foreach(auto key, m_filterMap.keys())
	{
		if (messages.size() > key) {
			const QVariant& vt = messages.at(key);
			foreach(QString str, m_filterMap.value(key))
			{
				if (vt.toString().compare(str, Qt::CaseInsensitive) == 0) {
					Superclass::writeToFile(level, messages);
					return;
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuFilteredFileLoggerEngine::addFilters(int nLevel, QStringList lstFilters)
{
	bool retVal = (!lstFilters.isEmpty());
	if (retVal) {
		FilterMap::iterator it = m_filterMap.find(nLevel);
		if (it == m_filterMap.end()) {
			m_filterMap[nLevel] = lstFilters;
		}
		else
		{
			m_filterMap[nLevel].append(lstFilters);
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////
