#pragma once

#ifndef QBUSTATE_H
#define QBUSTATE_H

#include "qbuBaseLibraryDefines.h"

#include <QState>
#include "qbuMacros.h"
#include "qbuErrorBase.h"

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	
*	\ingroup qbuBase
*/

class qbuBase_EXPORT qbuState : public QState, public qbuErrorBase
{
	Q_OBJECT
	QBU_DECLARE_SUPERCLASS(QState);
public:
	explicit qbuState ( QState * parent = 0 );
	qbuState ( ChildMode childMode, QState * parent = 0 );
	virtual ~qbuState();
protected:
	virtual void onEntry(QEvent *event);
	virtual void onExit(QEvent *event);
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUSTATE_H
