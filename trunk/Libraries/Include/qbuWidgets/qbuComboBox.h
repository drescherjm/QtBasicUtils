#pragma once

#ifndef QBUCOMBOBOX_H
#define QBUCOMBOBOX_H

#include <QComboBox>
#include <qbuBase/qbuMacros.h>
#include <QtDesigner/QtDesigner>

namespace qbu {


	/////////////////////////////////////////////////////////////////////////////////////////

	class QDESIGNER_WIDGET_EXPORT qbuComboBox : public QComboBox
	{
		Q_OBJECT
			QBU_DECLARE_SUPERCLASS(QComboBox)
	public:
		explicit qbuComboBox(QWidget* parent = 0);
	};

	/////////////////////////////////////////////////////////////////////////////////////////

};

#endif // QBUCOMBOBOX_H
