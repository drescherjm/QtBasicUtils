#ifndef __SMDBCOLUMNDEFLIST_H__
#define __SMDBCOLUMNDEFLIST_H__

#include "qbuDBColumnDef.h"
#include <QList>

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This class implements a list of qbuDBColDefs
 *
 *
 *	\ingroup qbuDatabase
 *
 */

class qbuDBColumnDefList : public QList<qbuDBColDef>
{
public:
	QString toString();
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMDBCOLUMNDEFLIST_H__

