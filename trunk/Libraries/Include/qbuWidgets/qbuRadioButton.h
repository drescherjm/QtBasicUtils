#include <QRadioButton>
#include <qbuBase/qbuMacros.h>

/////////////////////////////////////////////////////////////////////////////////////////

class qbuRadioButton : public QRadioButton
{
	Q_OBJECT
		QBU_DECLARE_SUPERCLASS(QRadioButton)
public:
	explicit qbuRadioButton(QWidget* parent = 0);
	explicit qbuRadioButton(const QString &title, QWidget* parent = 0);
};

/////////////////////////////////////////////////////////////////////////////////////////

