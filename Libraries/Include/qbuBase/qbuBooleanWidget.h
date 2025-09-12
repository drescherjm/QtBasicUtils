#pragma once

#ifndef QBUBOOLEANWIDGET_H
#define QBUBOOLEANWIDGET_H

#include <QWidget>

class QCheckBox;

/////////////////////////////////////////////////////////////////////////////////////////

class qbuBooleanWidget : public QWidget
{
    Q_OBJECT
    public:
    qbuBooleanWidget(QWidget * parent = 0);

    bool isChecked();
    void setChecked(bool value);

signals:
    void toggled(bool);

private:
    QCheckBox* checkBox;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUBOOLEANWIDGET_H
