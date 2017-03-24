#include "qbuBasePCH.h"

#include "qbuBase/qbuButtonSignalGroup.h"

#include <QSet>
#include "qbuBase/qbuButtonSignalBase.h"
#include "qbuBase/qbuButtonSignal.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuButtonSignalGroup::qbuPrivate
{
public:
	qbuPrivate();

public:
	QSet<qbuButtonSignalBase*> m_pButtons;
	qbuButtonSignalGroup::SignalGroupMode m_md;
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuButtonSignalGroup::qbuPrivate::qbuPrivate() : m_md(qbuButtonSignalGroup::BSG_OR)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuButtonSignalGroup::qbuButtonSignalGroup(QObject* pParent) : Superclass(pParent), 
	m_pPrivate(new qbuPrivate)
{
	connect(this, SIGNAL(some_toggled(bool)), this, SIGNAL(toggled(bool)));
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuButtonSignalGroup::~qbuButtonSignalGroup()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuButtonSignalGroup::addButton(QAbstractButton* pAbstractButton, const char * method)
{
	bool retVal = ((m_pPrivate != nullptr) && (pAbstractButton != nullptr) && (method != nullptr));
	if (retVal) {

		qbuButtonSignal* pSignal = new qbuButtonSignal(this);
		pSignal->setButton(pAbstractButton, method);

		m_pPrivate->m_pButtons << pSignal;

		connect(pSignal, SIGNAL(toggled(bool)), SLOT(buttonToggledInt(bool)));
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuButtonSignalGroup::addButton(QAbstractButton* pAbstractButton, QObject* pTriggerObject, const char * method /*= SIGNAL(toggled(bool))*/)
{
	bool retVal = ((m_pPrivate != nullptr) && (pAbstractButton != nullptr) && (pTriggerObject != nullptr) && (method != nullptr));
	if (retVal) {
// 		m_pPrivate->m_pButtons << pAbstractButton;
// 
// 		connect(pTriggerObject, method, SLOT(buttonToggledInt(bool)));
		
		qbuButtonSignal* pSignal = new qbuButtonSignal(this);
		pSignal->setButton(pAbstractButton, pTriggerObject, method);
		
		retVal = addButton(pSignal);

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuButtonSignalGroup::addButton(qbuButtonSignalBase* pButtonSignal)
{
	bool retVal = ((m_pPrivate != nullptr) && (pButtonSignal != nullptr));
	if (retVal) {
		m_pPrivate->m_pButtons << pButtonSignal;

		connect(pButtonSignal, SIGNAL(toggled(bool)), SLOT(buttonToggledInt(bool)));
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuButtonSignalGroup::buttonToggledInt(bool bChecked)
{

	if (bChecked) {

		if (m_pPrivate->m_md == BSG_OR) {
			foreach(qbuButtonSignalBase* pButtonSignal, m_pPrivate->m_pButtons) {
				bChecked = pButtonSignal->isChecked();
				if (bChecked) {
					break;
				}
			}
		}
		else
		{
			// AND
			// bChecked will be false if any ButtonSignal is not checked.
			foreach(qbuButtonSignalBase* pButtonSignal, m_pPrivate->m_pButtons) {
				bChecked = pButtonSignal->isChecked();
				if (!bChecked) {
					break;
				}
			}
		}

		// Any button is checked
		if (bChecked) {
			emit some_toggled(bChecked);
		}
	}
	else
	{
	
		if (m_pPrivate->m_md == BSG_OR) {
			foreach(qbuButtonSignalBase* pButtonSignal, m_pPrivate->m_pButtons) {
				bChecked = pButtonSignal->isChecked();
				if (bChecked) {
					break;
				}
			}
		}
		else
		{
			foreach(qbuButtonSignalBase* pButtonSignal, m_pPrivate->m_pButtons) {
				bChecked = pButtonSignal->isChecked();
				if (!bChecked) {
					break;
				}
			}
		}

		// All buttons are unchecked
		if (!bChecked) {
			emit some_toggled(bChecked);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuButtonSignalGroup::setMode(SignalGroupMode md)
{
	m_pPrivate->m_md = md;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuButtonSignalGroup::isChecked()
{
	bool retVal = false;
	switch (m_pPrivate->m_md) {
	case BSG_OR:
		foreach(qbuButtonSignalBase* pButtonSignal, m_pPrivate->m_pButtons) {
			retVal = pButtonSignal->isChecked();
			if (retVal) {
				break;
			}
		}
		break;
	case BSG_AND:
		retVal = true;
		foreach(qbuButtonSignalBase* pButtonSignal, m_pPrivate->m_pButtons) {
			retVal = pButtonSignal->isChecked();
			if (!retVal) {
				break;
			}
		}
		break;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////
