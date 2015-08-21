#pragma once

#ifndef QBUSTRINGLIST_H
#define QBUSTRINGLIST_H

#include <QStringList>
#include "qbuBase/qbuMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief 
 *	This class extends the QStringList to add some extra needed functionality.
 *
 *	\ingroup smBase
 */

class qbuStringList : public QStringList
{
	QBU_DECLARE_SUPERCLASS(QStringList);
public:
	inline qbuStringList() { }
	inline explicit qbuStringList(const QString &i) { append(i); }
	inline qbuStringList(const qbuStringList &l) : QStringList(l) { }
	inline qbuStringList(const QStringList &l) : QStringList(l) { }
	inline qbuStringList(const QList<QString> &l) : QStringList(l) { }
public:
	int			removeAll(QString strRemove,Qt::CaseSensitivity cs);
	int			indexOf(const QString & str, Qt::CaseSensitivity cs, int from=0) const;
	int			lastIndexOf( const QString & value, Qt::CaseSensitivity cs, int from = -1 ) const;
	QString		toCSVString();
	QString		toDelimitedString(QString delimiter=",");
	QString		toDoubleDelimitedString(QString before, QString after);
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUSTRINGLIST_H
