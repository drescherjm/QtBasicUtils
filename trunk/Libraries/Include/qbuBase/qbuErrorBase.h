#pragma once

#ifndef QBUERRORBASE_H
#define QBUERRORBASE_H

//#include "qbuBaseLibraryDefines.h"
#include <QString>
#include <memory>

/////////////////////////////////////////////////////////////////////////////////////////

class /*qbuBase_EXPORT*/ qbuErrorBase
{
public:
	qbuErrorBase();
	virtual ~qbuErrorBase();
public:
	bool		appendFailureReason( QString strFailure );
	QString		getFailureReasons();
	bool		hasRecordedErrors();

private:
	class	qbuErrorBasePrivate;
	std::unique_ptr<qbuErrorBasePrivate>	m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUERRORBASE_H

