#pragma once

#ifndef QBURADIOBUTTON_H
#define QBURADIOBUTTON_H

#include <QRadioButton>
#include <qbuBase/qbuMacros.h>
#include <QtDesigner/QtDesigner>

namespace qbu {


	/////////////////////////////////////////////////////////////////////////////////////////

	class QDESIGNER_WIDGET_EXPORT qbuRadioButton : public QRadioButton
	{
		Q_OBJECT
			QBU_DECLARE_SUPERCLASS(QRadioButton)
	public:
		explicit qbuRadioButton(QWidget* parent = 0);
		explicit qbuRadioButton(const QString &title, QWidget* parent = 0);
	};

	/////////////////////////////////////////////////////////////////////////////////////////

};

#endif // QBURADIOBUTTON_H
