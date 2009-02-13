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

namespace QTUTILS {

class QCmdPart 
{
public:
	QCmdPart( QString strDescription, QString strExplanation);
	virtual ~QCmdPart();
public:
	int		MarkSet();
	bool	HasValueBeenSet();
	QString GetDescription();
	QString	GetExplanation();
	virtual int		ImportData( QString strValue )=0;
	virtual void	Initialize();
protected:
	bool	m_bValueSet;
	QString m_strDescription;
	QString	m_strExplanation;
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