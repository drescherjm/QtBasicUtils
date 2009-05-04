#ifndef __QNAMEDCMDPART_H__
#define __QNAMEDCMDPART_H__

#include "QCmdPart.h"

namespace  QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

class QNamedCmdPart : public QCmdPart
{
public:
	QNamedCmdPart(QString strName,QString strDescription, QString strExplanation);
public:
	virtual QString GetSyntax( )=0;
	virtual QString GetShortSyntax( )=0;
	virtual QString getValueDescription();
	QString GetName();
protected:
	QString m_strName;
};

/////////////////////////////////////////////////////////////////////////////////////////

inline QString QNamedCmdPart::GetName()
{
	return m_strName;
}


/////////////////////////////////////////////////////////////////////////////////////////

}; // namespace QTUTILS

#endif //__QNAMEDCMDPART_H__