#pragma once

#ifndef QBUGUIDEV0MAINWINDOW_H
#define QBUGUIDEV0MAINWINDOW_H

#include <QMainWindow>
#include <qbuBase/qbuMacros.h>

/////////////////////////////////////////////////////////////////////////////////////////

class qbuGUIDev0MainWindow : public QMainWindow
{
	Q_OBJECT
	QBU_DECLARE_SUPERCLASS(QMainWindow)
public:
	explicit qbuGUIDev0MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUGUIDEV0MAINWINDOW_H
