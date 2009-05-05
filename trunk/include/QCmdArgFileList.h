#ifndef __QCMDARGFILELIST_H__
#define __QCMDARGFILELIST_H__

#include "QCmdArgBasicBase.h"
#include "QCmdLineFileList.h"
#include "QCmd.h"

namespace QTUTILS {

class QCmdArgFileList : public QCmdArgBasicBase<QCmdLineFileList>
{
public:
	QCmdArgFileList(QString strName, QString strDescription, QString strExplanation, 
		QCmdLineFileList strDefaultValue, 
		CMDSTRVERIFY pfnVerify);
	virtual int			ImportData( QString strValue );
	virtual void		Initialize();
	virtual QString		GetSyntax();
	virtual QString		GetShortSyntax( );
	virtual QString		exportCommandString();
public:
	CMDSTRVERIFY		m_pFnVerify;
};

}; //namespace QTUTILS

#endif //ndef __QCMDARGFILELIST_H__