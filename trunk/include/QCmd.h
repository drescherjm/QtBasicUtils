//

#include <QString>

namespace QTUTILS {
 
class QCmd
{
public:
	QCmd(QString strName,QString strDescription, QString strExplanation=QString(),bool bIgnoreCase = true);
	virtual ~QCmd();
public:
	virtual void Initialize();
public:
	int	AddOpt( QChar ch, QString strDescription, QString strExplanation, bool bDefaultValue = true);
	int	AddOpt( QChar ch, QString strDescription, QString strExplanation, UINT nDefaultValue = 0, UINT nMinValue=0, 
		UINT nMaxValue = UINT_MAX);
	int	AddOpt( QChar ch, QString strDescription, QString strExplanation, int nDefaultValue = 0, int nMinValue=INT_MIN, 
		int nMaxValue = INT_MAX);
	int	AddOpt( QChar ch, QString strDescription, QString strExplanation, BYTE nDefaultValue = 0, BYTE nMinValue=0, 
		BYTE nMaxValue = UCHAR_MAX);
	int	AddOpt( QChar ch, QString strDescription, QString strExplanation, WORD nDefaultValue = 0, WORD nMinValue=0, 
		WORD nMaxValue = USHRT_MAX);
	int	AddOpt( QChar ch, QString strDescription, QString strExplanation, short nDefaultValue = 0, short nMinValue=SHRT_MIN, 
		short nMaxValue = SHRT_MAX);
	int	AddOpt( QChar ch, QString strDescription, QString strExplanation, float nDefaultValue = 0, float nMinValue=FLT_MIN, 
		float nMaxValue = FLT_MAX);
	int	AddOpt( QChar ch, QString strDescription, QString strExplanation, double nDefaultValue = 0, double nMinValue=DBL_MIN, 
		double nMaxValue = DBL_MAX);
	int AddOpt( QChar ch, QString strDescription, QString strExplanation, bool bIgnoreCase=true, 
		QChar chDefaultValue=0x0, QChar chMinVal=SCHAR_MIN, QChar chMaxVal=SCHAR_MAX);
	int AddOpt( QChar ch, QString strDescription, QString strExplanation, QString strDefaultValue=_T(""), 
		CMDSTRVERIFY pFnVerify=NULL);
	int	AddOpt(QChar ch, QString strDescription, QString strExplanation, const  CStringList & strLstDefaultValue, 
		CMDSTRVERIFY pFnVerify=NULL);
	int	AddOpt(QChar ch, QString strDescription, QString strExplanation, const  CCmdLineFileList & strLstDefaultValue, 
		CMDSTRVERIFY pFnVerify=NULL);

	int AddArg(QString strName, CCmdArg* pArg=NULL);
	int	AddArg( QString strName, QString strDescription, QString strExplanation, bool bDefaultValue = true);
	int	AddArg( QString strName, QString strDescription, QString strExplanation, UINT nDefaultValue = 0, UINT nMinValue=0, 
		UINT nMaxValue = UINT_MAX);
	int	AddArg( QString strName, QString strDescription, QString strExplanation, int nDefaultValue = 0, int nMinValue=INT_MIN, 
		int nMaxValue = INT_MAX);
	int	AddArg( QString strName, QString strDescription, QString strExplanation, BYTE nDefaultValue = 0, BYTE nMinValue=0, 
		BYTE nMaxValue = UCHAR_MAX);
	int	AddArg( QString strName, QString strDescription, QString strExplanation, WORD nDefaultValue = 0, WORD nMinValue=0, 
		WORD nMaxValue = USHRT_MAX);
	int	AddArg( QString strName, QString strDescription, QString strExplanation, short nDefaultValue = 0, short nMinValue=SHRT_MIN, 
		short nMaxValue = SHRT_MAX);
	int	AddArg( QString strName, QString strDescription, QString strExplanation, float nDefaultValue = 0, float nMinValue=FLT_MIN, 
		float nMaxValue = FLT_MAX);
	int	AddArg( QString strName, QString strDescription, QString strExplanation, double nDefaultValue = 0, double nMinValue=DBL_MIN, 
		double nMaxValue = DBL_MAX);
	int AddArg( QString strName, QString strDescription, QString strExplanation, bool bIgnoreCase=true, 
		QChar chNameDefaultValue=0x0, QChar chNameMinVal=SCHAR_MIN, QChar chNameMaxVal=SCHAR_MAX);
	int AddArg( QString strName, QString strDescription, QString strExplanation, QString strDefaultValue=_T(""), 
		CMDSTRVERIFY pFnVerify=NULL);
	int	AddArg(QString strName, QString strDescription, QString strExplanation,const  CStringList & strLstDefaultValue, 
		CMDSTRVERIFY pFnVerify=NULL);
	int	AddArg(QString strName, QString strDescription, QString strExplanation,const  CCmdLineFileList & strLstDefaultValue, 
		CMDSTRVERIFY pFnVerify=NULL);
public:
	int GetOpt(QChar ch, bool & bValue);
	int GetOpt(QChar ch, UINT & nValue);
	int GetOpt(QChar ch, int & nValue);
	int GetOpt(QChar ch, BYTE & nValue);
	int GetOpt(QChar ch, WORD & nValue);
	int	GetOpt(QChar ch, short & nValue);
	int GetOpt(QChar ch, float & nValue);
	int GetOpt(QChar ch, double & nValue);
	int	GetOpt(QChar ch, char & chValue);
	int GetOpt(QChar ch, QString & nValue);
	int	GetOpt(QChar ch, CStringList & nValue);
	int	GetOpt(QChar ch, CCmdLineFileList & nValue);

	int GetArg(QString strName, bool & bValue);
	int GetArg(QString strName, UINT & nValue);
	int GetArg(QString strName, int & nValue);
	int GetArg(QString strName, BYTE & nValue);
	int GetArg(QString strName, WORD & nValue);
	int	GetArg(QString strName, short & nValue);
	int GetArg(QString strName, float & nValue);
	int GetArg(QString strName, double & nValue);
	int	GetArg(QString strName, char & chValue);
	int	GetArg(QString strName, QString & nValue);
	int	GetArg(QString strName, CStringList & nValue);
	int	GetArg(QString strName, CCmdLineFileList & nValue);
public:
	virtual int Parse();
	CStringList m_strLstCmd;
	virtual int Execute();
	void	EndRequiredArguments();
	int		IsOption( QString & str, CCmdOpt *& pOption );
	virtual QString GetSyntax();
	QString	GetName();
	QString GetDescription();
	QString GetLongDescription();
protected:
	int		Parse( CStringList & strLst );
	int		AddOpt( QChar ch, CCmdOpt* pOpt = NULL );
	QChar	GetOptChar( QChar ch );
	int		FindOpt( QChar ch, CCmdOpt *& option );
	int		FindArg(QString strName, CCmdArg *& ARGUMENT);
protected:
	QString		m_strName;
	bool		m_bOptional;
	bool		m_bIgnoreCase;
	QString		m_strDescription;
	QString		m_strExplanation;
	COptList	m_listOptions;
	CArgList	m_listArguments;
	COptMap		m_mapOpt;
	CArgMap		m_mapArg;
private:
	QString m_strStringListEnd;
	QChar m_chOption;
};

inline QString QtCmd::GetName()
{
	return m_strName;
}

inline QString QtCmd::GetDescription()
{
	return m_strDescription;
}

}; // namespace QTUTILS