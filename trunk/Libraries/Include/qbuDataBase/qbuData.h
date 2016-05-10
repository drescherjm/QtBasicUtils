#pragma once

#ifndef QBUDATA_H
#define QBUDATA_H

#include "qbuDataBase/qbuDataBaseLibraryDefines.h"
#include "qbuBase/qbuObject.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuDataBase_EXPORT qbuData : public qbuObject
{
	QBU_DECLARE_SUPERCLASS(qbuObject);
	Q_OBJECT
public:
	explicit qbuData(QObject* pParent = nullptr);
	virtual ~qbuData();
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUDATA_H
