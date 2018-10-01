#include "rfGUIPCH.h"
#include "rfGUI/Include/qbuBooleanWidget.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuBooleanWidget::qbuBooleanWidget(QWidget * parent /*= 0*/) : QWidget(parent)
{
    checkBox = new QCheckBox(this);

    connect(checkBox, SIGNAL(toggled(bool)), SIGNAL(toggled(bool)));

    QHBoxLayout * layout = new QHBoxLayout(this);
    layout->addWidget(checkBox, 0, Qt::AlignCenter);
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuBooleanWidget::isChecked()
{
    return checkBox->isChecked();
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuBooleanWidget::setChecked(bool value)
{
    checkBox->setChecked(value);
}

/////////////////////////////////////////////////////////////////////////////////////////
