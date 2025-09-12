#pragma once

#ifndef QBUFILTERTABLEHEADER_H
#define QBUFILTERTABLEHEADER_H

#include <QHeaderView>
#include <QList>

class QLineEdit;
class QTableView;
class qbuTableFilterLineEdit;

#include <qbuBase/qbuMacros.h>
#include <QtDesigner/QtDesigner>

/////////////////////////////////////////////////////////////////////////////////////////

class QDESIGNER_WIDGET_EXPORT qbuFilterTableHeader : public QHeaderView
{
    Q_OBJECT

public:
    explicit qbuFilterTableHeader(QTableView* parent = 0);
    virtual QSize sizeHint() const;
    
public slots:
    void generateFilters(int number, bool showFirst = false);
    void adjustPositions();
    void clearFilters();
    void setFilter(int column, const QString& value);

signals:
    void filterChanged(int column, QString value);

protected:
    virtual void updateGeometries();

private slots:
    void inputChanged(const QString& new_value);

private:
    QList<qbuTableFilterLineEdit*> filterWidgets;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUFILTERTABLEHEADER_H
