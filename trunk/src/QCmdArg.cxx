#include "QCmdArg.h"

namespace QTUTILS {

	/////////////////////////////////////////////////////////////////////////////////////////

	QCmdArg::QCmdArg(QString strName,QString strDescription, QString strExplanation) : 
m_strName(strName), QCmdPart(strDescription,strExplanation)
{
	m_bOptional = false;
}

QCmdArg::~QCmdArg()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

}; //namespace QTUTILS