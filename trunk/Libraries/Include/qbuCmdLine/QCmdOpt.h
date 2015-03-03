//
// C++ Interface: QCmdOpt
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

#ifndef QCMDOPT_H
#define QCMDOPT_H

#include "QNamedCmdPart.h"

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdOpt : public QNamedCmdPart  
{
public:
	QCmdOpt(QString strName,QString strDescription, QString strExplanation);
	QCmdOpt(const QCmdOpt & other);
	QCmdOpt& operator=(const QCmdOpt & other);
	virtual ~QCmdOpt();
public:
	virtual int		ImportData( QString strValue )=0;
	virtual QString GetSyntax( )=0;
	virtual QString GetShortSyntax( );
	virtual bool	isExtendedOption();
	virtual QString exportOptionName();
private:
	void			copy( const QCmdOpt & other );
	void			destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QCMDOPT_H
