#include "qbuDBBasePCH.h"
#include "qbuInfo.h"
#include <QStringList>
#include "qbuMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////

QBU_IMPLEMENT_ASSIGNMENT_OPERATOR_BASE(qbuInfo);

/////////////////////////////////////////////////////////////////////////////////////////

qbuInfo::qbuInfo() : Superclass()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuInfo::qbuInfo( const qbuInfo & other )
{
	// Do not call copy() here. That will cause a pure virtual call to getDBFieldNames()
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuInfo::isDBField( QString strField ) const
{
	const QStringList& lst = getDBFieldNames();
	bool retVal = !lst.isEmpty();
	if (retVal) {
		retVal = lst.contains(strField.trimmed(),Qt::CaseInsensitive);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuInfo::destroy()
{
	clear();
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	This will copy only the valid properties from other to this qbuInfo instance.
 */

void qbuInfo::copy( const qbuInfo & other )
{
	copy(&other);
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuInfo::copy( const PropertyMap * other )
{
	if (other != NULL) {
		const QStringList& lst = getDBFieldNames();
		foreach(QString str,lst) {
			CopyProperty(str,*other);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	This overrides the base behavior of copying every Property to only copying the 
 *  properties that are valid for thus qbuInfo instance.
 */

void qbuInfo::addProperties( PropertyMap * other )
{
	copy(other);
}
