#include "smDBBasePCH.h"
#include "smTableColumnDef.h"
#include "Property.h"
#include "smDatabaseMacros.h"
#include <QStringList>

/////////////////////////////////////////////////////////////////////////////////////////

const QString smTableColumnDef::g_strName("Name");
const QString smTableColumnDef::g_strType("Type");
const QString smTableColumnDef::g_strNotNull("NotNull");
const QString smTableColumnDef::g_strPrimaryKey("PrimaryKey");

/////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SA_GET(smTableColumnDef,Name,QString,smTableColumnDef::g_strName);
IMPLEMENT_SA_GET(smTableColumnDef,Type,QString,smTableColumnDef::g_strType);
IMPLEMENT_SA_GET(smTableColumnDef,NotNull,bool,smTableColumnDef::g_strNotNull);
IMPLEMENT_SA_GET(smTableColumnDef,PrimaryKey,bool,smTableColumnDef::g_strPrimaryKey);

/////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SA_SET(smTableColumnDef,Name,QString,smTableColumnDef::g_strName);
IMPLEMENT_SA_SET(smTableColumnDef,Type,QString,smTableColumnDef::g_strType);
IMPLEMENT_SA_SET(smTableColumnDef,NotNull,bool,smTableColumnDef::g_strNotNull);
IMPLEMENT_SA_SET(smTableColumnDef,PrimaryKey,bool,smTableColumnDef::g_strPrimaryKey);

//Implement the assignment operator
SM_IMPLEMENT_ASSIGNMENT_OPERATOR_DERIVED(smTableColumnDef,Superclass);

/////////////////////////////////////////////////////////////////////////////////////////

smTableColumnDef::smTableColumnDef()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

smTableColumnDef::smTableColumnDef( const smTableColumnDef & other )
{
	Superclass::copy(other);	
}

/////////////////////////////////////////////////////////////////////////////////////////

smTableColumnDef::smTableColumnDef( const Superclass & other ) : Superclass()
{

	// The reason for the unusual code is this avoids a pure virtual call in
	// smInfo::copy()

	Superclass::copy(other);	
}

/////////////////////////////////////////////////////////////////////////////////////////

smTableColumnDef& smTableColumnDef::operator=( const Superclass & other )
{
	Superclass::operator=(other);
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////

void smTableColumnDef::copy( const smTableColumnDef & other )
{

}

/////////////////////////////////////////////////////////////////////////////////////////

void smTableColumnDef::destroy()
{
	clear();
}

/////////////////////////////////////////////////////////////////////////////////////////

const QStringList& smTableColumnDef::getDBFieldNames() const
{
	static QStringList strLstFields;
	if (strLstFields.isEmpty()) {
		strLstFields = QStringList() <<
			smTableColumnDef::g_strName <<
			smTableColumnDef::g_strType <<
			smTableColumnDef::g_strNotNull <<
			smTableColumnDef::g_strPrimaryKey;
	}
	return strLstFields;
}
