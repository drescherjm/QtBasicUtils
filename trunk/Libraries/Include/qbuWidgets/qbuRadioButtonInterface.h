#pragma once

#ifndef QBURADIOBUTTONINTERFACE_H
#define QBURADIOBUTTONINTERFACE_H

#include <QDesignerCustomWidgetInterface>

/////////////////////////////////////////////////////////////////////////////////////////

class qbuRadioButtonInterface : public QObject, public QDesignerCustomWidgetInterface
{
	Q_OBJECT

	Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
	explicit qbuRadioButtonInterface(QObject *parent = 0);

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

#endif // QBURADIOBUTTONINTERFACE_H
