#pragma once

#ifndef QBUGROUPBOX_H
#define QBUGROUPBOX_H

#include <QGroupBox>
#include <qbuBase/qbuMacros.h>

/////////////////////////////////////////////////////////////////////////////////////////

class qbuGroupBox : public QGroupBox
{
	Q_OBJECT
		QBU_DECLARE_SUPERCLASS(QGroupBox)
public:
	explicit qbuGroupBox(QWidget* parent = 0);
	explicit qbuGroupBox(const QString &title, QWidget* parent = 0);
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUGROUPBOX_H
