#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuDBColumnDefList.h"

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuDBColumnDefList::toString(size_t nWordWrapAt/* =0 */)
{
	QString retVal;

    if (nWordWrapAt == 0) {
        iterator it = begin();
        for (; it != end(); ++it) {
            if (!retVal.isEmpty()) {
                retVal.append(", ");
            }
            retVal.append(it->getFullString());
        }
    }
    else {

        bool bFirst = true;
        bool bLong = false;

        QString strLine;

        iterator it = begin();
        for (; it != end(); ++it) {
            if (!bFirst) {
                strLine.append(", ");
            }
            else {
                bFirst = false;
            }

            QString str = it->getFullString();

            int nLineLength = strLine.length();
            
            if (((nLineLength + str.length() + 2) > nWordWrapAt) && (nLineLength > 0) ) {
                retVal.append(strLine + "\n\t");
                strLine = str;
            }
            else {
                strLine.append(str);
            }
        }
        retVal.append(strLine);
    }

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////
