#ifndef __QNAMEDCMDPART_H__
#define __QNAMEDCMDPART_H__

#include "QCmdPart.h"

namespace  QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

class QNamedCmdPart : public QCmdPart
{
public:
	QNamedCmdPart(QString strName,QString strDescription, QString strExplanation);
	QNamedCmdPart(const QNamedCmdPart & other);
	QNamedCmdPart& operator=(const QNamedCmdPart & other);
public:
	virtual QString GetSyntax( )=0;
	virtual QString GetShortSyntax( )=0;
	virtual bool	isDefaultValue()=0;
	virtual QString getValueDescription();
	virtual QString exportCommandString()=0;
	QString			GetName();
private:
	void			copy( const QNamedCmdPart & other );
	void			destroy();
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