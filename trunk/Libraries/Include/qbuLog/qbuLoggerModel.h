#pragma once

#ifndef QBULOGGERMODEL_H
#define QBULOGGERMODEL_H

#include <QAbstractTableModel>
#include <memory>
#include <QDateTime>
#include "qbuBase\qbuMacros.h"

class QxtLoggerEngine;

/////////////////////////////////////////////////////////////////////////////////////////

class qbuLoggerModel : public QAbstractTableModel
{
	QBU_DECLARE_SUPERCLASS(QAbstractTableModel);
	Q_OBJECT
public:
    explicit qbuLoggerModel(QObject* pParent);
    virtual ~qbuLoggerModel();

public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

public:
	QxtLoggerEngine* getLoggerEngine() const;

public slots:
	void	logMessage(QDateTime dtMsg, quint32 nLevel, QString strFileName, quint32 nLine, const QStringList& messages);

private:
    class qbuPrivate;
    std::unique_ptr<qbuPrivate> m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBULOGGERMODEL_H
