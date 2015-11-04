#include "qbuBasePCH.h"
#include "qbuBase/qbuState.h"
#include "qbuBase/qbuMacros.h"

#ifdef QBU_HAS_LOG
#include <qbuLog/qbuLog.h>
#endif // QBU_HAS_LOG


/////////////////////////////////////////////////////////////////////////////////////////

qbuState::qbuState(QState * parent /*= 0 */) : Superclass(parent), m_bInState(false)
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

#ifdef QBU_HAS_LOG

	QString name;
	const QMetaObject* pMetaObject= this->metaObject();

	if (pMetaObject != nullptr) {
		name = pMetaObject->className();
	}

	QLOG_INFO() << "Entering state " << name;

#endif //def QBU_HAS_LOG

	m_bInState = true;

}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuState::onExit( QEvent *event )
{
	Superclass::onExit(event);

#ifdef QBU_HAS_LOG

	QString name;
	const QMetaObject* pMetaObject= this->metaObject();

	if (pMetaObject != nullptr) {
		name = pMetaObject->className();
	}

	QLOG_INFO() << "Exiting state " << name;

#endif //def QBU_HAS_LOG

	m_bInState = false;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuState::isInState()
{
	return m_bInState;
}

/////////////////////////////////////////////////////////////////////////////////////////



