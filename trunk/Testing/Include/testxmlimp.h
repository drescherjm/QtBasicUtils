#pragma once

#ifndef TESTXMLIMP_H
#define TESTXMLIMP_H

#include "qbuCmdLine/QCmd.h"

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdTestXMLImport : public QCmd
{
public:
	QCmdTestXMLImport(QString strName, QString strDescription);
	virtual int Execute();
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // TESTXMLIMP_H
