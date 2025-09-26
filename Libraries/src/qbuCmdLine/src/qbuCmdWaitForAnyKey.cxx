#include "qbuCmdLinePCH.h"

#include "qbuCmdLine/qbuCmdWaitForAnyKey.h"

#include <iostream>
#include <QCoreApplication>
#include <QTextStream>
#include <QIODevice>
#include "qbuCmdLine/QCmdParseError.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuCmdWaitForAnyKey::qbuCmdWaitForAnyKey(QString strName, QString strDescription) :
Superclass(strName, strDescription)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

int qbuCmdWaitForAnyKey::Execute()
{
    std::cout << "Press Enter to continue!" << std::endl;

    QTextStream qin(stdin);
    qin.readLine();  // Waits for Enter key

    return QCmdParseError::STATUS_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////
