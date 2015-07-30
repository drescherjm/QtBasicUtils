#include <QCheckBox>
#include <qbuBase/qbuMacros.h>
#include <QtDesigner/QtDesigner>

namespace qbu {


	/////////////////////////////////////////////////////////////////////////////////////////

	class QDESIGNER_WIDGET_EXPORT qbuCheckBox : public QCheckBox
	{
		Q_OBJECT
			QBU_DECLARE_SUPERCLASS(QCheckBox)
	public:
		explicit qbuCheckBox(QWidget* parent = 0);
		explicit qbuCheckBox(const QString &title, QWidget* parent = 0);
	};

	/////////////////////////////////////////////////////////////////////////////////////////

};

