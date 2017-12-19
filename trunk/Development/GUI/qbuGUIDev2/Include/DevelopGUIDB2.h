#pragma once

#ifndef DEVELOPGUIDB1_H
#define DEVELOPGUIDB1_H

#include <QDialog>
#include "qbuBase/qbuMacros.h"
#include "ui_DevelopGUIDB1.h"

/////////////////////////////////////////////////////////////////////////////////////////

class DevelopGUIDB1 : public QDialog, public Ui::DevelopGUIDB1
{
	QBU_DECLARE_SUPERCLASS(QDialog);
	Q_OBJECT
public:
	explicit DevelopGUIDB1(QWidget* parent = 0, Qt::WindowFlags f = 0);

};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // DEVELOPGUIDB1_H
