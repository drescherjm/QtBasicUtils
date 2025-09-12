#pragma once

#ifndef QBUBUTTONSIGNAL_H
#define QBUBUTTONSIGNAL_H

#include "qbuBase/qbuButtonSignalBase.h"
#include <memory>

class QAbstractButton;

/////////////////////////////////////////////////////////////////////////////////////////

class qbuBase_EXPORT qbuButtonSignal : public qbuButtonSignalBase
{
	Q_OBJECT
	QBU_DECLARE_SUPERCLASS(qbuButtonSignalBase)
public:
	explicit qbuButtonSignal(QObject* pParent);
	~qbuButtonSignal();

	enum ButtonMode {
		BS_NORMAL,
		BS_INVERTED
	};

public:
	void	setMode(ButtonMode md);
	bool	setButton(QAbstractButton* pAbstractButton, const char * method = SIGNAL(toggled(bool)));
	bool	setButton(QAbstractButton* pAbstractButton, QObject* pTriggerObject, const char * method = SIGNAL(toggled(bool)));

public:
	virtual bool isChecked();

protected slots:
	void	buttonToggledInt(bool bChecked);

private:
	class qbuPrivate;
	std::unique_ptr<qbuPrivate> m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUBUTTONSIGNAL_H
