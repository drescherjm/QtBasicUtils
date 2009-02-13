//
// C++ Interface: QCmdHelpException
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

class QCmdHelpException 
{
public:
	void		Delete();
	static void Throw(QString strMessage);
	QString		GetMessageString();
protected:
	QString		m_strMessage;
private:
	QCmdHelpException(QString strMessage);
};

inline QCmdHelpException::QCmdHelpException(QString strMessage)
{
	m_strMessage = strMessage;
}

inline QString QCmdHelpException::GetMessageString()
{
	return m_strMessage;
}

}; //namespace QTUTILS