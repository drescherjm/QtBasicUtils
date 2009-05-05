//
// C++ Interface: QCmdArgBool
//
// Description: 
//
//
// Author:  <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <QString>

#include "QCmdArgBasicBase.h"

namespace QTUTILS {

class QCmdArgBool : public QCmdArgBasicBase<bool>
{
public:
	QCmdArgBool(QString strName,QString strDescription, QString strExplanation, bool bDefaultValue);
	virtual int		ImportData( QString strValue );
public:
	virtual QString GetSyntax();
	virtual QString exportCommandString();
};

}; //namespace QTUTILS
