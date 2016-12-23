#pragma once

#ifndef QBULOGGERWIDGET3_H
#define QBULOGGERWIDGET3_H

#include <QWidget>
#include <memory>
#include <qbuBase/qbuMacros.h>

/////////////////////////////////////////////////////////////////////////////////////////
// 
// namespace Ui {
//     class qbuLoggerWidget2;
// }

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

protected:
	void	rowsInserted(const QModelIndex &parent, int start, int end);

public:
	QxtLoggerEngine* getLoggerEngine() const;

// private:
// 	bool	            m_bFirst;
//     Ui::qbuLoggerWidget2 *ui;

private:
    class qbuPrivate;
    std::unique_ptr<qbuPrivate> m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBULOGGERWIDGET3_H
