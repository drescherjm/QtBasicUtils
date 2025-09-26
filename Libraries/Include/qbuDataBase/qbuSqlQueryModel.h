#pragma once

#ifndef QBUSQLQUERYMODEL_H
#define QBUSQLQUERYMODEL_H

#include "qbuDataBase/qbuDataBaseLibraryDefines.h"
#include <QSqlQueryModel>
#include <qbuBase/qbuMacros.h>
#include <memory>

class qbuSelectQuery;
class qbuDatabase;

/////////////////////////////////////////////////////////////////////////////////////////

class qbuDataBase_EXPORT qbuSqlQueryModel : public QSqlQueryModel
{
	Q_OBJECT
	QBU_DECLARE_SUPERCLASS(QSqlQueryModel)
public:
	explicit qbuSqlQueryModel(QObject *parent = 0);

public:
	void	setQuery(qbuSelectQuery* pQuery, std::shared_ptr<qbuDatabase> pDB);
	using	Superclass::setQuery;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUSQLQUERYMODEL_H
