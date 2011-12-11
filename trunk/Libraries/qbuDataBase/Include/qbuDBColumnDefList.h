#ifndef __SMDBCOLUMNDEFLIST_H__
#define __SMDBCOLUMNDEFLIST_H__

#include "smDBColumnDef.h"
#include <QList>

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This class implements a list of smDBColDefs
 *
 *
 *	\ingroup smDatabase
 *
 */

class smDBColumnDefList : public QList<smDBColDef>
{
public:
	QString toString();
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMDBCOLUMNDEFLIST_H__

