#include "qbuDatabasePCH.h"
#include "qbuDataBase/qbuSimpleQuery.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include "qbuLog/qbuLog.h"
#include "qbuDataBase/qbuDatabaseFunctions.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuSimpleQuery::smPrivate
{
public:
	smPrivate( std::shared_ptr<QSqlDatabase> pDatabase);
	smPrivate(QString strQuery,std::shared_ptr<QSqlDatabase> pDatabase);

public:
	QSqlQuery	m_query;
	std::shared_ptr<QSqlDatabase> m_pDB;
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuSimpleQuery::smPrivate::smPrivate(std::shared_ptr<QSqlDatabase> pDatabase) : m_pDB(pDatabase),
	m_query(*pDatabase)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuSimpleQuery::smPrivate::smPrivate( QString strQuery,std::shared_ptr<QSqlDatabase> pDatabase ) : m_pDB(pDatabase),
	m_query(strQuery,*pDatabase)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuSimpleQuery::qbuSimpleQuery( std::shared_ptr<QSqlDatabase> pDatabase) : m_pPrivate( new smPrivate(pDatabase) )
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuSimpleQuery::qbuSimpleQuery( QString strQuery, std::shared_ptr<QSqlDatabase> pDB ) : m_pPrivate( new smPrivate(strQuery, pDB) )
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuSimpleQuery::~qbuSimpleQuery()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSimpleQuery::exec()
{
	bool retVal =  m_pPrivate->m_query.exec();

	QString query = m_pPrivate->m_query.lastQuery();

	if (query.contains("INSERT")) {
		QString str = query;
// 		QTextStream stream(&str);
// 		QMapIterator<QString, QVariant> i(m_pPrivate->m_query.boundValues());
// 		while (i.hasNext()) {
// 			i.next();
// 			stream << i.key().toAscii().data() << ": "
// 				<< i.value().toString().toAscii().data() << endl;
// 		}


		QMapIterator<QString, QVariant> i(m_pPrivate->m_query.boundValues());
		while (i.hasNext()) {
			i.next();

			QString var = i.key().toLatin1().data();

			int idx = 0;
			do {
				idx = str.indexOf(QRegExp(QString("%1\\W").arg(var)), idx);

				if (idx >= 0) {
					str.replace(idx, var.length(), toQueryValue(i.value()));
				}

			} while (idx >= 0);
			 
		}

		QLOG_DATABASE() << str;
	}
	else
	{
		QLOG_DATABASE() << query;
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSimpleQuery::exec( const QString & query )
{
	return m_pPrivate->m_query.exec(query);
}

/////////////////////////////////////////////////////////////////////////////////////////

QSqlError qbuSimpleQuery::lastError() const
{
	return m_pPrivate->m_query.lastError();
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSimpleQuery::next()
{
	return m_pPrivate->m_query.next();
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSimpleQuery::first()
{
	return m_pPrivate->m_query.first();
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSimpleQuery::prepare( const QString & query )
{
// 	if (query.contains("INSERT", Qt::CaseInsensitive)) {
// 		QString str = query;
// 		QTextStream stream(&str);
// 		QMapIterator<QString, QVariant> i(m_pPrivate->m_query.boundValues());
// 		while (i.hasNext()) {
// 			i.next();
// 			stream << i.key().toAscii().data() << ": "
// 				<< i.value().toString().toAscii().data() << endl;
// 		}
// 
// 		QLOG_DATABASE() << str;
// 
// 	}
// 	else
// 	{
// 		QLOG_DATABASE() << query;
// 	}
	

	return m_pPrivate->m_query.prepare(query);
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuSimpleQuery::executedQuery() const
{
	return m_pPrivate->m_query.executedQuery();
}

/////////////////////////////////////////////////////////////////////////////////////////

QSqlRecord qbuSimpleQuery::record() const
{
	return m_pPrivate->m_query.record();
}

/////////////////////////////////////////////////////////////////////////////////////////

QVariant qbuSimpleQuery::value( int index ) const
{
	return m_pPrivate->m_query.value(index);
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSimpleQuery::isNull( int field ) const
{
	return m_pPrivate->m_query.isNull(field);
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuSimpleQuery::isValid() const
{
	return m_pPrivate->m_query.isValid();
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuSimpleQuery::bindValue( const QString & placeholder, const QVariant & val, QSql::ParamType paramType /*= QSql::In*/ )
{
	return m_pPrivate->m_query.bindValue(placeholder,val,paramType);
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuSimpleQuery::bindValue( int pos, const QVariant & val, QSql::ParamType paramType /*= QSql::In*/ )
{
	return m_pPrivate->m_query.bindValue(pos,val,paramType);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuSimpleQuery::operator const QSqlQuery&() const
{
	return m_pPrivate->m_query;
}

/////////////////////////////////////////////////////////////////////////////////////////

