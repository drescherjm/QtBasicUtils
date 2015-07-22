#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuDBColumnDefList.h"

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuDBColumnDefList::toString()
{
	QString retVal;

	iterator it = begin();
	for (; it != end(); ++it) {
		if (!retVal.isEmpty()) {
			retVal.append(", ");
		}
		retVal.append(it->getFullString());
	}
	return retVal;
}
