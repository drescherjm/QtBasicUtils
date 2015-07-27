#pragma once

#ifndef DEVELOPGUIDB0_H
#define DEVELOPGUIDB0_H

#include <QDialog>
#include "qbuBase/qbuMacros.h"
#include "ui_DevelopGUIDB0.h"

/////////////////////////////////////////////////////////////////////////////////////////

class DevelopGUIDB0 : public QDialog, public Ui::DevelopGUIDB0
{
	QBU_DECLARE_SUPERCLASS(QDialog);
	Q_OBJECT
public:
	explicit DevelopGUIDB0(QWidget* parent = 0, Qt::WindowFlags f = 0);

};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // DEVELOPGUIDB0_H
