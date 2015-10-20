#pragma once

#ifndef QBUWIDGETSPLUGIN_H
#define QBUWIDGETSPLUGIN_H

/////////////////////////////////////////////////////////////////////////////////////////

#include <QtDesigner/QtDesigner>

class qbuWidgetsPlugin : public QObject, public QDesignerCustomWidgetCollectionInterface
{
	Q_OBJECT

		// Note: QT_VERSION_CHECK(5,5,0) does not work in qt4 moc since it does not expand macros so we force a version directly!
#if (QT_VERSION >= 0x050500)
//#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		Q_PLUGIN_METADATA(IID "com.pitt.Qt.CustomWidgets")
#endif
		Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
public:
	explicit qbuWidgetsPlugin(QObject *parent = 0);

public:

#if (QT_VERSION >= 0x050500)
	QList<QDesignerCustomWidgetInterface*> customWidgets() const Q_DECL_OVERRIDE;
#else
	QList<QDesignerCustomWidgetInterface*> customWidgets() const;
#endif 
private:
	QList<QDesignerCustomWidgetInterface*> m_lstWidgetInterfaces;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUWIDGETSPLUGIN_H
