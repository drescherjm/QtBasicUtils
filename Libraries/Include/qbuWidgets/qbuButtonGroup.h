#pragma once

#ifndef QBUBUTTONGROUP_H
#define QBUBUTTONGROUP_H

#include <QButtonGroup>
#include <qbuBase/qbuMacros.h>
#include <QtDesigner/QtDesigner>

/////////////////////////////////////////////////////////////////////////////////////////

class QDESIGNER_WIDGET_EXPORT qbuButtonGroup : public QButtonGroup
{
	Q_OBJECT
	QBU_DECLARE_SUPERCLASS(QButtonGroup)
public:
	explicit qbuButtonGroup(QWidget* parent = 0);
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUBUTTONGROUP_H

