#pragma once

#ifndef QBUGROUPBOX_H
#define QBUGROUPBOX_H

#include <QGroupBox>
#include <qbuBase/qbuMacros.h>
#include <QtDesigner/QtDesigner>

// Note: Unfortunately we must not use a macro for the namespace line..
namespace qbu {

	/////////////////////////////////////////////////////////////////////////////////////////

	class QDESIGNER_WIDGET_EXPORT qbuGroupBox : public QGroupBox
	{
		Q_OBJECT
			QBU_DECLARE_SUPERCLASS(QGroupBox)
	public:
		explicit qbuGroupBox(QWidget* parent = 0);
		explicit qbuGroupBox(const QString &title, QWidget* parent = 0);
	};

	/////////////////////////////////////////////////////////////////////////////////////////

}; // end namespace 

#endif // QBUGROUPBOX_H

