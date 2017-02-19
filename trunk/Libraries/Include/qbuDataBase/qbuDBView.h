#pragma once

#ifndef QBUDBVIEW_H
#define QBUDBVIEW_H

class qbuDatabase;
class qbuPropertyMap;
class qbuInfo;

#include "qbuDataBase/qbuDataBaseLibraryDefines.h"
#include <QObject>

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	This is the base class for all database Database Views.
 *
 *	\ingroup qbuDatabase
 */

class qbuDataBase_EXPORT qbuDBView : public QObject
{
public:
	qbuDBView(std::shared_ptr<qbuDatabase> pDataBase);

public:
	virtual bool		upgradeDBView(int nOldSchema, int nNewSchema, bool bForceUpdate=false);

	virtual bool		verifySchema();
	virtual QString		getDBViewName() const =0;
	virtual const QStringList&	getFieldList() const;
	virtual bool				verifyRequiredFields(qbuInfo * pInfo, const QStringList & lst) const;

protected:
	virtual bool	    dropView();
	virtual bool		renameDBView(QString strNewName);
	virtual bool		createDBView(int nSchema)=0;
	virtual bool		internalCreateDBView(QString strDBViewName, QString strDBViewSQL, bool bTempView=false);

	virtual	bool		isValidField(QString strName);
    virtual bool        viewNeedsUpdate(int nNewSchema, bool bForceUpdate);
protected:
	std::shared_ptr<qbuDatabase>		m_pDB;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUDBVIEW_H
