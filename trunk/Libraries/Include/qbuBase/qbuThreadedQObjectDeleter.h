#pragma once

#ifndef QBUTHREADEDQOBJECTDELETER_H
#define QBUTHREADEDQOBJECTDELETER_H

#include "qbuBase/qbuBaseLibraryDefines.h"
#include <QObject>
#include <QPointer>

class QThread;

/////////////////////////////////////////////////////////////////////////////////////////
//
// \description
// Deletes a given QObject when its thread is destroyed.Useful when a thread logically 
// owns its objects.This logical ownership is not a parent - child ownership, because the 
// thread and the logically owned object live in different threads(!).
//
// The constructor is private, and a factory method is provided.This is to enforce creation 
// of the deleter on the free store(a.k.a.the heap).It'd be likely an error to make the 
// deleter on the stack, so this pattern uses the compiler to prevent it from happening.
//
// The object must not have been moved to the specified thread yet, otherwise the 
// construction of the deleter would be subject to race conditions - the object could have 
// already deleted itself within the thread.This precondition is asserted.
//
// This code was taken from the ThreadedQObjectDeleter class here:
// https://stackoverflow.com/questions/19280903/how-to-make-a-threaded-network-server-in-qt/19282287#19282287
//
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
// Deletes an object living in a thread upon thread's termination.

class qbuBase_EXPORT qbuThreadedQObjectDeleter : public QObject {
    Q_OBJECT
    QPointer<QObject> m_object;
    qbuThreadedQObjectDeleter(QObject * object, QThread * thread);
    ~qbuThreadedQObjectDeleter();
public:
    static void addDeleter(QObject * object, QThread * thread);
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUTHREADEDQOBJECTDELETER_H
