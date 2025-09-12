#pragma once

#ifndef QBUTHREAD_H
#define QBUTHREAD_H

#include <QThread>
#include "qbuBase/qbuBaseLibraryDefines.h"

/////////////////////////////////////////////////////////////////////////////////////////
//
// \description
// Adds a missing behavior to QThread. Normally, when you destruct a running thread, you 
// get a warning message and crash/undefined behavior. This class, upon destruction, tells 
// the thread's event loop to quit and waits for the thread to actually finish. It's used 
// just like QThread would be, except that it won't do silly things upon destruction.
//
// This code was taken from the StoppingThread class here:
// https://stackoverflow.com/questions/19280903/how-to-make-a-threaded-network-server-in-qt/19282287#19282287
//
/////////////////////////////////////////////////////////////////////////////////////////

class qbuBase_EXPORT qbuThread : public QThread
{
public:
    qbuThread(QObject * parent = 0) : QThread(parent) {}
    ~qbuThread();
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUTHREAD_H
