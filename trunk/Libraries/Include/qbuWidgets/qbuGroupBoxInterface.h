#pragma once

#ifndef QBUGROUPBOXINTERFACE_H
#define QBUGROUPBOXINTERFACE_H

#ifndef QT_VERSION_CHECK
#include <qglobal.h>
#endif

#if (QT_VERSION < QT_VERSION_CHECK(5,5,0))
#include <QDesignerCustomWidgetInterface>
#else
#include <QtUiPlugin/QDesignerCustomWidgetInterface>
#endif 

/////////////////////////////////////////////////////////////////////////////////////////

class qbuGroupBoxInterface : public QObject, public QDesignerCustomWidgetInterface
{
	Q_OBJECT

		Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
	explicit qbuGroupBoxInterface(QObject *parent = 0);

public:
	virtual bool isInitialized() const;
	virtual void initialize(QDesignerFormEditorInterface *core);

	virtual QString domXml() const;
	virtual QString name() const;
	virtual QString group() const;
	virtual QString toolTip() const;
	virtual QString whatsThis() const;
	virtual QString includeFile() const;
	virtual QIcon icon() const;
	virtual bool isContainer() const;

	virtual QWidget * createWidget(QWidget *parent);
private:
	bool	m_bInitilaized;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUGROUPBOXINTERFACE_H
