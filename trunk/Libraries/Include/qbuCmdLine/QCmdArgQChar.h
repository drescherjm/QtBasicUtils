#ifndef __QCMDARGQCHAR_H__
#define __QCMDARGQCHAR_H__

#include "qbuCmdLine/QCmdArgBasicBaseMM.h"

namespace QTUTILS {
	
	class QCmdArgQChar : public QCmdArgBasicBaseMM<QChar>  
	{
		typedef QCmdArgBasicBaseMM<QChar> SuperClass;
	public:
		QCmdArgQChar(QString strName, QString strDescription, QString strExplanation, 
			bool bIgnoreCase, 
			QChar chDefaultValue, QChar chMinVal, QChar chMaxVal);
		QCmdArgQChar(const QCmdArgQChar & other);
		QCmdArgQChar& operator=(const QCmdArgQChar & other);
		virtual QCmdArgQChar* Clone();
	public:
		virtual int		ImportData( QString strValue );
		virtual QString GetSyntax();
		virtual QString exportCommandString();
	public:
		bool	m_bIgnoreCase;
	private:
		void			copy( const QCmdArgQChar & other );
		void			destroy();
	};

}; //namespace QTUTILS

#endif //__QCMDARGQCHAR_H__
