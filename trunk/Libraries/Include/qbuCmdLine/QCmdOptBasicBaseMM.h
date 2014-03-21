#ifndef __QCMDOPTBASICBASEMM_H__
#define __QCMDOPTBASICBASEMM_H__

#include "qbuCmdLine/QCmdOptBasicBase.h"

namespace QTUTILS {

	template <class TYPE> class QCmdOptBasicBaseMM : public QCmdOptBasicBase<TYPE>
	{
	public:
		QCmdOptBasicBaseMM(QString strName, QString strDescription, QString strExplanation, 
			TYPE nDefaultValue,TYPE nMinValue, TYPE nMaxValue);
		QCmdOptBasicBaseMM(const QCmdOptBasicBaseMM<TYPE> & other);
		QCmdOptBasicBaseMM<TYPE>& operator=(const QCmdOptBasicBaseMM<TYPE> & other);
		virtual QString GetSyntax()=0;
		virtual int		ImportData( QString strValue )=0;
	public:
		TYPE			m_nMinValue;
		TYPE			m_nMaxValue;
	private:
		void			copy( const QCmdOptBasicBaseMM & other );
		void			destroy();
	};

/////////////////////////////////////////////////////////////////////////////////////////

#include "qbuCmdLine/QCmdOptBasicBaseMM.txx"

/////////////////////////////////////////////////////////////////////////////////////////

};//namespace QTUTILS

#endif //__QCMDOPTBASICBASEMM_H__
