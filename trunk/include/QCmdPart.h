//
// C++ Interface: QCmdPart
//
// Description: 
//
//
// Author:  <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef __QCMDPART_H__
#define __QCMDPART_H__

#include <QString>

namespace QTUTILS {

class QCmdPart 
{
public:
	QCmdPart( QString strDescription, QString strExplanation);
	QCmdPart(const QCmdPart & other);
	QCmdPart&	operator=(const QCmdPart & other);
	virtual		QCmdPart* Clone()=0;
	virtual		~QCmdPart();
public:
	int				MarkSet();
	bool			HasValueBeenSet();
	QString			GetDescription();
	QString			GetExplanation();
	virtual int		ImportData( QString strValue )=0;
	virtual void	Initialize();
private:
	void			copy( const QCmdPart & other );
	void			destroy();
protected:
	bool			m_bValueSet;
	QString			m_strDescription;
	QString			m_strExplanation;
};

inline QCmdPart::~QCmdPart()
{
}

inline QString QCmdPart::GetDescription()
{
	return m_strDescription;
}

inline QString QCmdPart::GetExplanation()
{
	return m_strExplanation;
}

}; //namespace QTUTILS

#endif //__QCMDPART_H__