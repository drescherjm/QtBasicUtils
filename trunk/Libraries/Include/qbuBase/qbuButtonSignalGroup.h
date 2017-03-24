#pragma once

#ifndef QBUBUTTONSIGNALGROUP_H
#define QBUBUTTONSIGNALGROUP_H

#include <QObject>
#include <qbuBase/qbuMacros.h>
#include <memory>
#include "qbuBase/qbuBaseLibraryDefines.h"
#include "qbuBase/qbuButtonSignalBase.h"

class QAbstractButton;
//class qbuButtonSignalBase;

/////////////////////////////////////////////////////////////////////////////////////////

class qbuBase_EXPORT qbuButtonSignalGroup : public qbuButtonSignalBase
{
	Q_OBJECT
	QBU_DECLARE_SUPERCLASS(qbuButtonSignalBase)
public:
	explicit qbuButtonSignalGroup(QObject* pParent);
	~qbuButtonSignalGroup();

	enum SignalGroupMode {
		BSG_OR,
		BSG_AND,
	};

public:
	bool	addButton(QAbstractButton* pAbstractButton, const char * method = SIGNAL(toggled(bool)));
	bool	addButton(QAbstractButton* pAbstractButton, QObject* pTriggerObject, const char * method = SIGNAL(toggled(bool)));
	bool	addButton(qbuButtonSignalBase* pButtonSignal);
	void	setMode(SignalGroupMode md);

public:
	virtual bool isChecked();

signals:
	void	some_toggled(bool bChecked);

protected slots:
	void	buttonToggledInt(bool bChecked);
	
private:
	class qbuPrivate;
	std::unique_ptr<qbuPrivate> m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUBUTTONSIGNALGROUP_H

