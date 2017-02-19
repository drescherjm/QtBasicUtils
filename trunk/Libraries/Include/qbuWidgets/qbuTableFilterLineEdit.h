#pragma once

#ifndef QBUTABLEFILTERLINEEDIT_H
#define QBUTABLEFILTERLINEEDIT_H

#include <QLineEdit>
#include <QList>

class QTimer;
class QKeyEvent;

#include <qbuBase/qbuMacros.h>
#include <QtDesigner/QtDesigner>

/////////////////////////////////////////////////////////////////////////////////////////

class QDESIGNER_WIDGET_EXPORT qbuTableFilterLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit qbuTableFilterLineEdit(QWidget* parent, QList<qbuTableFilterLineEdit*>* filters, int columnnum);

    // Override methods for programatically changing the value of the line edit
    void clear();
    void setText(const QString& text);

private slots:
    void delayedSignalTimerTriggered();

signals:
    void delayedTextChanged(QString text);

protected:
    void keyReleaseEvent(QKeyEvent* event);

private:
    QList<qbuTableFilterLineEdit*>* filterList;
    int columnNumber;
    QTimer* delaySignalTimer;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUTABLEFILTERLINEEDIT_H
