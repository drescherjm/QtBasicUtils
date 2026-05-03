#include "qbuLogPCH.h"
#include "qbuLog/qbuLoggerWidget2FileNameDelagate.h"
#include <QPainter>
#include <QApplication>
#include <QClipboard>
#include <QStyle>
#include <QAbstractItemView>
#include "qbuLog/qbuLoggerModel.h"

struct StaticLibInitializer {
	StaticLibInitializer() { Q_INIT_RESOURCE(qbuLog); }
};
static StaticLibInitializer s_init;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static QIcon& clippyIcon()
{
	static QIcon s_icon(":/Images/clippy.png");
	return s_icon;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerWidget2FileNameDelagate::qbuLoggerWidget2FileNameDelagate(QWidget* pParent)
	: Superclass(pParent)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*static*/ QRect qbuLoggerWidget2FileNameDelagate::buttonRect(const QRect& cellRect)
{
	// A 32x32 button centred vertically in the cell, pinned to the left edge.
	const int sz = 32;
	int y = cellRect.top() + (cellRect.height() - sz) / 2;
	return QRect(cellRect.left() + 2, y, sz, sz);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget2FileNameDelagate::paint(QPainter* painter,
	const QStyleOptionViewItem& option,
	const QModelIndex& index) const
{
	// Let the base class handle selection / focus background.
	QStyledItemDelegate::paint(painter, option, index);

	QStyleOptionToolButton opt;
	opt.initFrom(option.widget);
	opt.rect = buttonRect(option.rect);
	opt.icon = clippyIcon();
	opt.iconSize = QSize(24, 24);
	opt.subControls = QStyle::SC_ToolButton;
	opt.features = QStyleOptionToolButton::None;
	opt.state = QStyle::State_Enabled | QStyle::State_AutoRaise;

	QApplication::style()->drawComplexControl(QStyle::CC_ToolButton, &opt, painter, option.widget);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSize qbuLoggerWidget2FileNameDelagate::sizeHint(const QStyleOptionViewItem& option,
	const QModelIndex& index) const
{
	QSize sz = Superclass::sizeHint(option, index);
	sz.setHeight(40);
	return sz;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget2FileNameDelagate::onViewClicked(const QAbstractItemView* pView,
	const QModelIndex& index)
{
	if (!pView || index.column() != qbuLoggerModel::CT_FILENAME)
		return;

	// Map the last mouse position into cell-local coords to confirm
	// the click landed inside the button rect.
	QPoint localPos = pView->viewport()->mapFromGlobal(QCursor::pos());
	QRect  cellRect = pView->visualRect(index);

	if (!buttonRect(cellRect).contains(localPos))
		return;

	QString strFileName = index.data(Qt::EditRole).toString();
	if (!strFileName.isEmpty())
		QApplication::clipboard()->setText(strFileName);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
