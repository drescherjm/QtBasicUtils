#include "testDBExpression.h"
#include "qbuCmdLine/QCmdParseError.h"
#include "qbuCmdLine/QCmdLine.h"
#include <QFile>
#include <iostream>
#include "qbuDataBase/qbuDBCondition.h"
#include "qbuDataBase/qbuDBExpression.h"

/////////////////////////////////////////////////////////////////////////////////////////

CmdTestDBExpression::CmdTestDBExpression( QString strName, QString strDescription ) : 
	QCmd(strName,strDescription)
{
	int nTest = 0;
	AddArg("Test", "Run test #", "", nTest);
}

/////////////////////////////////////////////////////////////////////////////////////////

int CmdTestDBExpression::Execute()
{
	int nTest;

	GetArg("Test", nTest);

	bool bVal;
	switch (nTest) {
	case 0:
		bVal = test0();
		break;
	case 1:
		bVal = test1();
		break;
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

bool CmdTestDBExpression::test0()
{
	const QString g_strConnectionDurationTotalSeconds{ "DurationTotalSeconds" };

	qbuDBCondition condExprDurationDaysMod{ g_strConnectionDurationTotalSeconds,QString::number(60 * 60 * 24),"%",true };

	qbuDBExpression expr{ condExprDurationDaysMod,true };

	qbuDBCondition condExprDurationInHours{expr,QString::number(60),"/",true };

	QString strVal = condExprDurationInHours.toString().simplified().remove(' ');

	const QString strExpected{ "((DurationTotalSeconds%86400)/60)" };

	bool retVal = { strVal.compare(strExpected, Qt::CaseInsensitive) == 0 };

	displayComparisonMessageIfFalse(retVal, strExpected, strVal);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool CmdTestDBExpression::test1()
{
	const QString g_strConnectionDurationTotalSeconds{ "DurationTotalSeconds" };

	auto expr = qbuDBExpression::printf("%02d", QList<qbuDBColDef>{qbuDBColDef{ g_strConnectionDurationTotalSeconds }, });

	QString strVal = expr.toString();

	const QString strExpected{ " printf( '%02d', DurationTotalSeconds ) " };

	bool retVal = { strVal.compare(strExpected, Qt::CaseInsensitive) == 0 };

	displayComparisonMessageIfFalse(retVal, strExpected, strVal);

	return retVal;
}


/////////////////////////////////////////////////////////////////////////////////////////

void CmdTestDBExpression::displayComparisonMessageIfFalse(bool retVal, const QString strExpected, const QString strVal)
{
	if (!retVal) {
		std::cerr << qPrintable(QString("In %1 the output did not match. \n Expected: %2 \n Actual:   %3").arg(__FUNCTION__).arg(strExpected,strVal));
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
