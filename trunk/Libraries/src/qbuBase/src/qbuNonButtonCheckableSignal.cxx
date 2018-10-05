#include "qbuBasePCH.h"

#include "qbuBase/qbuNonButtonCheckableSignal.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuNonButtonCheckableSignal::qbuPrivate
{
public:
	qbuPrivate();

public:
	qbuNonButtonCheckableSignal::ButtonMode	m_md;
	QObject*								m_pObject;
	bool									m_bChecked;
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuNonButtonCheckableSignal::qbuPrivate::qbuPrivate() : m_pObject(nullptr), m_md(qbuNonButtonCheckableSignal::BS_NORMAL),
m_bChecked(false)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuNonButtonCheckableSignal::qbuNonButtonCheckableSignal(QObject* pParent) : Superclass(pParent), m_pPrivate(new qbuPrivate)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuNonButtonCheckableSignal::~qbuNonButtonCheckableSignal()
{
	// Do not delete this!
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuNonButtonCheckableSignal::setMode(ButtonMode md)
{
	m_pPrivate->m_md = md;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuNonButtonCheckableSignal::isChecked()
{
	bool retVal = m_pPrivate->m_bChecked;
	
	if (m_pPrivate->m_md == BS_INVERTED) {
		retVal = !retVal;
	}
	
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuNonButtonCheckableSignal::setObject(QObject* pObject, const char * method /*= SIGNAL(toggled(bool))*/)
{
	bool retVal = ((m_pPrivate != nullptr) && (pObject != nullptr) && (method != nullptr));
	if (retVal) {
		m_pPrivate->m_pObject = pObject;

		connect(pObject, method, SLOT(buttonToggledInt(bool)));
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuNonButtonCheckableSignal::buttonToggledInt(bool bChecked)
{
	setChecked(bChecked);

	if (m_pPrivate->m_md != BS_INVERTED) {
		emit toggled(bChecked);
	}
	else
	{
		emit toggled(!bChecked);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuNonButtonCheckableSignal::setChecked(bool bChecked)
{
	bool bChanged = (m_pPrivate->m_bChecked != bChecked);

	m_pPrivate->m_bChecked = bChecked;

	// Send toggled signal when changed and not connected to an object that signals.
	if ( (m_pPrivate->m_pObject == nullptr) && bChanged) {
		emit buttonToggledInt(bChecked);
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////
