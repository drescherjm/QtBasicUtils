#include "QCmdParseException.h"

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

	QString QCmdParseError::GetErrorString(quint32 nErrorCode, QString str0, QString str1,QString str2)
	{
		QString strError;
		switch( nErrorCode ) {
	case STATUS_OK:
		strError = ("No Error. %1%2%3");
		break;
	case PARAM_NOT_OPTION:
		strError = ("PARAM_NOT_OPTION %1%2%3");
		break;
	case INVALID_OPTION_NAME:
		strError = ("ERROR: INVALID_OPTION_NAME %1 when parsing the command %2 %3");
		break;
	case PARAM_EXTRA_DATA: 
		strError = ("ERROR: Found extra data while parsing parameter%1. %2%3");
		break;
	case PARAM_MISSING_DATA:
		strError = ("ERROR: The parameter %s was missing data%1. %2%3");
		break;
	case PARAM_TOO_BIG:
		strError = ("PARAM_TOO_BIG %1 %2%3");
		break;
	case PARAM_TOO_SMALL:
		strError = ("PARAM_TOO_SMALL %1 %2%3");
		break;
	case PARAM_INVALID_DATA:
		strError = ("PARAM_INVALID_DATA %1 %2%3");
		break;
	case PARAM_ALLREADY_SET:
		strError = ("PARAM_ALLREADY_SET %1 %2%3");
		break;
	case OPTION_ALLREADY_ADDED:
		strError = ("OPTION_ALLREADY_ADDED %1");
		break;
	case OPTION_NOT_FOUND:
		if ( !str1.isEmpty() ) {
			strError = ("ERROR: The option -%1 was not defined for the command %2.%3");
		}
		else
		{
			strError = ("ERROR:  The option -%1 was not defined for this this command. %2%3");
		}

		str2 = QString("\nNOTE: This is normally caused by a call to GetOpt() with something passed that is not defined as an option.");
		if (str0.length() > 1) {
			str0.prepend("-");
		}
		break;
	case OPTION_WRONG_TYPE:
		strError = ("OPTION_WRONG_TYPE %1 %2%3");
		break;
	case ARGUMENT_ALLREADY_ADDED:
		strError = ("ARGUMENT_ALLREADY_ADDED %1 %2%3");
		break;
	case ARGUMENT_NOT_FOUND:
		strError = ("ARGUMENT_NOT_FOUND %1 %2%3");
		break;
	case ARGUMENT_WRONG_TYPE:
		strError = ("ARGUMENT_WRONG_TYPE %1 %2%3");
		break;
	case TOO_MANY_ARGUMENTS:
		strError = ("TOO_MANY_ARGUMENTS %1%2 %3");
		break;
	case NOT_ENOUGH_ARGUMENTS:
		strError = ("NOT_ENOUGH_ARGUMENTS %1 %2%3");
		break;
	case COMMAND_ALLREADY_ADDED:
		strError = ("COMMAND_ALLREADY_ADDED %1 %2%3");
		break;
	case PARAM_NOT_COMMAND:
		strError = ("PARAM_NOT_COMMAND %1 %2%3");
		break;
	case COMMAND_NOT_SEPARATED:
		strError = ("COMMAND_NOT_SEPARATED %1 %2%3");
		break;
	case MEMORY_ALLOCATION_ERROR:
		strError = ("MEMORY_ALLOCATION_ERROR %1 %2%3");
		break;
	case MEMORY_CORRUPTION_ERROR:
		strError = ("MEMORY_CORRUPTION_ERROR %1 %2%3");
		break;
	case FOLDER_MUST_EXIST:
		strError = ("FOLDER_MUST_EXIST %1. The user specified a path that does not exist %2 %3");
		break;
	case FILE_MUST_EXIST:
		strError = ("FILE_MUST_EXIST %1. The user specified a file that does not exist %2 %3");
		break;
	case FILE_MUST_NOT_EXIST:
		strError = ("FILE_MUST_NOT_EXIST %1. The user specified a file that exists %2, but the program requires a unique file name. %3");
		break;
	case FILE_NOT_IN_CWD:
		strError = ("FILE_NOT_IN_CWD %1. The program requires that the file %2 is in the current working directory. %3");
		break;
	case MUST_BE_FILE:
		strError = ("MUST_BE_FILE %1. The parameter %2 must be the name of a file. %3");
		break;
	case MUST_BE_FOLDER:
		strError = ("MUST_BE_FOLDER %1. The parameter %2 must be the name of a folder. %3");
		break;
	case USER_EXECUTION_ERROR:
		strError = ("USER_EXECUTION_ERROR %1. An error occurred executing the command %2%3");
		break;
	default:
		strError = ("ERROR: Unknown parse error. %1 %2 %3");
		break;
		}
		QString retVal = QString(strError).arg(str0).arg(str1).arg(str2);
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	bool QCmdParseError::SUCCEEDED( quint32 nErrorCode )
	{
		return nErrorCode == STATUS_OK;
	}

/////////////////////////////////////////////////////////////////////////////////////////

}; //namespace QTUTILS
