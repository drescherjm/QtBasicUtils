//
// C++ Interface: QCmdArg
//
// Description: 
//
//
// Author:  <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef __QCMDARG_H__
#define __QCMDARG_H__

#include "QNamedCmdPart.h"

namespace QTUTILS {

class QCmdArg : public QNamedCmdPart  
{
public:
	QCmdArg(QString strName,QString strDescription, QString strExplanation);
	QCmdArg(const QCmdArg & other);
	QCmdArg& operator=(const QCmdArg & other);
	virtual ~QCmdArg();
public:
	virtual bool	isOptional();
	virtual void	SetOptional(bool bOptional);
	virtual QString GetShortSyntax( );
public:
	bool	m_bOptional;
private:
	void			copy( const QCmdArg & other );
	void			destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////

inline void QCmdArg::SetOptional(bool bOptional)
{
	m_bOptional = bOptional;
}

inline bool QCmdArg::isOptional()
{
	return m_bOptional;
}

}; //namespace QTUTILS

#endif //def __QCMDARG_H__
