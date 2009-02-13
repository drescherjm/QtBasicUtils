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

namespace QTUTILS {

class QCmdLineFileList
{
public:
	QCmdLineFileList();
	QCmdLineFileList(const QCmdLineFileList & other);
	QCmdLineFileList& operator=(const QCmdLineFileList & other);
public:
	QString		GetSyntax();
	int			CheckFileName(QString & strFile);
	void		SetPath();
	void		CopyTo(QCmdLineFileList & other);
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
	m_strListFiles.RemoveAll();
	m_strDefaultPath.Empty();
}

}; //namespace QTUTILS
