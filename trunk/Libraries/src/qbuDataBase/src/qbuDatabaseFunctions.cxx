#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuDatabaseFunctions.h"
#include <QRegExp>
#include <QVariant>

/////////////////////////////////////////////////////////////////////////////////////////

bool beginsAndEnds(QString str,QChar delimStart,QChar delimEnd)
{
	str = str.trimmed();
	bool retVal = (str.length() > 1);
	if (retVal) {
		retVal = str.startsWith(delimStart);
		if (retVal) {
			retVal = str.endsWith(delimEnd);
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool isSQLFunction(QString str)
{
	QRegExp regExp("\\s*[a-z_]+\\(.*\\)\\s*",Qt::CaseInsensitive);
	
	return regExp.exactMatch ( str );
}

/////////////////////////////////////////////////////////////////////////////////////////

QString singleQuoteIfNecissary(QString str)
{
	QString retVal = str;
	if (str.contains(QRegExp("\\s+"))) {
		if ( !beginsAndEnds(str,'(',')') && !beginsAndEnds(str,'\'','\'') && !beginsAndEnds(str,'\"','\"')) {
			if (!isSQLFunction(str)) {
				retVal.prepend("\'");
				retVal.append("\'");
			}
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString doubleQuoteIfNecissary(QString str)
{
	QString retVal = str;
	if (str.contains(QRegExp("\\s+"))) {
		if ( !beginsAndEnds(str,'(',')') && !beginsAndEnds(str,'\'','\'') && !beginsAndEnds(str,'\"','\"')) {
			retVal.prepend("\"");
			retVal.append("\"");
		}
		
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

extern QString quoteSQLObjectNameIfNecissary(QString str)
{
	QString retVal = str;
	if (str.contains(QRegExp("\\s+"))) {
		if (!beginsAndEnds(str, '(', ')') && !beginsAndEnds(str, '\'', '\'') && !beginsAndEnds(str, '\"', '\"')) {
			retVal.prepend("\"");
			retVal.append("\"");
		}

	}
	else if ( !str.isEmpty() && str[0].isDigit() ) {
		retVal.prepend("\"");
		retVal.append("\"");
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

extern QString toQueryValue(QVariant & vt)
{
	QString retVal;

	if (vt.type() == QVariant::Bool) {
		vt = vt.toBool() ? QVariant(int(1)) : QVariant(int(0));
	}

	switch(vt.type()) {
	case QVariant::Int:
	case QVariant::UInt:
	case QVariant::LongLong:
	case QVariant::ULongLong:
	case QVariant::Double:
	case QVariant::Char:
		retVal = vt.toString();
		break;
	case QVariant::DateTime:
	case QVariant::Date:
	case QVariant::Time:
		retVal = "\'" + vt.toString() + "\'";
		break;
	default:
		retVal = singleQuoteIfNecissary(vt.toString());
		break;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

extern QString toQueryValue(const QVariant & vt)
{
	QVariant val = vt;
	return toQueryValue(val);
}

/////////////////////////////////////////////////////////////////////////////////////////
