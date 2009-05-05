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

#include "QCmdOptBasicBase.h"

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdOptBool : public QCmdOptBasicBase<bool>
{
public:
	QCmdOptBool(QString strName,QString strDescription, QString strExplanation, bool bDefaultValue);
	virtual int		ImportData( QString strValue );
public:
	virtual QString GetSyntax();
	virtual QString getValueDescription();
	virtual QString	exportCommandString();
};

/////////////////////////////////////////////////////////////////////////////////////////

}; //namespace QTUTILS
