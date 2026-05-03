#pragma once
#ifndef QBULOGGERWIDGET2FILENAMEDELAGATE_H
#define QBULOGGERWIDGET2FILENAMEDELAGATE_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <QStyledItemDelegate>
#include "qbuBase/qbuMacros.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class qbuLoggerWidget2FileNameDelagate : public QStyledItemDelegate
{
	QBU_DECLARE_SUPERCLASS(QStyledItemDelegate)
		Q_OBJECT
public:
	explicit qbuLoggerWidget2FileNameDelagate(QWidget* pParent);

	// Returns the button rect for a given cell rect — used by both
	// paint() and the view's clicked handler.
	static QRect buttonRect(const QRect& cellRect);

	void paint(QPainter* painter,
		const QStyleOptionViewItem& option,
		const QModelIndex& index) const override;

	QSize sizeHint(const QStyleOptionViewItem& option,
		const QModelIndex& index) const override;

public slots:
	// Connect QTableView::clicked(QModelIndex) to this.
	void onViewClicked(const QAbstractItemView* pView,
		const QModelIndex& index);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // QBULOGGERWIDGET2FILENAMEDELAGATE_H