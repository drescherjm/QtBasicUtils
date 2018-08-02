#pragma once

#ifndef QBUSIMPLEQUERY_H
#define QBUSIMPLEQUERY_H

#include <QObject>
#include <QSQLError>
#include <QSqlRecord>
#include <qsql.h>
#include <memory>

class qbuDatabase;
class QSqlQuery;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\ingroup qbuDatabase
 */

class qbuSimpleQuery : public QObject
{
public:
	typedef QObject Superclass;
public:
	qbuSimpleQuery(std::shared_ptr<qbuDatabase> pDB);
	qbuSimpleQuery(QString strQuery, std::shared_ptr<qbuDatabase> pDB);
	virtual ~qbuSimpleQuery();

	operator const QSqlQuery&() const; 

public:
	virtual bool exec();
	virtual bool exec(const QString & query);
	virtual bool first();
	virtual bool next();
	virtual bool prepare(const QString & query);
	virtual	bool isNull(int field) const;
	virtual	bool isValid() const;

	virtual QSqlError	lastError() const;
	virtual QString		executedQuery() const;
	virtual QSqlRecord	record() const;
	virtual	QVariant	value(int index) const;
	virtual void		bindValue(const QString & placeholder, const QVariant & val, QSql::ParamType paramType = QSql::In);
	virtual	void		bindValue(int pos, const QVariant & val, QSql::ParamType paramType = QSql::In);

    std::shared_ptr<qbuDatabase> getDataBase();

protected:
	virtual	void	databaseError(QString strErrorMessage);

private:
	class qbuPrivate;
	std::unique_ptr<qbuPrivate>	m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUSIMPLEQUERY_H

