#pragma once

#ifndef QBULOGGERWIDGET3_H
#define QBULOGGERWIDGET3_H

#include <QWidget>
#include <memory>
#include <qbuBase/qbuMacros.h>

/////////////////////////////////////////////////////////////////////////////////////////

class QxtLoggerEngine;
class QAbstractItemModel;

/////////////////////////////////////////////////////////////////////////////////////////

class /*qbuLog_EXPORT*/ qbuLoggerWidget3 : public QWidget
{
public:
    QBU_DECLARE_SUPERCLASS(QWidget);
	Q_OBJECT
public:
	explicit    qbuLoggerWidget3(QWidget *parent = 0);
    virtual     ~qbuLoggerWidget3();

public:
    void	initialize();
    void    setModel(QAbstractItemModel *model);

protected slots:
    void    updateRowHeights(int nStartingRow, int nEndingRow);
    void	rowsInserted(const QModelIndex &parent, int start, int end);

public:
	QxtLoggerEngine* getLoggerEngine() const;

private:
    class qbuPrivate;
    std::unique_ptr<qbuPrivate> m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBULOGGERWIDGET3_H
