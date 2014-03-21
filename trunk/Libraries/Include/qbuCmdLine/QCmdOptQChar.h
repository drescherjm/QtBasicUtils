#ifndef __QCMDOPTQCHAR_H__
#define __QCMDOPTQCHAR_H__

#include "qbuCmdLine/QCmdOptBasicBaseMM.h"

namespace QTUTILS {
	
	class QCmdOptQChar : public QCmdOptBasicBaseMM<QChar>  
	{
		typedef QCmdOptBasicBaseMM<QChar> SuperClass;
	public:
		QCmdOptQChar(QString strName, QString strDescription, QString strExplanation, bool bIgnoreCase, 
			QChar chDefaultValue, QChar chMinVal, QChar chMaxVal);
		QCmdOptQChar(const QCmdOptQChar & other);
		QCmdOptQChar& operator=(const QCmdOptQChar & other);
		virtual QCmdOptQChar* Clone();
	public:
		virtual int		ImportData( QString strValue );
		virtual QString GetSyntax();
		virtual QString exportCommandString();
	public:
		bool	m_bIgnoreCase;
	private:
		void			copy( const QCmdOptQChar & other );
		void			destroy();
	};

}; //namespace QTUTILS

#endif //__QCMDOPTQCHAR_H__
