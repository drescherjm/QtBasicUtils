#include "qbuDBBasePCH.h"
#include "qbuTableColumnDef.h"
#include "Property.h"
#include "qbuDatabaseMacros.h"
#include <QStringList>

/////////////////////////////////////////////////////////////////////////////////////////

const QString qbuTableColumnDef::g_strName("Name");
const QString qbuTableColumnDef::g_strType("Type");
const QString qbuTableColumnDef::g_strNotNull("NotNull");
const QString qbuTableColumnDef::g_strPrimaryKey("PrimaryKey");

/////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SA_GET(qbuTableColumnDef,Name,QString,qbuTableColumnDef::g_strName);
IMPLEMENT_SA_GET(qbuTableColumnDef,Type,QString,qbuTableColumnDef::g_strType);
IMPLEMENT_SA_GET(qbuTableColumnDef,NotNull,bool,qbuTableColumnDef::g_strNotNull);
IMPLEMENT_SA_GET(qbuTableColumnDef,PrimaryKey,bool,qbuTableColumnDef::g_strPrimaryKey);

/////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SA_SET(qbuTableColumnDef,Name,QString,qbuTableColumnDef::g_strName);
IMPLEMENT_SA_SET(qbuTableColumnDef,Type,QString,qbuTableColumnDef::g_strType);
IMPLEMENT_SA_SET(qbuTableColumnDef,NotNull,bool,qbuTableColumnDef::g_strNotNull);
IMPLEMENT_SA_SET(qbuTableColumnDef,PrimaryKey,bool,qbuTableColumnDef::g_strPrimaryKey);

//Implement the assignment operator
SM_IMPLEMENT_ASSIGNMENT_OPERATOR_DERIVED(qbuTableColumnDef,Superclass);

/////////////////////////////////////////////////////////////////////////////////////////

qbuTableColumnDef::qbuTableColumnDef()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuTableColumnDef::qbuTableColumnDef( const qbuTableColumnDef & other )
{
	Superclass::copy(other);	
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuTableColumnDef::qbuTableColumnDef( const Superclass & other ) : Superclass()
{

	// The reason for the unusual code is this avoids a pure virtual call in
	// qbuInfo::copy()

	Superclass::copy(other);	
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuTableColumnDef& qbuTableColumnDef::operator=( const Superclass & other )
{
	Superclass::operator=(other);
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuTableColumnDef::copy( const qbuTableColumnDef & other )
{

}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuTableColumnDef::destroy()
{
	clear();
}

/////////////////////////////////////////////////////////////////////////////////////////

const QStringList& qbuTableColumnDef::getDBFieldNames() const
{
	static QStringList strLstFields;
	if (strLstFields.isEmpty()) {
		strLstFields = QStringList() <<
			qbuTableColumnDef::g_strName <<
			qbuTableColumnDef::g_strType <<
			qbuTableColumnDef::g_strNotNull <<
			qbuTableColumnDef::g_strPrimaryKey;
	}
	return strLstFields;
}
