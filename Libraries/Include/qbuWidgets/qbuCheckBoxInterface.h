#pragma once

#ifndef QBUCHECKBOXINTERFACE_H
#define QBUCHECKBOXINTERFACE_H

#ifndef QT_VERSION_CHECK
#include <qglobal.h>
#endif

#if (QT_VERSION < 0x050500 )
#include <QDesignerCustomWidgetInterface>
#else
#include <QtUiPlugin/QDesignerCustomWidgetInterface>
#endif 

/////////////////////////////////////////////////////////////////////////////////////////

class qbuCheckBoxInterface : public QObject, public QDesignerCustomWidgetInterface
{
	Q_OBJECT

	Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
	explicit qbuCheckBoxInterface(QObject *parent = 0);

public:
	virtual QString name() const;
	virtual QString group() const;
	virtual QString toolTip() const;
	virtual QString whatsThis() const;
	virtual QString includeFile() const;
	virtual QIcon icon() const;
	virtual bool isContainer() const;
	virtual QWidget * createWidget(QWidget *parent);

	virtual bool isInitialized() const;
	virtual void initialize(QDesignerFormEditorInterface *core);

	virtual QString domXml() const;
private:
	bool	m_bInitilaized;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUCHECKBOXINTERFACE_H

