#ifndef __SMSTRINGLIST_H__
#define __SMSTRINGLIST_H__

#include <QStringList>
#include "smMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief 
 *	This class extends the QStringList to add some extra needed functionality.
 *
 *	\ingroup smBase
 */

class smStringList : public QStringList
{
	SM_DECLARE_SUPERCLASS(QStringList);
public:
	inline smStringList() { }
	inline explicit smStringList(const QString &i) { append(i); }
	inline smStringList(const smStringList &l) : QStringList(l) { }
	inline smStringList(const QStringList &l) : QStringList(l) { }
	inline smStringList(const QList<QString> &l) : QStringList(l) { }
public:
	int		removeAll(QString strRemove,Qt::CaseSensitivity cs);
	int		indexOf(const QString & str, Qt::CaseSensitivity cs, int from=0) const;
	int		lastIndexOf( const QString & value, Qt::CaseSensitivity cs, int from = -1 ) const;
	QString toCSVString();
	QString toDelimitedString(QString delimiter=",");
};

#endif //__SMSTRINGLIST_H__