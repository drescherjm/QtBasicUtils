#include "QCmdParseException.h"

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

	QString QCmdParseError::GetErrorString(quint32 nErrorCode, QString str0, QString str1,QString str2)
	{
		QString strError;
		switch( nErrorCode ) {
	case STATUS_OK:
		strError = ("No Error.");
		break;
	case PARAM_NOT_OPTION:
		strError = ("PARAM_NOT_OPTION");
		break;
	case PARAM_EXTRA_DATA: 
		strError = ("ERROR: Found extra data while parsing parameter%s.");
		break;
	case PARAM_MISSING_DATA:
		strError = ("ERROR: The parameter %s was missing data%s.");
		break;
	case PARAM_TOO_BIG:
		strError = ("PARAM_TOO_BIG %s");
		break;
	case PARAM_TOO_SMALL:
		strError = ("PARAM_TOO_SMALL %s");
		break;
	case PARAM_INVALID_DATA:
		strError = ("PARAM_INVALID_DATA %s");
		break;
	case PARAM_ALLREADY_SET:
		strError = ("PARAM_ALLREADY_SET %s");
		break;
	case OPTION_ALLREADY_ADDED:
		strError = ("OPTION_ALLREADY_ADDED %s");
		break;
	case OPTION_NOT_FOUND:
		if ( !str1.isEmpty() ) {
			strError = ("ERROR: The option -%s was not defined for the command %s.");
		}
		else
		{
			strError = ("ERROR:  The option -%s was not defined for this this command.");
		}
		break;
	case OPTION_WRONG_TYPE:
		strError = ("OPTION_WRONG_TYPE %s");
		break;
	case ARGUMENT_ALLREADY_ADDED:
		strError = ("ARGUMENT_ALLREADY_ADDED %s");
		break;
	case ARGUMENT_NOT_FOUND:
		strError = ("ARGUMENT_NOT_FOUND %s");
		break;
	case ARGUMENT_WRONG_TYPE:
		strError = ("ARGUMENT_WRONG_TYPE %s");
		break;
	case TOO_MANY_ARGUMENTS:
		strError = ("TOO_MANY_ARGUMENTS %s%s");
		break;
	case NOT_ENOUGH_ARGUMENTS:
		strError = ("NOT_ENOUGH_ARGUMENTS %s");
		break;
	case COMMAND_ALLREADY_ADDED:
		strError = ("COMMAND_ALLREADY_ADDED %s");
		break;
	case PARAM_NOT_COMMAND:
		strError = ("PARAM_NOT_COMMAND %s");
		break;
	case COMMAND_NOT_SEPARATED:
		strError = ("COMMAND_NOT_SEPARATED %s");
		break;
	case MEMORY_ALLOCATION_ERROR:
		strError = ("MEMORY_ALLOCATION_ERROR %s");
		break;
	case MEMORY_CORRUPTION_ERROR:
		strError = ("MEMORY_CORRUPTION_ERROR %s");
		break;
	case FOLDER_MUST_EXIST:
		strError = ("FOLDER_MUST_EXIST %s. The user specified a path that does not exist %s");
		break;
	case FILE_MUST_EXIST:
		strError = ("FILE_MUST_EXIST %s. The user specified a file that does not exist %s");
		break;
	case FILE_MUST_NOT_EXIST:
		strError = ("FILE_MUST_NOT_EXIST %s. The user specified a file that exists %s, but the program requires a unique file name.");
		break;
	case FILE_NOT_IN_CWD:
		strError = ("FILE_NOT_IN_CWD %s. The program requires that the file %s is in the current working directory.");
		break;
	case MUST_BE_FILE:
		strError = ("MUST_BE_FILE %s. The parameter %s must be the name of a file.");
		break;
	case MUST_BE_FOLDER:
		strError = ("MUST_BE_FOLDER %s. The parameter %s must be the name of a folder.");
		break;
	default:
		strError = ("ERROR: Unknown parse error.");
		break;
		}
		QString retVal;
		retVal.sprintf(strError.toAscii(),str0,str1);
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

}; //namespace QTUTILS