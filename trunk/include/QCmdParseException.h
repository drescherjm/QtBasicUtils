//
// C++ Interface: QCmdParseException
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

class CCmdParseException 
{
public:
	void Delete();
	static void Throw(UINT nErrorCode, CString str0=_T(""), CString str1=_T(""));
	static void Throw(UINT nErrorCode, CString str0, const CStringList & sl);
	static void Throw(UINT nErrorCode, CString str0, const CStringList & sl,CString str2);
	UINT	GetErrorCode();
	CString	GetErrorString();
protected:
	UINT		m_nErrorCode;
	CString		m_strError;
private:
	CCmdParseException(UINT nErrorCode, CString str0, CString str1,CString str2="");
};

inline CCmdParseException::CCmdParseException(UINT nErrorCode, CString str0, CString str1,CString str2)
{
	m_nErrorCode = nErrorCode;
	m_strError = CCmdParseError::GetErrorString(nErrorCode,str0,str1,str2);
}

inline UINT CCmdParseException::GetErrorCode()
{
	return m_nErrorCode;
}

inline CString CCmdParseException::GetErrorString()
{
	return m_strError;
}

}; //namespace QTUTILS