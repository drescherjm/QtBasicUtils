#include "smDBBasePCH.h"
#include "smInfo.h"
#include <QStringList>
#include "smMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////

SM_IMPLEMENT_ASSIGNMENT_OPERATOR_BASE(smInfo);

/////////////////////////////////////////////////////////////////////////////////////////

smInfo::smInfo() : Superclass()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

smInfo::smInfo( const smInfo & other )
{
	// Do not call copy() here. That will cause a pure virtual call to getDBFieldNames()
}

/////////////////////////////////////////////////////////////////////////////////////////

bool smInfo::isDBField( QString strField ) const
{
	const QStringList& lst = getDBFieldNames();
	bool retVal = !lst.isEmpty();
	if (retVal) {
		retVal = lst.contains(strField.trimmed(),Qt::CaseInsensitive);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void smInfo::destroy()
{
	clear();
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	This will copy only the valid properties from other to this smInfo instance.
 */

void smInfo::copy( const smInfo & other )
{
	copy(&other);
}

/////////////////////////////////////////////////////////////////////////////////////////

void smInfo::copy( const PropertyMap * other )
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
 *  properties that are valid for thus smInfo instance.
 */

void smInfo::addProperties( PropertyMap * other )
{
	copy(other);
}
