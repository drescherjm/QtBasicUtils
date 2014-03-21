#include "testSetVariable.h"
#include "qbuCmdLine/QCmdParseError.h"
#include "qbuCmdLine/QCmdLine.h"
#include <QFile>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////////

CmdTestSetVar::CmdTestSetVar( QString strName, QString strDescription ) : 
	QCmd(strName,strDescription)
{
	QString str;
	AddOpt("group","This sets the group of the variable.","",str);
	AddOpt("name","This sets the name of the variable.","",str);
	AddOpt("fullname","This sets the group and name of the variable.","",str);
	AddArg("value","The value of the variable","",str);
}

/////////////////////////////////////////////////////////////////////////////////////////

int CmdTestSetVar::Execute()
{
	QString strName;

	int retVal = GetOpt("fullname",strName,QCmd::REMOVE_OUTER_QUOTES);

	if (QCmdParseError::Succeeded(retVal)) {
		if (strName.isEmpty()) {
			retVal = GetOpt("name",strName,QCmd::REMOVE_OUTER_QUOTES);
			if (QCmdParseError::Succeeded(retVal)) {
				retVal = !strName.isEmpty() ? QCmdParseError::STATUS_OK : QCmdParseError::PARAM_INVALID_DATA;
				if (QCmdParseError::Succeeded(retVal)) {
					QString strGroup;
					retVal = GetOpt("group",strGroup,QCmd::REMOVE_OUTER_QUOTES);
					if (QCmdParseError::Succeeded(retVal)) {
						retVal = !strGroup.isEmpty() ? QCmdParseError::STATUS_OK : QCmdParseError::PARAM_INVALID_DATA;
						if (QCmdParseError::Succeeded(retVal)) {
							strGroup = strGroup.trimmed() + "/";

							strName = strGroup + strName.trimmed();
						}
					}
				}
			}
		}
	}

	if (QCmdParseError::Succeeded(retVal)) {

		QString strValue;

		retVal = GetArg("value",strValue,QCmd::REMOVE_OUTER_QUOTES);

		if (QCmdParseError::Succeeded(retVal)) {
			retVal = !strValue.isEmpty() ? QCmdParseError::STATUS_OK : QCmdParseError::PARAM_INVALID_DATA;
			if (QCmdParseError::Succeeded(retVal)) {
				std::cout << qPrintable(strName) << " = " << qPrintable(strValue) << std::endl;
			}
		}
	}
	return retVal;
}

