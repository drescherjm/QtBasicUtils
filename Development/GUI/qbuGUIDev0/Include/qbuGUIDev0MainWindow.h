#pragma once

#ifndef QBUGUIDEV0MAINWINDOW_H
#define QBUGUIDEV0MAINWINDOW_H

#include <QMainWindow>
#include <qbuBase/qbuMacros.h>
#include "ui_qbuGUIDev0MainWindow.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuGUIDev0MainWindow : public QMainWindow, public Ui::qbuGUIDev0MainWindow
{
	Q_OBJECT
	QBU_DECLARE_SUPERCLASS(QMainWindow)
public:
	explicit qbuGUIDev0MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);

public slots:
	void	on_actionDBDev0_triggered();
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUGUIDEV0MAINWINDOW_H
