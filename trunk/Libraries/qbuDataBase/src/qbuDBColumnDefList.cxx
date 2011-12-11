#include "smDBBasePCH.h"
#include "smDBColumnDefList.h"

/////////////////////////////////////////////////////////////////////////////////////////

QString smDBColumnDefList::toString()
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
