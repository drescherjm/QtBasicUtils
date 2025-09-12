#pragma once

#include <QString>
#include <QMap>
#include <QMutex>
#include "qbuBase/qbuNonThreadSafeSingleton.h"

#ifndef __QBUPROPERTYTYPENAMEALIAS_H__
#define __QBUPROPERTYTYPENAMEALIAS_H__

/////////////////////////////////////////////////////////////////////////////////////////

class qbuPropertyTypeNameAlias : public NonThreadSafeSingleton<qbuPropertyTypeNameAlias>
{
public:
	bool	addAlias(QString strClassTypeName, QString strTypeNameAlias);
	QString getAlias(QString strClassTypeName);

	typedef QMap<QString,QString> MapAliases;
private:
	MapAliases	m_mapHelpers;
	QMutex		m_mutex;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // __QBUPROPERTYTYPENAMEALIAS_H__
