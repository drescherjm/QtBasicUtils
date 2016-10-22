#pragma once

#ifndef QBULOGGERWIDGET2_H
#define QBULOGGERWIDGET2_H

#include <QTableView>
#include <QxtLoggerEngine>
#include <qbuBase/qbuMacros.h>

/////////////////////////////////////////////////////////////////////////////////////////

class /*qbuLog_EXPORT*/ qbuLoggerWidget2 : public QTableView
{
public:
	QBU_DECLARE_SUPERCLASS(QTableView);
	Q_OBJECT
public:
	explicit qbuLoggerWidget2(QWidget *parent = 0);

protected:
	void	initialize();
	void	rowsInserted(const QModelIndex &parent, int start, int end);

public:
	QxtLoggerEngine* getLoggerEngine() const;

private:
	bool	m_bFirst;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBULOGGERWIDGET2_H
