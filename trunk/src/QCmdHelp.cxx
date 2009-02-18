#include "QCmdHelp.h"
#include "QCmdHelpException.h"
#include "QCmdParseError.h"

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdHelp::QCmdHelp(QString strDescription, QString strExplanation) :
	QCmd("?",strDescription,strExplanation)
	{
		m_pCmdLine = NULL;
		EndRequiredArguments();
	}

/////////////////////////////////////////////////////////////////////////////////////////

	int QCmdHelp::Execute()
	{
		QCmdLine* pCmdLine = GetCmdLine();
		if ( pCmdLine ) {
			QCmdHelpException::Throw(pCmdLine->GetSyntax());
		}
		return QCmdParseError::STATUS_OK;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdLine* QCmdHelp::GetCmdLine()
	{
		return m_pCmdLine;
	}

}; //namespace QTUTILS