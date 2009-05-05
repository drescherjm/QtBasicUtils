#include "QCmdOpt.h"

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

QCmdOpt::QCmdOpt(QString strName,QString strDescription, QString strExplanation) : 
 QNamedCmdPart(strName,strDescription,strExplanation)
{

}

QCmdOpt::~QCmdOpt()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

bool QCmdOpt::isExtendedOption()
{
	return (m_strName.length() > 1);
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmdOpt::GetShortSyntax()
{
	QString retVal;
	if (!isExtendedOption()) {
		retVal = GetName()+ getValueDescription();
	}
	else
	{
		retVal = GetName() + "="+getValueDescription();
	}
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

QString QCmdOpt::exportOptionName()
{
	QString retVal;
	if (!isExtendedOption()) {
		retVal = "-" + GetName();
	}
	else
	{
		retVal = "--" + GetName() + "=";
	}
	return retVal;		
}

/////////////////////////////////////////////////////////////////////////////////////////

}; //namespace QTUTILS