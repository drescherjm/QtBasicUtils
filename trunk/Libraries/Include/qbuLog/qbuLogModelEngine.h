#include <QObject>
#include <QxtLoggerEngine>
#include <qbuBase/qbuMacros.h>

/////////////////////////////////////////////////////////////////////////////////////////

class /*qbuLog_EXPORT*/ qbuLogModelEngine : public QObject, public QxtLoggerEngine
{
public:
	QBU_DECLARE_SUPERCLASS(QObject);
	Q_OBJECT
public:
	explicit qbuLogModelEngine(QWidget *parent = 0);
private:
	void	initialize();
protected:
	 virtual void   writeFormatted(QxtLogger::LogLevel level, const QList<QVariant>& messages);
	 virtual void	initLoggerEngine();
	 virtual void	killLoggerEngine();
	 virtual bool	isInitialized() const;
};

/////////////////////////////////////////////////////////////////////////////////////////
