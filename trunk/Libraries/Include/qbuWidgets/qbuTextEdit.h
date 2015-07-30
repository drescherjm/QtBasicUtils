#pragma once

#ifndef QBUTEXTEDIT_H
#define QBUTEXTEDIT_H

#include <QTextEdit>
#include <qbuBase/qbuMacros.h>
#include <QtDesigner/QtDesigner>

namespace qbu {


	/////////////////////////////////////////////////////////////////////////////////////////

	class QDESIGNER_WIDGET_EXPORT qbuTextEdit : public QTextEdit
	{
		Q_OBJECT
			QBU_DECLARE_SUPERCLASS(QTextEdit)
	public:
		explicit qbuTextEdit(QWidget* parent = 0);
		explicit qbuTextEdit(const QString &title, QWidget* parent = 0);
	};

	/////////////////////////////////////////////////////////////////////////////////////////

};

#endif // QBUTEXTEDIT_H
