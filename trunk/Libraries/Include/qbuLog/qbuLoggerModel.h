#pragma once

#ifndef QBULOGGERMODEL_H
#define QBULOGGERMODEL_H

#include <QAbstractTableModel>
#include <memory>
#include <QDateTime>
#include "qbuBase\qbuMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////

class QxtLoggerEngine;

/////////////////////////////////////////////////////////////////////////////////////////

class qbuLoggerModel : public QAbstractTableModel
{
	QBU_DECLARE_SUPERCLASS(QAbstractTableModel);
	Q_OBJECT
public:
    explicit qbuLoggerModel(QObject* pParent);
    virtual ~qbuLoggerModel();

	enum Cols {
		CT_DATE,
		CT_LEVEL,
		CT_FILENAME,
		CT_MESSAGE
	};

public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool    isLogLevel(const QModelIndex &index, uint32_t nLevel) const;

	QString getColumnName(Cols col) const;

public:
	QxtLoggerEngine* getLoggerEngine() const;
    void setRecordLimit(quint32);
	void setUpdateDelay(quint8 nSeconds = 5);

	uint32_t	getMessageTypeCountsByLevel(uint32_t nLevel);

public slots:
	void	logMessage(QDateTime dtMsg, quint32 nLevel, QString strFileName, quint32 nLine, const QStringList& messages);
	void	synchronize();
	void	handleRecordLimit();

private:
    class qbuPrivate;
    std::unique_ptr<qbuPrivate> m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBULOGGERMODEL_H
