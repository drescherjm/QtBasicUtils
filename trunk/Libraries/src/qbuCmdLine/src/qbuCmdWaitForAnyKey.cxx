#include "qbuCmdLinePCH.h"

#include "qbuCmdLine/qbuCmdWaitForAnyKey.h"
#include <conio.h>
#include <iostream>
#include "qbuCmdLine/QCmdParseError.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuCmdWaitForAnyKey::qbuCmdWaitForAnyKey(QString strName, QString strDescription) :
Superclass(strName,strDescription)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

int qbuCmdWaitForAnyKey::Execute()
{

	std::cout << "Press any key continue!" << std::endl;

	getch();

	return QCmdParseError::STATUS_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////
