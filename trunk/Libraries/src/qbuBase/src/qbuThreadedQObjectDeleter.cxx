#include "qbuBasePCH.h"

#include "qbuBase/qbuThreadedQObjectDeleter.h"


/////////////////////////////////////////////////////////////////////////////////////////

qbuThreadedQObjectDeleter::qbuThreadedQObjectDeleter(QObject * object, QThread * thread) :
QObject(thread), m_object(object)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuThreadedQObjectDeleter::~qbuThreadedQObjectDeleter()
{
    if (m_object && m_object->thread() == 0) {
        delete m_object;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuThreadedQObjectDeleter::addDeleter(QObject * object, QThread * thread)
{
    // The object must not be in the thread yet, otherwise we'd have
    // a race condition.
    Q_ASSERT(thread != object->thread());
    new qbuThreadedQObjectDeleter(object, thread);
}

/////////////////////////////////////////////////////////////////////////////////////////
