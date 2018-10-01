#include "qbuBasePCH.h"

#include "qbuBase\qbuCheckBoxDelegate.h"
#include "rfGUI/Include/rfBooleanWidget.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuCheckBoxDelegate::qbuCheckBoxDelegate(QObject *parent) : QItemDelegate(parent)
{
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuCheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    drawCheck(painter, option, option.rect, index.data().toBool() ? Qt::Checked : Qt::Unchecked);
    drawFocus(painter, option, option.rect);
}

/////////////////////////////////////////////////////////////////////////////////////////

QWidget *qbuCheckBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    rfBooleanWidget* retVal = new rfBooleanWidget(parent);
	QObject::connect(retVal, SIGNAL(toggled(bool)), this, SLOT(changed(bool)));
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuCheckBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	bool bVal = index.model()->data(index, Qt::DisplayRole).toBool();

    rfBooleanWidget* pWidget = qobject_cast<rfBooleanWidget*>(editor);

    if (pWidget) {
        // Yes toggle the value when setting since the editor is enabled on first click.
        // This way the first click will change the value of the check instead of requiring
        // a second click to do that.

        pWidget->setChecked(!bVal);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuCheckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    rfBooleanWidget* pWidget = qobject_cast<rfBooleanWidget*>(editor);
    if (pWidget) {
        model->setData(index, pWidget->isChecked() ? 1 : 0, Qt::EditRole);
    }
    
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuCheckBoxDelegate::changed(bool value)
{
    rfBooleanWidget *checkbox = qobject_cast<rfBooleanWidget*>(sender());
    emit commitData(checkbox);
    emit closeEditor(checkbox);
}

/////////////////////////////////////////////////////////////////////////////////////////
