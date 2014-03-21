#ifndef __QCMDOPTQSTRING_H__
#define __QCMDOPTQSTRING_H__

#include "qbuCmdLine/QCmdOptBasicBase.h"
#include "qbuCmdLine/QCmd.h"

namespace QTUTILS {

	class QCmdOptQString : public QCmdOptBasicBase<QString>  
	{
		typedef QCmdOptBasicBase<QString> SuperClass;
	public:
		QCmdOptQString(QString strName, QString strDescription, QString strExplanation,  
			QString strDefaultValue, CMDSTRVERIFY pfnVerify);
		QCmdOptQString(const QCmdOptQString & other);
		QCmdOptQString& operator=(const QCmdOptQString & other);

		virtual QCmdOptQString* Clone();
	public:
		virtual int		ImportData( QString strValue );
		virtual QString GetSyntax();
		virtual QString exportCommandString();
	protected:
		CMDSTRVERIFY	m_pFnVerify;
	private:
		void			copy( const QCmdOptQString & other );
		void			destroy();
	};

}; //namespace QTUTILS

#endif //__QCMDOPTQSTRING_H__
