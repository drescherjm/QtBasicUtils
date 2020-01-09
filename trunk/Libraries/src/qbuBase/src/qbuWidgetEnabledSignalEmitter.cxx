#include "qbuBasePCH.h"
#include "qbuBase/qbuWidgetEnabledSignalEmitter.h"
#include <QWidget>

/////////////////////////////////////////////////////////////////////////////////////////

qbuWidgetEnabledSignalEmitter::qbuWidgetEnabledSignalEmitter( QObject* pParent ) : Superclass(pParent)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuWidgetEnabledSignalEmitter::eventFilter(QObject* obj, QEvent* event)
{
	if (event->type() == QEvent::EnabledChange) {
		QWidget* pWidget = dynamic_cast<QWidget*>(obj);
		if (pWidget) {
			emit enabledChange(pWidget->isEnabled());
		}
	}
	return QObject::eventFilter(obj, event);
}

/////////////////////////////////////////////////////////////////////////////////////////
