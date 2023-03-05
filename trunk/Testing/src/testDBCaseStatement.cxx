#include "testDBCaseStatement.h"
#include "qbuCmdLine/QCmdParseError.h"
#include "qbuCmdLine/QCmdLine.h"
#include <QFile>
#include <iostream>
#include "qbuDataBase/qbuDBCondition.h"
#include "qbuDataBase/qbuDBCaseStatement.h"

/////////////////////////////////////////////////////////////////////////////////////////

CmdTestDBCaseStatement::CmdTestDBCaseStatement( QString strName, QString strDescription ) : 
	QCmd(strName,strDescription)
{
	int nTest = 0;
	AddArg("Test", "Run test #", "", nTest);
}

/////////////////////////////////////////////////////////////////////////////////////////

int CmdTestDBCaseStatement::Execute()
{
	int nTest;

	GetArg("Test", nTest);

	bool bVal;
	switch (nTest) {
	case 0:
		bVal = test0();
		break;
// 	case 1:
// 		bVal = test1();
// 		break;
// 	case 2:
// 		bVal = test2();
// 		break;
// 	case 5:
// 		bVal = test5();
// 		break;
	default:
		bVal = false;
	}

	return bVal ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool CmdTestDBCaseStatement::test0()
{
	const QString g_strConnectionDurationInDays{ "DurationDays" };

	qbuDBCondition condExprDurationDays{ g_strConnectionDurationInDays,QString::number(0),">",true };

	qbuDBCaseStatement daysCaseStatement;

	daysCaseStatement.addCase(condExprDurationDays.toString(), QString("%1 || ' Days '").arg(g_strConnectionDurationInDays));

	QString strVal = daysCaseStatement.toString().simplified();

	const QString strExpected{ "CASE WHEN ( DurationDays > 0 ) THEN DurationDays || ' Days ' END" };

	bool retVal = { strVal.compare(strExpected, Qt::CaseInsensitive) == 0 };

	displayComparisonMessageIfFalse(retVal, strExpected, strVal);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void CmdTestDBCaseStatement::displayComparisonMessageIfFalse(bool retVal, const QString strExpected, const QString strVal)
{
	if (!retVal) {
		std::cerr << qPrintable(QString("In %1 the output did not match. \n Expected: %2 \n Actual:   %3").arg(__FUNCTION__).arg(strExpected).arg(strVal));
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
