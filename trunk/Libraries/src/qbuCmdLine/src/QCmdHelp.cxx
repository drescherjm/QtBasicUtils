#include "qbuCmdLinePCH.h"

#include "qbuCmdLine/QCmdHelp.h"
#include "qbuCmdLine/QCmdHelpException.h"
#include "qbuCmdLine/QCmdParseError.h"

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmdHelp::g_strOPTBrief("b");

/////////////////////////////////////////////////////////////////////////////////////////

QCmdHelp::QCmdHelp(QString strDescription, QString strExplanation) :
QCmd("?", strDescription, strExplanation)
{
	m_pCmdLine = NULL;
	EndRequiredArguments();

	bool bBrief = false;
	AddOpt(g_strOPTBrief, "Show commands only.", "This will omit the description and options section from the output", bBrief);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdHelp::Execute()
{
	QCmdLine* pCmdLine = GetCmdLine();
	if (pCmdLine) {

		bool bBrief = false;
		GetOpt(g_strOPTBrief, bBrief);

		QCmdHelpException::Throw(pCmdLine->GetSyntax(bBrief));
	}
	return QCmdParseError::STATUS_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////

QCmdLine* QCmdHelp::GetCmdLine()
{
	return m_pCmdLine;
}

/////////////////////////////////////////////////////////////////////////////////////////
