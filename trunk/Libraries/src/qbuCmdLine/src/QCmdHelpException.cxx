#include "qbuCmdLine/QCmdHelpException.h"

namespace QTUTILS {

	void QCmdHelpException::Throw(QString str0)
	{
		QCmdHelpException* pExcept = new QCmdHelpException(str0);
		throw pExcept;

	}

	void QCmdHelpException::Delete()
	{
		delete this;
	}


}; //namespace QTUTILS
