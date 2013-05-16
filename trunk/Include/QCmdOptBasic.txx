#ifndef __QCMDOPTBASICXX__
#define __QCMDOPTBASICXX__

#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
QCmdOptBasic<TYPE,fmt>::QCmdOptBasic(QString strName, QString strDescription, 
									 QString strExplanation, TYPE nDefaultValue,
									 TYPE nMinValue, 
									 TYPE nMaxValue) : QCmdOptBasicBaseMM<TYPE>::QCmdOptBasicBaseMM(strName,
									 strDescription,strExplanation,
									 nDefaultValue,nMinValue,nMaxValue
									 )
{

}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
int QCmdOptBasic<TYPE,fmt>::ImportData( QString strValue )
{
	int retVal = QCmdPart::MarkSet();
	if ( retVal == 0 ) {
		QString strTemp = strValue.trimmed();
		if ( strTemp.isEmpty() ) {
			retVal = QCmdParseError::PARAM_MISSING_DATA;
		}
		else
		{
			retVal = sscanf(strTemp.toStdString().c_str(),fmt,&this->m_nValue);
			if ( retVal == 1 ) {
				if ( this->m_nValue < this->m_nMinValue ) {
					retVal = QCmdParseError::PARAM_TOO_SMALL;
				}
				else
					if ( this->m_nValue > this->m_nMaxValue ) {
						retVal = QCmdParseError::PARAM_TOO_BIG;
					}
					else
						retVal = QCmdParseError::STATUS_OK;

			}
			else
			{
				retVal = QCmdParseError::PARAM_INVALID_DATA;
			}
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
QString QCmdOptBasic<TYPE,fmt>::GetSyntax()
{
	QString retVal;
	QString tempStr = this->GetDescription() + " [";
	tempStr += fmt;
	tempStr += ("]");
	retVal.sprintf(tempStr.toAscii(),this->m_nDefaultValue);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
QString QCmdOptBasic<TYPE, fmt>::exportCommandString()
{
	QString retVal;
        if ( !this->isDefaultValue() ) {
		retVal = QString("%1%2")
                                        .arg(this->exportOptionName())
                                        .arg(this->m_nValue);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
void QTUTILS::QCmdOptBasic<TYPE, fmt>::destroy()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
void QTUTILS::QCmdOptBasic<TYPE, fmt>::copy( const QCmdOptBasic<TYPE, fmt> & other )
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
QCmdOptBasic<TYPE, fmt>& QTUTILS::QCmdOptBasic<TYPE, fmt>::operator=( const QCmdOptBasic<TYPE, fmt> & other )
{
	SuperClass::operator =(other);

	if ( &other != this ) {
		destroy();
		copy(other);
	}
	return (*this);
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
QTUTILS::QCmdOptBasic<TYPE, fmt>::QCmdOptBasic( const QCmdOptBasic<TYPE, fmt> & other ) : SuperClass(other)
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
QCmdOptBasic<TYPE, fmt>* QCmdOptBasic<TYPE, fmt>::Clone()
{
	return new QCmdOptBasic<TYPE, fmt>(*this);
}

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__QCMDOPTBASICXX__
