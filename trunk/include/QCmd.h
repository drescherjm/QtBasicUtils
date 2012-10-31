#ifndef __QCMD_H__
#define __QCMD_H__
//

#include <float.h>
#include <QString>
#include <QMap>
#include "QCmdLineFileList.h"
#include <limits>
#include "QCmdArg.h"
#include "QCmdOpt.h"

namespace QTUTILS {

typedef QList<QCmdArg*> QArgList;
typedef QList<QCmdOpt*> QOptList;

typedef QMap< QString,QCmdOpt* > QOptMap;
typedef QMap< QString,QCmdArg* > QArgMap;

typedef int (*CMDSTRVERIFY)( QString str, qint32 nStr );

const float		NEG_FLOAT_MAX = -1.0f * FLT_MAX;
const double	NEG_DOUBLE_MAX = -1.0 * DBL_MAX;
 
/////////////////////////////////////////////////////////////////////////////////////////

class QCmd : public QObject
{
	Q_OBJECT
public:
	QCmd(QString strName,QString strDescription, QString strExplanation=QString(),bool bIgnoreCase = true);
	QCmd(const QCmd & other);
	virtual ~QCmd();

	virtual QCmd* Clone();
	virtual QCmd* New();

	enum Flag {
		NO_FLAG=0,
		REMOVE_OUTER_QUOTES=1,
	};

	Q_DECLARE_FLAGS(Flags,Flag);

public:
	virtual void Initialize();
public:
	int	AddOpt( QString strName, QString strDescription, QString strExplanation, bool bDefaultValue = true);
	int	AddOpt( QString strName, QString strDescription, QString strExplanation, quint32 nDefaultValue = 0, 
		quint32 nMinValue = std::numeric_limits<quint32>::min(), 
		quint32 nMaxValue = std::numeric_limits<quint32>::max());
	int	AddOpt( QString strName, QString strDescription, QString strExplanation, int nDefaultValue = 0, 
		int nMinValue = std::numeric_limits<int>::min(), 
		int nMaxValue = std::numeric_limits<int>::max());
	int	AddOpt( QString strName, QString strDescription, QString strExplanation, quint8 nDefaultValue = 0, 
		quint8 nMinValue = std::numeric_limits<quint8>::min(), 
		quint8 nMaxValue = std::numeric_limits<quint8>::max());
	int	AddOpt( QString strName, QString strDescription, QString strExplanation, quint16 nDefaultValue = 0, 
		quint16 nMinValue = std::numeric_limits<quint16>::min(), 
		quint16 nMaxValue = std::numeric_limits<quint16>::max());
	int	AddOpt( QString strName, QString strDescription, QString strExplanation, short nDefaultValue = 0, 
		short nMinValue = std::numeric_limits<short>::min(), 
		short nMaxValue = std::numeric_limits<short>::max());
	int	AddOpt( QString strName, QString strDescription, QString strExplanation, float nDefaultValue = 0, 
		float nMinValue = -std::numeric_limits<float>::max(), 
		float nMaxValue = std::numeric_limits<float>::max());
	int	AddOpt( QString strName, QString strDescription, QString strExplanation, double nDefaultValue = 0, 
		double nMinValue = -std::numeric_limits<double>::max(), 
		double nMaxValue = std::numeric_limits<double>::max());
	int AddOpt( QString strName, QString strDescription, QString strExplanation, bool bIgnoreCase, 
		QChar chDefaultValue, 
		QChar chMinVal = std::numeric_limits<QChar>::min(), 
		QChar chMaxVal = std::numeric_limits<QChar>::max());

	int AddOpt( QString strName, QString strDescription, QString strExplanation, QString strDefaultValue=(""), 
		CMDSTRVERIFY pFnVerify=NULL);
	int	AddOpt(QString strName, QString strDescription, QString strExplanation, const  QStringList & strLstDefaultValue, 
		CMDSTRVERIFY pFnVerify=NULL);
	int	AddOpt(QString strName, QString strDescription, QString strExplanation, const  QCmdLineFileList & strLstDefaultValue, 
		CMDSTRVERIFY pFnVerify=NULL);

