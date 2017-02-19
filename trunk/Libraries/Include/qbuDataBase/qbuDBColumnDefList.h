#pragma once

#ifndef QBUDBCOLUMNDEFLIST_H
#define QBUDBCOLUMNDEFLIST_H

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
	QString toString(size_t nWordWrapAt=0);
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUDBCOLUMNDEFLIST_H
