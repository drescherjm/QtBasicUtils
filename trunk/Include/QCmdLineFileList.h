//
// C++ Interface: QCmdLineFileList
//
// Description: 
//
//
// Author:  <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef __QCMDLINEFILELIST_H__
#define __QCMDLINEFILELIST_H__

#include <QStringList>

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdLineFileList
{
public:
	QCmdLineFileList();
	QCmdLineFileList(const QCmdLineFileList & other);
	QCmdLineFileList& operator=(const QCmdLineFileList & other);
	bool operator==(const QCmdLineFileList & other) const;
public:
	QString		GetSyntax();
	int			CheckFileName(QString & strFile);
	void		SetPath();
	void		CopyTo(QCmdLineFileList & other);
public:

	typedef		QStringList::iterator iterator;

	int			size () const;
	void		push_back(const QString & str);
	void		clear();
	iterator	begin();
	iterator	end();
	bool		isEmpty() const;
public:
	QStringList		m_strListFiles;
	QString			m_strDefaultPath;
	quint32			m_nMinNumFiles;
	quint32			m_nMaxNumFiles;
	quint32			m_nFlags;
public:
	enum Flags {MUST_EXIST				= 0x0001, 
				MUST_NOT_EXIST			= 0x0002,
				EXIST_IN_DEFAULT_PATH	= 0x0004,
				USE_CWD_AS_DEFAULT		= 0x0008,
				CONTINUE_PATH			= 0x0010,
				PATH_MUST_EXIST			= 0x0020,
				MUST_BE_FILE			= 0x0100,
				MUST_BE_FOLDER			= 0x0200};
private:
	void copy( const QCmdLineFileList & other );
	void destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////

inline QCmdLineFileList& QCmdLineFileList::operator=(const QCmdLineFileList & other )
{
	if ( &other != this ) {
		destroy();
		copy(other);
	}
	return (*this);
}

inline QCmdLineFileList::QCmdLineFileList(const QCmdLineFileList & other )
{
	copy(other);
}

inline void QCmdLineFileList::destroy() 
{
	m_strListFiles.clear();
	m_strDefaultPath.clear();
}

}; //namespace QTUTILS

#endif //ndef __QCMDLINEFILELIST_H__
