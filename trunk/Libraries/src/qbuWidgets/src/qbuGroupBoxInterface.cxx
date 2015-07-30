#include "qbuWidgetsPCH.h"

#include "qbuWidgets/qbuGroupBoxInterface.h"
#include <QIcon>
#include "qbuWidgets/qbuGroupBox.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuGroupBoxInterface::qbuGroupBoxInterface(QObject *parent /*= 0*/) : QObject(parent),
	m_bInitilaized(false)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuGroupBoxInterface::name() const
{
	//return QString("%1qbuGroupBox").arg(QBU_STR_VALUE(QBU_NAMESPACE));

	//return QBU_STR_VALUE(QBU_PREPEND_NAMESPACE0(qbuGroupBox));

	//return QString("%1::qbuGroupBox").arg(QBU_STR_VALUE(QBU_NAMESPACE));

	return "qbu::qbuGroupBox";

}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuGroupBoxInterface::group() const
{
	return "qbuWidgets";
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuGroupBoxInterface::toolTip() const
{
	return "Nothing to see here!";
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuGroupBoxInterface::whatsThis() const
{
	return "";
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuGroupBoxInterface::includeFile() const
{
	return "qbuWidgets/qbuGroupBox.h";
}

/////////////////////////////////////////////////////////////////////////////////////////

QIcon qbuGroupBoxInterface::icon() const
{
	return QIcon();
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuGroupBoxInterface::isContainer() const
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

QWidget * qbuGroupBoxInterface::createWidget(QWidget *parent)
{
	return new QBU_PREPEND_NAMESPACE(qbuGroupBox(parent));
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuGroupBoxInterface::initialize(QDesignerFormEditorInterface *core)
{
	if (!m_bInitilaized) {
		m_bInitilaized = true;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuGroupBoxInterface::isInitialized() const
{
	return m_bInitilaized;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuGroupBoxInterface::domXml() const
{
	return
		"<ui language=\"c++\">\n"
		"<widget class = \"qbu::qbuGroupBox\">\n"
		"  <property name = \"title\" >\n"
		"    <string>qbuGroupBox</string>\n"
		"  </property>\n"
		"  <property name=\"geometry\">\n"
		"   <rect>\n"
		"    <width>120</width>\n"
		"    <height>60</height>\n"
		"   </rect>\n"
		"  </property>\n"
		"</widget>\n"
		"</ui>\n";
}

/////////////////////////////////////////////////////////////////////////////////////////
