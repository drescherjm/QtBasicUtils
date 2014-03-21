#include "testSetVariable.h"
#include "QCmdParseError.h"
#include "QCmdLine.h"
#include <QFile>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////////

QTUTILS::CmdTestSetVar::CmdTestSetVar( QString strName, QString strDescription ) : 
	QCmd(strName,strDescription)
{
	QString str;
	AddOpt("group","This sets the group of the variable.","",str);
	AddOpt("name","This sets the name of the variable.","",str);
	AddOpt("fullname","This sets the group and name of the variable.","",str);
	AddArg("value","The value of the variable","",str);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QTUTILS::CmdTestSetVar::Execute()
{
	QString strName;

	int retVal = GetOpt("fullname",strName,QCmd::REMOVE_OUTER_QUOTES);

	if (QCmdParseError::SUCCEEDED(retVal)) {
		if (strName.isEmpty()) {
			retVal = GetOpt("name",strName,QCmd::REMOVE_OUTER_QUOTES);
			if (QCmdParseError::SUCCEEDED(retVal)) {
				retVal = !strName.isEmpty() ? QCmdParseError::STATUS_OK : QCmdParseError::PARAM_INVALID_DATA;
				if (QCmdParseError::SUCCEEDED(retVal)) {
					QString strGroup;
					retVal = GetOpt("group",strGroup,QCmd::REMOVE_OUTER_QUOTES);
					if (QCmdParseError::SUCCEEDED(retVal)) {
						retVal = !strGroup.isEmpty() ? QCmdParseError::STATUS_OK : QCmdParseError::PARAM_INVALID_DATA;
						if (QCmdParseError::SUCCEEDED(retVal)) {
							strGroup = strGroup.trimmed() + "/";

							strName = strGroup + strName.trimmed();
						}
					}
				}
			}
		}
	}

	if (QCmdParseError::SUCCEEDED(retVal)) {

		QString strValue;

		retVal = GetArg("value",strValue,QCmd::REMOVE_OUTER_QUOTES);

		if (QCmdParseError::SUCCEEDED(retVal)) {
			retVal = !strValue.isEmpty() ? QCmdParseError::STATUS_OK : QCmdParseError::PARAM_INVALID_DATA;
			if (QCmdParseError::SUCCEEDED(retVal)) {
				std::cout << qPrintable(strName) << " = " << qPrintable(strValue) << std::endl;
			}
		}
	}
	return retVal;
}