	//int AddArg( QString strName, QCmdArg* pArg=NULL);
	int	AddArg( QString strName, QString strDescription, QString strExplanation, bool bDefaultValue = true);
	int	AddArg( QString strName, QString strDescription, QString strExplanation, quint32 nDefaultValue = 0, 
		quint32 nMinValue = std::numeric_limits<quint32>::min(), 
		quint32 nMaxValue = std::numeric_limits<quint32>::max());
	int	AddArg( QString strName, QString strDescription, QString strExplanation, int nDefaultValue = 0, 
		int nMinValue = std::numeric_limits<int>::min(), 
		int nMaxValue = std::numeric_limits<int>::max());
	int	AddArg( QString strName, QString strDescription, QString strExplanation, quint8 nDefaultValue = 0, 
		quint8 nMinValue = std::numeric_limits<quint8>::min(), 
		quint8 nMaxValue = std::numeric_limits<quint8>::max());
	int	AddArg( QString strName, QString strDescription, QString strExplanation, quint16 nDefaultValue = 0, 
		quint16 nMinValue = std::numeric_limits<quint16>::min(), 
		quint16 nMaxValue = std::numeric_limits<quint16>::max());
	int	AddArg( QString strName, QString strDescription, QString strExplanation, short nDefaultValue = 0, 
		short nMinValue = std::numeric_limits<short>::min(), 
		short nMaxValue = std::numeric_limits<short>::max());;
	int	AddArg( QString strName, QString strDescription, QString strExplanation, float nDefaultValue = 0, 
		float nMinValue = -std::numeric_limits<float>::max(), 
		float nMaxValue = std::numeric_limits<float>::max());
	int	AddArg( QString strName, QString strDescription, QString strExplanation, double nDefaultValue = 0, 
		double nMinValue = -std::numeric_limits<double>::max(), 
		double nMaxValue = std::numeric_limits<double>::max());
	int AddArg( QString strName, QString strDescription, QString strExplanation, bool bIgnoreCase=true, 
		QChar chNameDefaultValue=0x0, QChar chNameMinVal=SCHAR_MIN, QChar chNameMaxVal=SCHAR_MAX);
	int AddArg( QString strName, QString strDescription, QString strExplanation, QString strDefaultValue=(""), 
		CMDSTRVERIFY pFnVerify=NULL);
	int	AddArg(QString strName, QString strDescription, QString strExplanation,const  QStringList & strLstDefaultValue, 
		CMDSTRVERIFY pFnVerify=NULL);
	int	AddArg(QString strName, QString strDescription, QString strExplanation,const  QCmdLineFileList & strLstDefaultValue, 
		CMDSTRVERIFY pFnVerify=NULL);
public:
	int GetOpt(QString strName, bool & bValue);
	int GetOpt(QString strName, quint32 & nValue);
	int GetOpt(QString strName, int & nValue);
	int GetOpt(QString strName, quint8 & nValue);
	int GetOpt(QString strName, quint16 & nValue);
	int	GetOpt(QString strName, short & nValue);
	int GetOpt(QString strName, float & nValue);
	int GetOpt(QString strName, double & nValue);
	int	GetOpt(QString strName, QChar & chValue);
	int GetOpt(QString strName, QString & nValue,Flags fg=NO_FLAG);
	int	GetOpt(QString strName, QStringList & nValue,Flags fg=NO_FLAG);
	int	GetOpt(QString strName, QCmdLineFileList & nValue);

	int SetOpt(QString strName, bool bValue);
	int SetOpt(QString strName, quint32 nValue);
	int SetOpt(QString strName, int nValue);
	int SetOpt(QString strName, quint8 nValue);
	int SetOpt(QString strName, quint16 nValue);
	int	SetOpt(QString strName, short nValue);
	int SetOpt(QString strName, float nValue);
	int SetOpt(QString strName, double nValue);
	int	SetOpt(QString strName, QChar chValue);
	int SetOpt(QString strName, QString nValue);
	int	SetOpt(QString strName, QStringList nValue);
	int	SetOpt(QString strName, QCmdLineFileList nValue);

	int GetArg(QString strName, bool & bValue);
	int GetArg(QString strName, quint32 & nValue);
	int GetArg(QString strName, int & nValue);
	int GetArg(QString strName, quint8 & nValue);
	int GetArg(QString strName, quint16 & nValue);
	int	GetArg(QString strName, short & nValue);
	int GetArg(QString strName, float & nValue);
	int GetArg(QString strName, double & nValue);
	int	GetArg(QString strName, QChar & chValue);
	int	GetArg(QString strName, QString & nValue,Flags fg=NO_FLAG);
	int	GetArg(QString strName, QStringList & nValue,Flags fg=NO_FLAG);
	int	GetArg(QString strName, QCmdLineFileList & nValue);

	int SetArg(QString strName, bool bValue);
	int SetArg(QString strName, quint32 nValue);
	int SetArg(QString strName, int nValue);
	int SetArg(QString strName, quint8 nValue);
	int SetArg(QString strName, quint16 nValue);
	int	SetArg(QString strName, short nValue);
	int SetArg(QString strName, float nValue);
	int SetArg(QString strName, double nValue);
	int	SetArg(QString strName, QChar chValue);
	int SetArg(QString strName, QString nValue);
	int	SetArg(QString strName, QStringList nValue);
	int	SetArg(QString strName, QCmdLineFileList nValue);

public:
	virtual		int		Parse();
	virtual		int		Execute();
	virtual		QString GetSyntax();
	virtual		QString	GetName();
	virtual		QString	GetDescription();
	virtual		QString	GetLongDescription();
	virtual		bool	hasOpt(QString strName);

public:
	void		EndRequiredArguments();
	bool		wasSuccessful(int nRetCode) const;
	
	// Basically the reverse of what parse does. This generates the string that can
	// be placed on the command line to initialize this command in the current state.
	QString		exportCommandString(QChar chCommand);

	//This is everything in exportCommandString() except the Command itself.
	QString		exportArgumentsAndOptionsString();
public:
	QStringList m_strLstCmd;
protected:
	int			Parse( QStringList & strLst );

	// When called with bDuplicate==true these clone the Options or Arguments instead of
	// using the same pointer. 
	QOptList	getOptions(bool bDuplicate=false) const;
	QArgList	getArguments(bool bDuplicate=false) const;

	int			FindOpt(QString strName, QCmdOpt *& option);
	int			FindArg(QString strName, QCmdArg *& pArgument);

	void		setOptions(QOptList & lstOptions);
	void		setArguments(QArgList & lstArguments);
private:
	friend struct	qtutilsPrivate;
	struct			qtutilsPrivate;
	qtutilsPrivate* m_pPrivate;
private:
	void			copy(const QCmd & other);
	void			destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////

Q_DECLARE_OPERATORS_FOR_FLAGS(QCmd::Flags);

/////////////////////////////////////////////////////////////////////////////////////////

}; // namespace QTUTILS

#endif //__QCMD_H__
