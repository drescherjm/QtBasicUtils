//
// C++ Interface: QCmdOptBool
//
// Description: 
//
//
// Author:  <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <QChar>
#include <QString>

#include "qbuCmdLine/QCmdOptBasicBase.h"



/////////////////////////////////////////////////////////////////////////////////////////

class QCmdOptBool : public QCmdOptBasicBase<bool>
{
	typedef QCmdOptBasicBase<bool> SuperClass;
public:
	QCmdOptBool(QString strName,QString strDescription, QString strExplanation, bool bDefaultValue);
	virtual int		ImportData( QString strValue );
	QCmdOptBool(const QCmdOptBool & other);
	QCmdOptBool& operator=(const QCmdOptBool & other);
	virtual		QCmdOptBool* Clone();
public:
	virtual QString GetSyntax();
	virtual QString getValueDescription();
	virtual QString	exportCommandString();
	virtual QString exportOptionName();
private:
	void			copy( const QCmdOptBool & other );
	void			destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////


