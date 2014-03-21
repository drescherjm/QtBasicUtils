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

#pragma once

#ifndef __QCMDPART_H__
#define __QCMDPART_H__

#include <QString>

/////////////////////////////////////////////////////////////////////////////////////////

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
	void			MarkHidden(bool bHidden);
	bool			isHidden();
private:
	void			copy( const QCmdPart & other );
	void			destroy();
protected:
	bool			m_bValueSet;
	bool			m_bHidden;
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

/////////////////////////////////////////////////////////////////////////////////////////

#endif // __QCMDPART_H__
