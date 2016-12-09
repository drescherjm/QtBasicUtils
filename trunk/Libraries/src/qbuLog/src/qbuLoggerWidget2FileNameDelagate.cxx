#include "qbuLogPCH.h"

#include "qbuLog/qbuLoggerWidget2FileNameDelagate.h"
#include <QPushButton>
#include <QApplication>
#include <QClipboard>
#include <QHBoxLayout>
#include <QToolButton>

/////////////////////////////////////////////////////////////////////////////////////////

struct StaticLibInitializer
{
    void initialize()
    {
        Q_INIT_RESOURCE(qbuLog);
    }

    StaticLibInitializer()
    {
        initialize();
    }
};

static StaticLibInitializer test;


/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerWidget2FileNameDelagate::qbuLoggerWidget2FileNameDelagate(QWidget* pParent) : Superclass(pParent)
{
    //Q_INIT_RESOURCE(qbuLog);
}

/////////////////////////////////////////////////////////////////////////////////////////

QWidget * qbuLoggerWidget2FileNameDelagate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    static  QIcon g_icon(":/Images/clippy.png");

	QWidget* pWidget = new QWidget(parent);

	QHBoxLayout* pLayout = new QHBoxLayout(pWidget);

    QToolButton* pButton = new QToolButton(/*"Copy",*/parent);
    /*pButton->setSize(40, 40);*/

    pButton->setIcon(g_icon);

    //pButton->setIcon(QIcon(":/Images/clippy.png"));
	
	pLayout->addWidget(pButton);

	connect(pButton, SIGNAL(clicked(bool)), SLOT(buttonClicked(bool)));

	return pWidget;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget2FileNameDelagate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QToolButton* pPushButton = editor->findChild<QToolButton*>();

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

	retVal.setHeight(40);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget2FileNameDelagate::buttonClicked(bool checked)
{
    QToolButton* pWidget = qobject_cast<QToolButton*>(sender());
	if (pWidget) {
		QString strFileName = pWidget->property("Data").toString();

		if (!strFileName.isEmpty()) {
			QApplication::clipboard()->setText(strFileName);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
