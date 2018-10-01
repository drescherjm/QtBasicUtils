#include "rfGUILibraryDefines.h"
#include <QWidget>

class QCheckBox;

/////////////////////////////////////////////////////////////////////////////////////////

class rfGUI_EXPORT qbuBooleanWidget : public QWidget
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
