#include <QItemDelegate>
#include "rfGUILibraryDefines.h"

/////////////////////////////////////////////////////////////////////////////////////////

class rfGUI_EXPORT qbuCheckBoxDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	qbuCheckBoxDelegate(QObject *parent = 0);

	void paint(QPainter *painter,
		const QStyleOptionViewItem &option,
		const QModelIndex &index) const;


	QWidget *createEditor(QWidget *parent,
		const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	void setEditorData(QWidget *editor,
		const QModelIndex &index) const;

	void setModelData(QWidget *editor,
		QAbstractItemModel *model,
		const QModelIndex &index) const;

protected slots:
    void changed(bool value);
};

/////////////////////////////////////////////////////////////////////////////////////////
