#include "qbuBasePCH.h"
#include "qbuBase/qbuErrorBase.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuErrorBase::qbuErrorBasePrivate
{
public:
	QString		m_strFailureMessage;
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuErrorBase::qbuErrorBase(  ) : m_pPrivate(new qbuErrorBasePrivate())
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuErrorBase::~qbuErrorBase()
{
	// Do not delete this!
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuErrorBase::appendFailureReason( QString strFailure )
{

	/**
	 *	\todo Should we not add duplicate messages. Perhaps we should store a list of
	 *	failure messages instead of QString. 
	 */

	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		m_pPrivate->m_strFailureMessage.append(strFailure);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuErrorBase::getFailureReasons()
{
	QString retVal;
	if (m_pPrivate != nullptr) {
		retVal = m_pPrivate->m_strFailureMessage;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuErrorBase::hasRecordedErrors()
{
	bool retVal = (m_pPrivate == nullptr);
	if (!retVal) {
		retVal = !m_pPrivate->m_strFailureMessage.isEmpty();
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuErrorBase::prependFailureReason(QString strFailure)
{
	bool retVal = (m_pPrivate != nullptr);
	if (retVal) {
		m_pPrivate->m_strFailureMessage.prepend(strFailure);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////
