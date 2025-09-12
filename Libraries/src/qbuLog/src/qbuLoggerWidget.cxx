#include "qbuLogPCH.h"

#include "qbuLog/qbuLoggerWidget.h"
#include <QTableWidgetItem>
#include <QDateTime>
#include <QHeaderView>
#include <QColor>

/////////////////////////////////////////////////////////////////////////////////////////

qbuLoggerWidget::qbuLoggerWidget( QWidget *parent /*= 0*/ ) : Superclass(parent)
{
	initialize();
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget::initLoggerEngine()
{
    return; // Should work out of the box!
}

/////////////////////////////////////////////////////////////////////////////////////////

/*!
    \reimp
 */
void qbuLoggerWidget::killLoggerEngine()
{
    return; // I do nothing.
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuLoggerWidget::isInitialized() const
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

static QString Titles[] = {"Date","Level", "File", "Message"};
const int GRID_COLS = sizeof(Titles)/sizeof(Titles[0]);

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget::initialize()
{
	setColumnCount(GRID_COLS);
	for(quint32 i=0; i < GRID_COLS;++i) {
		QTableWidgetItem* pItem = new QTableWidgetItem;
		pItem->setText(Titles[i]);
		setHorizontalHeaderItem(i,pItem);
	}
	

	QHeaderView* pHeader = horizontalHeader();
	if (pHeader) {
		pHeader->setStretchLastSection(true);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuLoggerWidget::writeFormatted( QxtLogger::LogLevel level, const QList<QVariant>& messages )
{

	QString strToday = QDateTime::currentDateTime().toString(Qt::ISODate);
	int nRow = rowCount();

	QString strMsg, strFile;

	int i=0;

	foreach(QVariant vt, messages) {
		if (i == 0) {
			strFile = vt.toString();
			i++;
		}
		else
		{
			strMsg += vt.toString() + "\n\r";
		}
		
	}

	if (!strMsg.isEmpty()) {
		insertRow(nRow);
		QTableWidgetItem* pItem = new QTableWidgetItem;
		pItem->setText(strToday);
		setItem(nRow,0,pItem);

		pItem = new QTableWidgetItem;
		pItem->setText(QxtLogger::logLevelToString(level));
		setItem(nRow,1,pItem);
		
		switch(level) {
		case QxtLogger::WarningLevel:
		case QxtLogger::CriticalLevel:
		case QxtLogger::FatalLevel:
			pItem->setBackgroundColor(Qt::red);
			break;
		}
		
		pItem = new QTableWidgetItem;
		pItem->setText(strFile);
		pItem->setToolTip(strFile);
		//pItem->setData(Qt::ToolTipRole,strFile);
		setItem(nRow,2,pItem);

		pItem = new QTableWidgetItem;
		pItem->setText(strMsg.trimmed());
		setItem(nRow,3,pItem);
		resizeRowToContents(nRow);
	}


// 	foreach(QVariant vt, messages) {
// 		if (!vt.isNull()) {
// 			insertRow(nRow);
// 			QTableWidgetItem* pItem = new QTableWidgetItem;
// 			pItem->setText(strToday);
// 			setItem(nRow,0,pItem);
// 
// 			pItem = new QTableWidgetItem;
// 			pItem->setText(QxtLogger::logLevelToString(level));
// 			setItem(nRow,1,pItem);
// 
// 			switch(level) {
// 			case QxtLogger::WarningLevel:
// 			case QxtLogger::CriticalLevel:
// 			case QxtLogger::FatalLevel:
// 				pItem->setBackgroundColor(Qt::red);
// 				break;
// 			}
// 
// 			pItem = new QTableWidgetItem;
// 			pItem->setText(vt.toString());
// 			setItem(nRow,2,pItem);
// 
// 			nRow++;
// 		}
// 
// 	}
}


