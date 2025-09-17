#ifndef __QCMDARGBASIC_TXX__
#define __QCMDARGBASIC_TXX__

#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
QCmdArgBasic<TYPE,fmt>::QCmdArgBasic(QString strName, QString strDescription, 
									 QString strExplanation, TYPE nDefaultValue,
									 TYPE nMinValue, 
									 TYPE nMaxValue) : 
						QCmdArgBasicBaseMM<TYPE>::QCmdArgBasicBaseMM(strName,
						strDescription,strExplanation,
						nDefaultValue,nMinValue,nMaxValue
						)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
int QCmdArgBasic<TYPE,fmt>::ImportData( QString strValue )
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

template <class TYPE, char fmt[]>
QString QCmdArgBasic<TYPE, fmt>::GetSyntax()
{
	QString tempStr = this->GetDescription() + " [";
	tempStr += fmt;
	tempStr += "]";

#if QT_VERSION >= QT_VERSION_CHECK(5, 4, 0)
	return QString::asprintf(tempStr.toUtf8().constData(), this->m_nDefaultValue);
#else
	QString retVal;
	retVal.sprintf(tempStr.toUtf8().constData(), this->m_nDefaultValue);
	return retVal;
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
QString QCmdArgBasic<TYPE, fmt>::exportCommandString()
{
	QString retVal;
        if ( (!this->isOptional()) || (!this->isDefaultValue()) ) {
                retVal = QString("%1").arg(this->m_nValue);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
void QCmdArgBasic<TYPE, fmt>::destroy()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
void QCmdArgBasic<TYPE, fmt>::copy( const QCmdArgBasic<TYPE, fmt> & other )
{

}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
QCmdArgBasic<TYPE, fmt>& QCmdArgBasic<TYPE, fmt>::operator=( const QCmdArgBasic<TYPE, fmt> & other )
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
QCmdArgBasic<TYPE, fmt>::QCmdArgBasic( const QCmdArgBasic<TYPE, fmt> & other ) : SuperClass(other)
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
QCmdArgBasic<TYPE, fmt>* QCmdArgBasic<TYPE, fmt>::Clone()
{
	return new QCmdArgBasic<TYPE, fmt>(*this);
}


/////////////////////////////////////////////////////////////////////////////////////////

#endif //__QCMDARGBASIC_TXX__
