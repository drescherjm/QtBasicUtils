#pragma once

#ifndef TESTXMLPERF_H
#define TESTXMLPERF_H

#include "qbuCmdLine/QCmd.h"
#include <memory>

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdTestXMLPerformance : public QCmd
{
public:
	QCmdTestXMLPerformance(QString strName, QString strDescription);
    ~QCmdTestXMLPerformance();
	virtual int Execute();
private:
    struct qbuPrivate;

    std::unique_ptr<qbuPrivate>  m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // TESTXMLPERF_H

