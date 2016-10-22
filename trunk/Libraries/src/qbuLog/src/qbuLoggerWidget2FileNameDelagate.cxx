#include "qbuLogPCH.h"

#include "qbuLog/qbuLoggerWidget2FileNameDelagate.h"
#include <QPushButton>
#include <QApplication>
#include <QClipboard>
#include <QHBoxLayout>

/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerWidget2FileNameDelagate::qbuLoggerWidget2FileNameDelagate(QWidget* pParent) : Superclass(pParent)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

QWidget * qbuLoggerWidget2FileNameDelagate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

	QWidget* pWidget = new QWidget(parent);

	QHBoxLayout* pLayout = new QHBoxLayout(pWidget);

	QPushButton* pButton = new QPushButton("Copy",parent);
	
	pLayout->addWidget(pButton);

	connect(pButton, SIGNAL(clicked(bool)), SLOT(buttonClicked(bool)));

	return pWidget;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget2FileNameDelagate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QPushButton* pPushButton = editor->findChild<QPushButton*>();

	if (pPushButton) {
		pPushButton->setProperty("Data", index.model()->data(index, Qt::EditRole));
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget2FileNameDelagate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

	//editor->
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget2FileNameDelagate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	editor->setGeometry(option.rect);
}

/////////////////////////////////////////////////////////////////////////////////////////

QSize qbuLoggerWidget2FileNameDelagate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QSize retVal = Superclass::sizeHint(option, index);

	retVal.setHeight(15);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget2FileNameDelagate::buttonClicked(bool checked)
{
	QPushButton* pWidget = qobject_cast<QPushButton*>(sender());
	if (pWidget) {
		QString strFileName = pWidget->property("Data").toString();

		if (!strFileName.isEmpty()) {
			QApplication::clipboard()->setText(strFileName);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
