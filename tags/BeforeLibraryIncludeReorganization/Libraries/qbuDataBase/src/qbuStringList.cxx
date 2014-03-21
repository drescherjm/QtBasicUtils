#include "qbuStringList.h"

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuStringList::toCSVString()
{
	return toDelimitedString(", ");
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuStringList::toDelimitedString( QString delimiter/*=","*/ )
{
	QString retVal;
	if (!isEmpty()) {
		QStringList::iterator it = begin();
		retVal.push_back(QString("%1").arg(*it));
		for(++it;it != end();++it) {
			retVal.push_back(QString("%1%2").arg(delimiter).arg(*it));	
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This member function adds a case insensitive removeAll. 
 *	\details
 *	If you call this with cs set to Qt::CaseInsensitive the remove all will be case 
 *	insensitive. Otherwise the case sensitive Qt implementation will be called.
 *
 */

int qbuStringList::removeAll( QString strRemove,Qt::CaseSensitivity cs )
{
	int retVal=0;

	if (cs == Qt::CaseInsensitive) {
		int pos=0;
		while ( (pos=indexOf(strRemove,Qt::CaseInsensitive,pos)) >= 0) {
			removeAt(pos);
			retVal++;
		}
	}
	else
	{
		// We are dong a case sensitive removeAll. The base class can handle that..
		retVal = Superclass::removeAll(strRemove);
	}
	
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This member function adds a case insensitive indexOf. 
 *	\details
 *	If you call this with cs set to Qt::CaseInsensitive the indexOf will be case 
 *	insensitive. Otherwise the case sensitive Qt implementation will be called.
 *
 */

int qbuStringList::indexOf( const QString & str, Qt::CaseSensitivity cs, int from/*=0*/ ) const
{
	int retVal = -1;
	if (cs == Qt::CaseInsensitive) {
		QRegExp reg(str,cs);
		retVal = Superclass::indexOf(reg,from);
	}
	else
	{
		retVal = Superclass::indexOf(str,from);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This member function adds a case insensitive lastIndexOf. 
 *	\details
 *	If you call this with cs set to Qt::CaseInsensitive the lastIndexOf will be case 
 *	insensitive. Otherwise the case sensitive Qt implementation will be called.
 *
 */

int qbuStringList::lastIndexOf( const QString & str, Qt::CaseSensitivity cs, int from/*=-1*/ ) const
{
	int retVal = -1;
	if (cs == Qt::CaseInsensitive) {
		QRegExp reg(str,cs);
		retVal = Superclass::lastIndexOf(reg,from);
	}
	else
	{
		retVal = Superclass::lastIndexOf(str,from);
	}
	return retVal;
}

