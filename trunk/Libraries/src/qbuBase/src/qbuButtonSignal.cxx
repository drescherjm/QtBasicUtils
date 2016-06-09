#include "qbuBasePCH.h"
#include <QAbstractButton>

#include "qbuBase/qbuButtonSignal.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuButtonSignal::qbuPrivate
{
public:
	qbuPrivate();

public:
	qbuButtonSignal::ButtonMode	m_md;
	QAbstractButton*			m_pButton;
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuButtonSignal::qbuPrivate::qbuPrivate() : m_pButton(), m_md (qbuButtonSignal::BS_NORMAL )
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuButtonSignal::qbuButtonSignal(QObject* pParent) : Superclass(pParent), m_pPrivate(new qbuPrivate)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuButtonSignal::~qbuButtonSignal()
{
	// Do not delete this!
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuButtonSignal::setMode(ButtonMode md)
{
	m_pPrivate->m_md = md;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuButtonSignal::isChecked()
{
	bool retVal = false;

	if (m_pPrivate->m_pButton != nullptr) {
		retVal = m_pPrivate->m_pButton->isChecked();
		if (m_pPrivate->m_md == BS_INVERTED) {
			retVal = !retVal;
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuButtonSignal::setButton(QAbstractButton* pAbstractButton, const char * method /*= SIGNAL(toggled(bool))*/)
{
	bool retVal = ((m_pPrivate != nullptr) && (pAbstractButton != nullptr) && (method != nullptr));
	if (retVal) {
		m_pPrivate->m_pButton = pAbstractButton;

		connect(pAbstractButton, method, SLOT(buttonToggledInt(bool)));
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuButtonSignal::setButton(QAbstractButton* pAbstractButton, QObject* pTriggerObject, const char * method /*= SIGNAL(toggled(bool))*/)
{
	bool retVal = ((m_pPrivate != nullptr) && (pAbstractButton != nullptr) && (pTriggerObject != nullptr) && (method != nullptr));
	if (retVal) {
		m_pPrivate->m_pButton = pAbstractButton;

		connect(pTriggerObject, method, SLOT(buttonToggledInt(bool)));
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuButtonSignal::buttonToggledInt(bool bChecked)
{
	if (m_pPrivate->m_md != BS_INVERTED) {
		emit toggled(bChecked);
	}
	else
	{
		emit toggled(!bChecked);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
