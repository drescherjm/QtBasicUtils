#pragma once

#ifndef DEVELOPGUIDB0_H
#define DEVELOPGUIDB0_H

#include <QWidget>
#include "qbuBase/qbuMacros.h"
#include "ui_DevelopGUIDB0.h"

/////////////////////////////////////////////////////////////////////////////////////////

class DevelopGUIDB0 : public QWidget, public Ui::DevelopGUIDB0
{
	QBU_DECLARE_SUPERCLASS(QWidget);
	Q_OBJECT
public:
	explicit DevelopGUIDB0(QWidget* parent = 0, Qt::WindowFlags f = 0);
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // DEVELOPGUIDB0_H
