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

#include "QCmdOpt.h"

namespace QTUTILS {

class QCmdOptBool : public QCmdOpt  
{
public:
	QCmdOptBool(QString strName, QString strDescription, QString strExplanation, bool bDefaultValue);
	virtual int		ImportData( QString strValue );
	virtual void	Initialize();
	bool	GetValue();
public:
	virtual QString GetSyntax();
	virtual QString getValueDescription();
	bool	m_bValue;
	bool	m_bDefaultValue;
};

inline  bool QCmdOptBool::GetValue()
{
	return m_bValue;
}

}; //namespace QTUTILS
