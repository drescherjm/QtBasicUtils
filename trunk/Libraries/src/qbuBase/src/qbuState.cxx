#include "qbuBasePCH.h"
#include "qbuState.h"
#include "qbuMacros.h"
#include <QDebug>

/////////////////////////////////////////////////////////////////////////////////////////

qbuState::qbuState( QState * parent /*= 0 */ ) : Superclass(parent)
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuState::qbuState( ChildMode childMode, QState * parent /*= 0 */ ) : Superclass(childMode,parent)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuState::~qbuState()
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuState::onEntry( QEvent *event )
{
	Superclass::onEntry(event);

#ifdef DEBUG_STATE_MACHINE

	QString name;
	const QMetaObject* pMetaObject= this->metaObject();

	if (pMetaObject != nullptr) {
		name = pMetaObject->className();
	}

	qDebug() << "Entering state " << qPrintable(name);

#endif //def DEBUG_STATE_MACHINE

}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuState::onExit( QEvent *event )
{
	Superclass::onExit(event);

#ifdef DEBUG_STATE_MACHINE

	QString name;
	const QMetaObject* pMetaObject= this->metaObject();

	if (pMetaObject != nullptr) {
		name = pMetaObject->className();
	}

	qDebug() << "Exiting state " << qPrintable(name);

#endif //def DEBUG_STATE_MACHINE
}



