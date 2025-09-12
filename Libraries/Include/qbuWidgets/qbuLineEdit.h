#pragma once

#ifndef QBULINEEDIT_H
#define QBULINEEDIT_H

#include <QLineEdit>
#include <qbuBase/qbuMacros.h>
#include <QtDesigner/QtDesigner>

namespace qbu {


	/////////////////////////////////////////////////////////////////////////////////////////

	class QDESIGNER_WIDGET_EXPORT qbuLineEdit : public QLineEdit
	{
		Q_OBJECT
		QBU_DECLARE_SUPERCLASS(QLineEdit)
	public:
		explicit qbuLineEdit(QWidget* parent = 0);
		explicit qbuLineEdit(const QString &title, QWidget* parent = 0);
	};

	/////////////////////////////////////////////////////////////////////////////////////////

};


#endif // QBULINEEDIT_H

