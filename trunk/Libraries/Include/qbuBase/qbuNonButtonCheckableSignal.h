#pragma once

#ifndef QBUNONBUTTONCHECKABLESIGNAL_H
#define QBUNONBUTTONCHECKABLESIGNAL_H

#include "qbuBase/qbuButtonSignalBase.h"
#include <memory>

/////////////////////////////////////////////////////////////////////////////////////////

class qbuBase_EXPORT qbuNonButtonCheckableSignal : public qbuButtonSignalBase
{
	Q_OBJECT
	QBU_DECLARE_SUPERCLASS(qbuButtonSignalBase)
public:
	explicit qbuNonButtonCheckableSignal(QObject* pParent = nullptr);
	~qbuNonButtonCheckableSignal();

	enum ButtonMode {
		BS_NORMAL,
		BS_INVERTED
	};

public:
	virtual void setChecked(bool bChecked);
	void	setMode(ButtonMode md);
	bool	setObject(QObject* pTriggerObject, const char * method = SIGNAL(toggled(bool)),
		Qt::ConnectionType atype = Qt::AutoConnection);

public:
	virtual bool isChecked();

protected slots:
	void	buttonToggledInt(bool bChecked);

private:
	class qbuPrivate;
	std::unique_ptr<qbuPrivate> m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUNONBUTTONCHECKABLESIGNAL_H
