#pragma once

#ifndef QBUGUIDEV0MAINWINDOW_H
#define QBUGUIDEV0MAINWINDOW_H

#include <QMainWindow>
#include <qbuBase/qbuMacros.h>
#include "ui_qbuGUIDev2MainWindow.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuGUIDev2MainWindow : public QMainWindow, public Ui::qbuGUIDev2MainWindow
{
	Q_OBJECT
	QBU_DECLARE_SUPERCLASS(QMainWindow)
public:
	explicit qbuGUIDev2MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);

public slots:
	void	on_actionTestLog0_triggered();
    void    on_actionToggleRandomData_triggered();

    void    generateLogDataTimer();
private:

};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUGUIDEV0MAINWINDOW_H
