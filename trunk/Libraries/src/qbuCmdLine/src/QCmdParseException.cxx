#include "qbuCmdLine/QCmdParseException.h"
#include <assert.h>

namespace QTUTILS {

	void QCmdParseException::Throw(quint32 nErrorCode, QString str0, QString str1)
	{
		if ( nErrorCode != QCmdParseError::STATUS_OK ) {
			
#if defined(_DEBUG) && defined(DEBUG_ASSERT_CMDLINE)
		assert(nErrorCode != QCmdParseError::STATUS_OK );
#endif //defined(_DEBUG) && defined(DEBUG_ASSERT_CMDLINE)
		
		QCmdParseException* pExcept = new QCmdParseException(nErrorCode,str0,str1);
		throw pExcept;

		}
	}

	void QCmdParseException::Throw(quint32 nErrorCode, QString str0, const QStringList & sl)
	{
		if ( nErrorCode != QCmdParseError::STATUS_OK ) {
			QString str1;
			for(QStringList::const_iterator it=sl.begin(); it != sl.end();++it) {
				str1 += *it + " ";
			}

#if defined(_DEBUG) && defined(DEBUG_ASSERT_CMDLINE)
			assert(nErrorCode != QCmdParseError::STATUS_OK );
#endif //defined(_DEBUG) && defined(DEBUG_ASSERT_CMDLINE)

			QCmdParseException* pExcept = new QCmdParseException(nErrorCode,str0,str1);
			throw pExcept;

		}
	}

	void QCmdParseException::Throw(quint32 nErrorCode, QString str0, const QStringList & sl,QString str2)
	{
		if ( nErrorCode != QCmdParseError::STATUS_OK ) {
			QString str1;
			for(QStringList::const_iterator it=sl.begin(); it != sl.end();++it) {
				str1 += *it + " ";
			}

#if defined(_DEBUG) && defined(DEBUG_ASSERT_CMDLINE)
			assert(nErrorCode != QCmdParseError::STATUS_OK );
#endif //defined(_DEBUG) && defined(DEBUG_ASSERT_CMDLINE)

			QCmdParseException* pExcept = new QCmdParseException(nErrorCode,str0 + str1,str2);
			throw pExcept;
		}
	}

	void QCmdParseException::Delete()
	{
		delete this;
	}

}; //namespace QTUTILS
