#pragma once

#ifndef QBULOGGERWIDGET2FILENAMEDELAGATE_H
#define QBULOGGERWIDGET2FILENAMEDELAGATE_H

/////////////////////////////////////////////////////////////////////////////////////////

#include <QItemDelegate>
#include "qbuBase/qbuMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuLoggerWidget2FileNameDelagate : public QItemDelegate
{
	QBU_DECLARE_SUPERCLASS(QItemDelegate)
	Q_OBJECT
public:
	explicit qbuLoggerWidget2FileNameDelagate(QWidget* pParent);

protected:
	virtual QWidget *	createEditor(QWidget *parent, 
		const QStyleOptionViewItem &option, const QModelIndex &index) const;
	
	virtual void		setEditorData(QWidget *editor, 
		const QModelIndex &index) const;
	
	virtual void		setModelData(QWidget *editor, 
		QAbstractItemModel *model, const QModelIndex &index) const;

	virtual void		updateEditorGeometry(QWidget *editor, 
		const QStyleOptionViewItem &option, const QModelIndex &index) const;

	virtual QSize		sizeHint(const QStyleOptionViewItem &option, 
		const QModelIndex &index) const;

protected slots:
	void	buttonClicked(bool checked);
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBULOGGERWIDGET2FILENAMEDELAGATE_H
