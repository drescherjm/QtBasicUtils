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
	typedef QCmdArgBasicBase<bool> SuperClass;
public:
	QCmdArgBool(QString strName,QString strDescription, QString strExplanation, bool bDefaultValue);
	virtual int		ImportData( QString strValue );
	QCmdArgBool(const QCmdArgBool & other);
	QCmdArgBool& operator=(const QCmdArgBool & other);
	virtual QCmdArgBool* Clone();
public:
	virtual QString GetSyntax();
	virtual QString exportCommandString();
private:
	void			copy( const QCmdArgBool & other );
	void			destroy();
};

}; //namespace QTUTILS
