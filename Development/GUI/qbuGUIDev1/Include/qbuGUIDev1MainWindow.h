#pragma once

#ifndef QBUGUIDEV0MAINWINDOW_H
#define QBUGUIDEV0MAINWINDOW_H

#include <QMainWindow>
#include <qbuBase/qbuMacros.h>
#include "ui_qbuGUIDev1MainWindow.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuGUIDev1MainWindow : public QMainWindow, public Ui::qbuGUIDev1MainWindow
{
	Q_OBJECT
	QBU_DECLARE_SUPERCLASS(QMainWindow)
public:
	explicit qbuGUIDev1MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = Qt::WindowFlags{});

public slots:
	void	on_actionTestLog0_triggered();
    void    on_actionToggleRandomData_triggered();

    void    generateLogDataTimer();
private:

};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUGUIDEV0MAINWINDOW_H
