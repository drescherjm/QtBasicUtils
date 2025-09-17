#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuDatabaseFunctions.h"
#include <QRegularExpression>
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

bool isAValidExpression(QString str)
{
	bool retVal = beginsAndEnds(str, '(', ')');

	if (retVal) {
		QString strTemp = str;

		int nCount = strTemp.length() - 2;

		retVal = (nCount > 0);

		if (retVal) {

			// Remove the '(' and ')' and any outer whitespace
			strTemp = strTemp.mid(1, nCount).trimmed();

			retVal = !strTemp.isEmpty();

			if (retVal) {
				retVal = strTemp.contains(QRegularExpression("[A-Za-z0-9]"));
			}
		}	
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool isValidFunctionParamaters(QString str)
{
	bool retVal = beginsAndEnds(str, '(', ')');

	if (retVal) {
		QString strTemp = str;

		int nCount = strTemp.length() - 2;

		retVal = (nCount > 0);

		if (retVal) {

			// Remove the '(' and ')' and any outer whitespace
			strTemp = strTemp.mid(1, nCount).trimmed();

			retVal = !strTemp.isEmpty();

			if (retVal) {
				retVal = strTemp.contains(QRegularExpression("[A-Za-z0-9]"));

				if (!retVal) {
					// Support count(*) ...
					retVal = (strTemp.compare("*") == 0);
				}

			}
		}
		else {
			retVal = true;
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool isSQLFunction(QString str)
{
	QRegExp regExp("\\s*[a-z_]+\\(.*\\)\\s*", Qt::CaseInsensitive);

	bool retVal = regExp.exactMatch(str);
	if (retVal) {
		int nBegin = str.indexOf('(');
		int nEnd = str.lastIndexOf(')');

		retVal = ((nEnd > nBegin) && (nBegin > 0));
		if (retVal) {

			QString strTemp = str.mid(nBegin, ++nEnd - nBegin);

			retVal = isValidFunctionParamaters(strTemp);
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString singleQuoteIfNotQuoted(QString str)
{
	QString retVal = str;

	if (str.isEmpty() || !str.startsWith('\'')) {
		retVal.prepend("\'");
		retVal.append("\'");
	}

	return retVal;
}


/////////////////////////////////////////////////////////////////////////////////////////

QString doubleQuoteIfNotQuoted(QString str)
{
	QString retVal = str;

	if (str.isEmpty() || !str.startsWith('\"')) {
		retVal.prepend("\"");
		retVal.append("\"");
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString singleQuoteIfNecissary(QString str)
{
    QString retVal = str;

    if (!str.isEmpty()) {
        QRegExp reg("\\d+|\\d+\\.\\d+|\\-\\d+\\.\\d+|\\-\\d+");

        if (!reg.exactMatch(str)) {
            if ( !isAValidExpression(str) 
                && !beginsAndEnds(str, '\'', '\'') 
                && !beginsAndEnds(str, '\"', '\"')
                && !beginsAndEnds(str, '[', ']')) {
                if (!isSQLFunction(str)) {

                    // BUG_FIX: Single quotes inside a string constant need to be doubled to escape them.
                    retVal.replace('\'', "\'\'");
                    retVal.replace(QRegExp(";\\s\\n"), ";\n");

                    retVal.prepend("\'");
                    retVal.append("\'");
                }
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
        if ( !beginsAndEnds(str,'(',')') 
            && !beginsAndEnds(str,'\'','\'') 
            && !beginsAndEnds(str,'\"','\"')
            && !beginsAndEnds(str, '[', ']')) {
            if (!isSQLFunction(str)) {
                retVal.prepend("\"");
                retVal.append("\"");
            }
        }
        
    }
    return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

extern QString addBracketsForIdentifierIfNecissary(QString str)
{
	QString retVal = str;
	if (str.contains(QRegExp("\\s+"))) {
		if (!beginsAndEnds(str, '(', ')') && !beginsAndEnds(str, '\'', '\'') 
            && !beginsAndEnds(str, '\"', '\"')
            && !beginsAndEnds(str, '[', ']')) {
			if (!isSQLFunction(str)) {
				retVal.prepend("[");
				retVal.append("]");
			}
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
            if (!isSQLFunction(str)) {
                retVal.prepend("\"");
                retVal.append("\"");
            }
        }

    }
    else if ( !str.isEmpty() && (str[0].isDigit() || (str.contains('#') )) ) {
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
        QString str = vt.toString();
        if (str.isEmpty()) {
            //std::cerr << "Got a blank string! in: " << __FUNCTION__ << std::endl;
            retVal = "\'\'";
        }
        else
        {
			if (isSQLFunction(str)) {
				// I don't believe any functions should be in this data.
				str.prepend("\'");
				str.append("\'");
			}
            retVal = singleQuoteIfNecissary(str);
        }
        
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

extern QString removeOuterParenthesis(QString strExpr)
{
	if (strExpr.startsWith('(') && strExpr.endsWith(')')) {
		strExpr.chop(1);
		strExpr.remove(0, 1);
	}
	return strExpr;
}

/////////////////////////////////////////////////////////////////////////////////////////

extern bool hasOuterParenthesis(QString str)
{
    str = str.trimmed();
    return str.startsWith('(') && str.endsWith(')');
}

/////////////////////////////////////////////////////////////////////////////////////////

extern QString addOuterParenthesisIfNecissary(QString str)
{
    if (!hasOuterParenthesis(str)) {
        str.prepend(" ( ").append(" ) ");
    }
    return str;
}

/////////////////////////////////////////////////////////////////////////////////////////
