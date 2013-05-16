#ifndef __QCMDARGQSTRING_H__
#define __QCMDARGQSTRING_H__

#include "QCmdArgBasicBase.h"
#include "QCmd.h"

namespace QTUTILS {

	class QCmdArgQString : public QCmdArgBasicBase<QString>  
	{
		typedef QCmdArgBasicBase<QString> SuperClass;
	public:
		QCmdArgQString(QString str, QString strDescription, QString strExplanation,  
			QString strDefaultValue, CMDSTRVERIFY pfnVerify);
		QCmdArgQString(const QCmdArgQString & other);
		QCmdArgQString& operator=(const QCmdArgQString & other);
		virtual QCmdArgQString* Clone();
	public:
		virtual int		ImportData( QString strValue );
		virtual QString GetSyntax();
		virtual QString exportCommandString();
	protected:
		CMDSTRVERIFY	m_pFnVerify;
	private:
		void			copy( const QCmdArgQString & other );
		void			destroy();
	};

}; //namespace QTUTILS

#endif //__QCMDARGQSTRING_H__
