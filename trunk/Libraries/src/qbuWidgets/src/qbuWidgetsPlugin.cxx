#include "qbuWidgetsPCH.h"
#include "qbuWidgets\qbuWidgetsPlugin.h"
#include "qbuWidgets\qbuRadioButtonInterface.h"
#include "qbuWidgets\qbuGroupBoxInterface.h"

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
Q_EXPORT_PLUGIN2(WidgetsPlugin, qbuWidgetsPlugin)
#endif

/////////////////////////////////////////////////////////////////////////////////////////

qbuWidgetsPlugin::qbuWidgetsPlugin(QObject *parent /*= 0*/)
{
	m_lstWidgetInterfaces.append(new qbuRadioButtonInterface(this));
	m_lstWidgetInterfaces.append(new qbuGroupBoxInterface(this));
}

/////////////////////////////////////////////////////////////////////////////////////////

QList<QDesignerCustomWidgetInterface*> qbuWidgetsPlugin::customWidgets() const
{
	return m_lstWidgetInterfaces;
}

/////////////////////////////////////////////////////////////////////////////////////////

