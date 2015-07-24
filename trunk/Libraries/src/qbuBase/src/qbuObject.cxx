#include "qbuBasePCH.h"
#include "qbuBase/qbuObject.h"
#include <QVariant>

/////////////////////////////////////////////////////////////////////////////////////////

qbuObject::qbuObject( QObject* pParent ) : Superclass(pParent)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuObject::setLastError( QString strLastError )
{
	QVariant vt = strLastError;
	setProperty("LastError",vt);
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuObject::getLastError()
{
	QString retVal;
	QVariant vt = property("LastError");
	if (vt.isValid()) {
		retVal = vt.toString();
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuObject::appendLastError( QString strLastError )
{
	QString str = getLastError();
	if (!str.isEmpty()) {
		str.append("\n");
	}
	
	setLastError(str + strLastError);
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuObject::prependLastError( QString strLastError )
{
	QString str = getLastError();
	if (!str.isEmpty()) {
		str.prepend("\n");
	}
	setLastError(strLastError + str);
}

/////////////////////////////////////////////////////////////////////////////////////////
