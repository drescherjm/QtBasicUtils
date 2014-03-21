#ifndef __QCMDHELP_H__
#define __QCMDHELP_H__

#include "QCmd.h"
#include "QCmdLine.h"

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

	class QCmdHelp : public QCmd
	{
		friend class QCmdLine;
	public:
		QCmdHelp(QString strDescription, QString strExplanation);
		virtual int Execute();
	protected:
		QCmdLine*	GetCmdLine();
	private:
		QCmdLine*	m_pCmdLine;
	};


/////////////////////////////////////////////////////////////////////////////////////////

}; // namespace QTUTILS

#endif //__QCMDHELP_H__
