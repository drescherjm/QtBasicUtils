#include "testxmlperf.h"
#include "qbuBase/qbuProperty.h"
#include "qbuCmdLine/QCmdParseError.h"
#include "qbuCmdLine/QCmdParseException.h"
#include "qbuCmdLine/QCmdHelpException.h"
#include "qbuBase/qbuPropertyMap.h"
#include <iostream>
#include <string>
#include <QDate>
#include "qxml.h"
#include "qdebug.h"
#include <chrono>
#include <ctime>
//#include <QStringLiteral>

/////////////////////////////////////////////////////////////////////////////////////////

enum GenerateType {
	Session,
	ProjectExamCompletion,
	Ratings,
	Update,
};

/////////////////////////////////////////////////////////////////////////////////////////

struct QCmdTestXMLPerformance::qbuPrivate
{
	bool test_exportXML(qbuProperty & prop);
	QString generate(GenerateType gt, uint32_t nLines);
	QString generateLine(GenerateType gt);
	bool test0();
	bool test1();
	bool test2();
};

/////////////////////////////////////////////////////////////////////////////////////////

QCmdTestXMLPerformance::QCmdTestXMLPerformance(QString strName, QString strDescription) :
QCmd(strName, strDescription), m_pPrivate{ std::make_unique<qbuPrivate>() }
{
	int nTest = 0;
	AddArg("Test","Run test #","",nTest);
}

/////////////////////////////////////////////////////////////////////////////////////////

QCmdTestXMLPerformance::~QCmdTestXMLPerformance()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

bool QCmdTestXMLPerformance::qbuPrivate::test_exportXML(qbuProperty & prop)
{
	std::cout << "BEGIN: Testing test_exportXML" << std::endl;

	QString strXML = prop.toXML();
	qbuProperty prop1;
	prop1.fromXML(strXML);
	QString strXML1 = prop1.toXML();

	std::cout << "Prop= " <<  strXML.toStdString() << std::endl;
	std::cout << "Prop1= " << strXML1.toStdString() << std::endl;

	std::cout << "END: Testing test_exportXML" << std::endl;

	return (strXML.compare(strXML1) == 0);
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmdTestXMLPerformance::qbuPrivate::generate(GenerateType gt, uint32_t nLines)
{
	QString retVal;

	for (uint32_t nLine = 0; nLine < nLines; ++nLine) {
		retVal += generateLine(gt);
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmdTestXMLPerformance::qbuPrivate::generateLine(GenerateType gt)
{
	QString retVal;

	switch (gt)
	{
	case Session:
		retVal = R"(INSERT OR IGNORE INTO Session (PROJECTID, READERID, SCORINGSYSTEMID, SESSIONBEGINDATE, SESSIONID) VALUES ( 101, 500, 13, '2016-02-24T12:59:41.993', 1 );)";
		break;
	case ProjectExamCompletion:
		retVal = R"(INSERT OR IGNORE INTO ReaderExamCompletion (COMPLETED, EXAMID, PATIENTID, PROJECTID, PROJECTMODEID, READEREXAMCOMPLETIONBEGINDATE, READEREXAMCOMPLETIONENDDATE, READEREXAMCOMPLETIONLASTEDITDATE, READEREXAMCOMPLETIONLASTEDITSCORINGSYSTEM, READEREXAMCOMPLETIONNUMBEROFEDITS, READERID, READINGTYPEID, SCORINGSYSTEMID, SESSIONID, SHOW) VALUES ( 1, 1, 3414, 101, 1, '2017-10-24T13:14:04.905', '2017-10-24T13:14:22.488', '2017-09-20T15:05:02.331', 53, 1, 104, 20, 52, 8929, 1 );)";
		break;
	case Ratings:
		switch (rand() % 3)
		{
		case 0:
			retVal = R"(INSERT OR IGNORE INTO Ratings (EDITS, EXAMID, FORMID, PATIENTID, PROJECTID, PROJECTMODEID, RATING, RATINGFIRSTEDITDATE, RATINGID, RATINGLASTEDITDATE, RATINGTYPEID, READERID, READERREPORTQUESTIONID, READINGID, RESULTID, RESULTSCOPETYPEID, SCORINGSYSTEMID, SESSIONID) VALUES ( 0, 1, 25, 617, 101, 4, 'Lesion 2: "I think this may be a lymph node"', '2017-02-16T14:32:01.328', 1, '2017-02-16T14:57:47.303', 62, 998, 193, 0, -1, 6, 13, 7445 ); )";
			break;
		case 1:
			retVal = R"(INSERT OR IGNORE INTO Ratings (EDITS, EXAMID, FORMID, PATIENTID, PROJECTID, PROJECTMODEID, RATING, RATINGFIRSTEDITDATE, RATINGID, RATINGLASTEDITDATE, RATINGTYPEID, READERID, READERREPORTQUESTIONID, READINGID, RESULTID, RESULTSCOPETYPEID, SCORINGSYSTEMID, SESSIONID) VALUES ( 0, 3, 25, 1219, 101, 4, 'Lesion 1: ? area of dense tissue', '2016-10-26T08:46:03.059', 1, '2016-09-23T10:11:45.801', 62, 998, 193, 0, -1, 6, 52, 9461 );)";
			break;
		case 2:
			retVal = R"(INSERT OR IGNORE INTO Ratings (EDITS, EXAMID, FORMID, PATIENTID, PROJECTID, PROJECTMODEID, RATING, RATINGFIRSTEDITDATE, RATINGID, RATINGLASTEDITDATE, RATINGTYPEID, READERID, READERREPORTQUESTIONID, READINGID, RESULTID, RESULTSCOPETYPEID, SCORINGSYSTEMID, SESSIONID) VALUES ( 0, 1, 37, 6544, 101, 1, '8:00', '2017-01-17T16:41:09.071', 56, '2016-07-29T13:36:36.581', 42, 402, 52, 1, -1, 12, 16, 2625 ); )";
			break;
		}
		break;
	case Update:
		retVal = R"(UPDATE CompletedExamBIRADS SET  ReaderID = 303 ,  ScoringSystemID = 54 ,  SessionID = 40 ,  RightBIRADSRating = '3 - 6M F/U' ,  LeftBIRADSRating = '1' ,  ImagingNotPerformed = 0 ,  CEBShow = 1 ,  CEBLastEditScoringSystemID = 54 ,  CEBEdits = 2 ,  CEBLastEditDate = '2017-11-03T14:11:35.106'  WHERE  ( ProjectID = 101 )  AND  ( ProjectModeID = 1 )  AND  ( ExamID = 1 )  AND  ( PatientID = 9267 )  AND  ( FormID = 37 )  AND  ( ReadingID = 1 )  AND  (  ( datetime(CEBLastEditDate) < datetime('2017-11-03T14:11:35') )  OR CEBLastEditDate is NULL ) ;)";
		break;
	default:
		break;
	}

	retVal += '\n';

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool QCmdTestXMLPerformance::qbuPrivate::test0()
{

	QString strSQL = generate(Session, 20000);

	strSQL += generate(ProjectExamCompletion, 100000);
	strSQL += generate(Ratings, 500000);
	strSQL += generate(Update, 1000);

	qbuProperty prop;
	prop.setObjectName("SQL");
	prop.SetData(strSQL);

	auto start = std::chrono::system_clock::now();

	QString strXML = prop.toXML();

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;

	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::cout << "finished computation at " << std::ctime(&end_time)
		<< "elapsed time (toXML): " << elapsed_seconds.count() << "s\n";


	std::cout << "SQLSize " << strSQL.size() << "\n";
	std::cout << "XMLSize " << strXML.size() << "\n";

	qbuProperty prop1;

	auto start1 = std::chrono::system_clock::now();
	prop1.fromXML(strXML);
	auto end1 = std::chrono::system_clock::now();

	{
		std::chrono::duration<double> elapsed_seconds = end1 - start1;
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);

		std::cout << "finished computation at " << std::ctime(&end_time)
			<< "elapsed time (fromXML): " << elapsed_seconds.count() << "s\n";
	}

	QString strSQL1 = prop1.GetData().toString();

	bool retVal = (strSQL.compare(strSQL1, Qt::CaseInsensitive) == 0);

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool QCmdTestXMLPerformance::qbuPrivate::test1()
{

	QString strSQL = generate(Session, 20000);

	strSQL += generate(ProjectExamCompletion, 200000);
	strSQL += generate(Ratings, 1000000);
	strSQL += generate(Update, 5000);

	qbuProperty prop;
	prop.setObjectName("SQL");
	prop.SetData(strSQL);

	auto start = std::chrono::system_clock::now();

	QString strXML = prop.toXML();

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;

	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::cout << "finished computation at " << std::ctime(&end_time)
		<< "elapsed time (toXML): " << elapsed_seconds.count() << "s\n";


	std::cout << "SQLSize " << strSQL.size() << "\n";
	std::cout << "XMLSize " << strXML.size() << "\n";

	qbuProperty prop1;

	auto start1 = std::chrono::system_clock::now();
	prop1.fromXML(strXML);
	auto end1 = std::chrono::system_clock::now();

	{
		std::chrono::duration<double> elapsed_seconds = end1 - start1;
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);

		std::cout << "finished computation at " << std::ctime(&end_time)
			<< "elapsed time (fromXML): " << elapsed_seconds.count() << "s\n";
	}

	QString strSQL1 = prop1.GetData().toString();

	bool retVal = (strSQL.compare(strSQL1, Qt::CaseInsensitive) == 0);

	return retVal;
}


/////////////////////////////////////////////////////////////////////////////////////////

bool QCmdTestXMLPerformance::qbuPrivate::test2()
{

	const QString sqlTag{ QStringLiteral("SQLSTATEMENT") };

	QString strSQL = generate(Session, 20000);

	strSQL += generate(ProjectExamCompletion, 20000);
	strSQL += generate(Ratings, 100000);
	strSQL += generate(Update, 5000);

	qbuPropertyMap props0;

	{
		qbuProperty prop;
		prop.setObjectName("Name");
		prop.SetData("2018-06-13-001.RADIMGWS85.WBUS_2015.FULL.sql");
		props0.insert(prop);
	}

	{	qbuProperty prop;
		prop.setObjectName("NetworkPeerID");
		prop.SetData(static_cast<uint32_t>(54));
		props0.insert(prop);
	}

	{	qbuProperty prop;
		prop.setObjectName("ProjectID");
		prop.SetData(static_cast<uint32_t>(101));
		props0.insert(prop);
	}

	{	qbuProperty prop;
		prop.setObjectName("ScoringSystemID");
		prop.SetData(static_cast<uint32_t>(9));
		props0.insert(prop);
	}

	{
		qbuProperty prop;
		prop.setObjectName(sqlTag);
		prop.SetData(strSQL);
		props0.insert(prop);
	}

	auto start = std::chrono::system_clock::now();
	

	QString strXML = props0.toXML();

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;

	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::cout << "finished computation at " << std::ctime(&end_time)
		<< "elapsed time (toXML): " << elapsed_seconds.count() << "s\n";


	std::cout << "SQLSize " << strSQL.size() << "\n";
	std::cout << "XMLSize " << strXML.size() << "\n";

	qbuPropertyMap  props1;

	auto start1 = std::chrono::system_clock::now();
	props1.fromXML(strXML);
	auto end1 = std::chrono::system_clock::now();

	{
		std::chrono::duration<double> elapsed_seconds = end1 - start1;
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);

		std::cout << "finished computation at " << std::ctime(&end_time)
			<< "elapsed time (fromXML): " << elapsed_seconds.count() << "s\n";
	}

	QString strSQL1;
	
	bool retVal = props1.getField<QString>(sqlTag, strSQL1);

	if (retVal) {
		//	QString strSQL1 = prop1.GetData().toString();

		retVal = (strSQL.compare(strSQL1, Qt::CaseInsensitive) == 0);
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

// static bool test0()
// {
// 
// 	qbuProperty prop;
// 
// 	prop.setObjectName("Name");
// 	prop.SetData(QString("John M. Drescher"));
// 	
// 	return test_exportXML(prop);
// }
// 
// /////////////////////////////////////////////////////////////////////////////////////////
// 
// static bool test1()
// {
// 
// 	qbuProperty prop;
// 
// 	prop.setObjectName("Age");
// 	prop.SetData((int)37);
// 	
// 	return test_exportXML(prop);
// }
// 
// /////////////////////////////////////////////////////////////////////////////////////////
// 
// static bool test2()
// {
// 
// 	qbuProperty prop;
// 
// 	prop.setObjectName("Sex");
// 	prop.SetData(QChar('M'));
// 	
// 	return test_exportXML(prop);
// }
// 
// /////////////////////////////////////////////////////////////////////////////////////////
// 
// static bool test3()
// {
// 	qbuPropertyMap pc;
// 	qbuProperty prop;
// 	
// 	prop.setObjectName("Age");
// 	prop.SetData((int)37);
// 	pc.insert(prop);
// 
// 	prop.setObjectName("Name");
// 	prop.SetData(QString("John M. Drescher"));
// 	pc.insert(prop);
// 
// 	prop.setObjectName("Sex");
// 	prop.SetData(QChar('M'));
// 	pc.insert(prop);
// 
// 	QString str = pc.toXML();
// 
// 	qbuPropertyMap pc1;
// 
// 	bool retVal = pc1.fromXML(str);
// 
// 	QString str1 = pc1.toXML();
// 
// 	if (retVal) {
// 		retVal = (str.compare(str1,Qt::CaseInsensitive) == 0);
// 	}
// 	
// 	return retVal;	
// }
// 
// /////////////////////////////////////////////////////////////////////////////////////////
// 
// static bool test4()
// {
// 
// 	qbuPropertyMap pmPeople,pmJohn, pmKathy;
// 	qbuProperty prop;
// 
// 	prop.setObjectName("Age");
// 	prop.SetData((int)37);
// 	pmJohn.insert(prop);
// 
// 	prop.setObjectName("Name");
// 	prop.SetData(QString("John M. Drescher"));
// 	pmJohn.insert(prop);
// 
// 	prop.setObjectName("Best Friend");
// 	prop.SetData(QString("Kathy M. Zorn"));
// 	pmJohn.insert(prop);
// 
// 	prop.setObjectName("Sex");
// 	prop.SetData(QChar('M'));
// 	pmJohn.insert(prop);
// 
// 	prop.setObjectName("Person0");
// 	prop.SetData(QVariant::fromValue(pmJohn));
// 	pmPeople.insert(prop);
// 
// 	prop.setObjectName("Age");
// 	prop.SetData((int)40);
// 	pmKathy.insert(prop);
// 
// 	prop.setObjectName("Name");
// 	prop.SetData(QString("Kathy M. Zorn"));
// 	pmKathy.insert(prop);
// 
// 	prop.setObjectName("Best Friend");
// 	prop.SetData(QString("John M. Drescher"));
// 	pmKathy.insert(prop);
// 
// 	prop.setObjectName("Sex");
// 	prop.SetData(QChar('F'));
// 	pmKathy.insert(prop);
// 
// 	prop.setObjectName("Person1");
// 	prop.SetData(QVariant::fromValue(pmKathy));
// 	pmPeople.insert(prop);
// 
// 	QString str = pmPeople.toXML();
// 
// 	qbuPropertyMap pc1;
// 
// 	bool retVal = pc1.fromXML(str);
// 
// 	QString str1 = pc1.toXML();
// 
// 	if (retVal) {
// 		retVal = (str.compare(str1,Qt::CaseInsensitive) == 0);
// 	}
// 
// 	return retVal;	
// 
// }
// 
// /////////////////////////////////////////////////////////////////////////////////////////
// 
// static bool test5()
// {
// 
// 	qbuPropertyMap pmPeople,pmJohn, pmKathy;
// 	qbuProperty prop;
// 
// 	prop.setObjectName("Age");
// 	prop.SetData((int)37);
// 	pmJohn.insert(prop);
// 
// 	prop.setObjectName("Name");
// 	prop.SetData(QString("John M. Drescher"));
// 	pmJohn.insert(prop);
// 
// 	prop.setObjectName("Best Friend");
// 	prop.SetData(QString("Kathy M. Zorn"));
// 	pmJohn.insert(prop);
// 
// 	prop.setObjectName("Sex");
// 	prop.SetData(QChar('M'));
// 	pmJohn.insert(prop);
// 
// 	prop.setObjectName("DOB");
// 	prop.SetData(QDate(1972,1,10));
// 	pmJohn.insert(prop);
// 
// 	prop.setObjectName("Some Extra data");
// 	prop.SetData((float)-1.222);
// 	pmJohn.insert(prop);
// 
// 	prop.setObjectName("Person0");
// 	prop.SetData(QVariant::fromValue(pmJohn));
// 	pmPeople.insert(prop);
// 
// 	prop.setObjectName("Age");
// 	prop.SetData((int)40);
// 	pmKathy.insert(prop);
// 
// 	prop.setObjectName("Name");
// 	prop.SetData(QString("Kathy M. Zorn"));
// 	pmKathy.insert(prop);
// 
// 	prop.setObjectName("Best Friend");
// 	prop.SetData(QString("John M. Drescher"));
// 	pmKathy.insert(prop);
// 
// 	prop.setObjectName("Sex");
// 	prop.SetData(QChar('F'));
// 	pmKathy.insert(prop);
// 
// 	prop.setObjectName("DOB");
// 	prop.SetData(QDate(1969,1,13));
// 	pmKathy.insert(prop);
// 
// 	prop.setObjectName("Person1");
// 	prop.SetData(QVariant::fromValue(pmKathy));
// 	pmPeople.insert(prop);
// 
// 	QString str = pmPeople.toXML();
// 	bool retVal = pmPeople.Save("People.xml");
// 	if (retVal) {
// 		qbuPropertyMap pc1;
// 
// 		retVal = pc1.Load("People.xml");
// 
// 		QString str1 = pc1.toXML();
// 
// 		if (retVal) {
// 			retVal = (str.compare(str1,Qt::CaseInsensitive) == 0);
// 		}
// 	}
// 
// 	return retVal;	
// }
// 
// /////////////////////////////////////////////////////////////////////////////////////////
// 
// static bool test6()
// {
// 	//This tests the update tracking of qbuPropertyMap
// 
// 	qbuPropertyMap pmPeople,pmJohn, pmKathy;
// 	qbuProperty prop;
// 
// 	bool retVal = !pmJohn.HasChanged();
// 
// 	if (retVal) {
// 		prop.setObjectName("Age");
// 		prop.SetData((int)37);
// 		pmJohn.insert(prop);
// 		
// 		retVal = pmJohn.HasChanged();
// 
// 		if (retVal) {
// 			
// 			pmJohn.ForceUnmodified();
// 
// 			retVal = !pmJohn.HasChanged();
// 
// 			if (retVal) {
// 				prop.setObjectName("Name");
// 				prop.SetData(QString("John M. Drescher"));
// 				pmJohn.insert(prop);
// 
// 
// 				prop.setObjectName("Best Friend");
// 				prop.SetData(QString("Kathy M. Zorn"));
// 				pmJohn.insert(prop);
// 
// 				prop.setObjectName("Sex");
// 				prop.SetData(QChar('M'));
// 				pmJohn.insert(prop);
// 
// 				retVal = pmJohn.HasChanged();
// 			}
// 
// 		}		
// 	}
// 
// 	return retVal;
// }
// 
// /////////////////////////////////////////////////////////////////////////////////////////
// 
// static bool test7()
// {
// 	QString testXML("<xml ty=\"127\"><RMTPatientID>HB016603</RMTPatientID></xml>");
// 	qbuPropertyMap map;
// 	bool retVal = map.fromXML(testXML);
// 	if (retVal) {
// 
// 	}
// 	return retVal;
// }
// 
// /////////////////////////////////////////////////////////////////////////////////////////
// 
// static bool test8()
// {
// 	qbuPropertyMap pc;
// 	qbuProperty prop;
// 
// 	prop.setObjectName("Age");
// 	prop.SetData((int)37);
// 	pc.insert(prop);
// 
// 	prop.setObjectName("Name");
// 	prop.SetData(QString("John M. Drescher"));
// 	pc.insert(prop);
// 
// 	prop.setObjectName("Sex");
// 	prop.SetData(QChar(' '));
// 	pc.insert(prop);
// 
// 	QString str = pc.toXML();
// 
// 	qbuPropertyMap pc1;
// 
// 	bool retVal = pc1.fromXML(str);
// 
// 	QString str1 = pc1.toXML();
// 
// 	if (retVal) {
// 		retVal = (str.compare(str1,Qt::CaseInsensitive) == 0);
// 	}
// 
// 	return retVal;	
// }
// 
// static bool test9() 
// {
// 	QString xmlString("<original>      </original>");
// 	QDomDocument doc;
// 	doc.setContent(xmlString);
// 	QDomElement docElem = doc.documentElement();
// 	qDebug() << "Without QXmlSimpleReader \t- element contains" <<docElem.text() << "\tlength="<< docElem.text().length();
// 	doc.clear();
// 	QXmlInputSource source;
// 	source.setData(xmlString);
// 	QXmlSimpleReader reader;
// 	doc.setContent(&source, &reader);
// 	docElem = doc.documentElement();
// 	qDebug() << "With QXmlSimpleReader \t- element contains" <<docElem.text() << "\tlength="<< docElem.text().length();
// 
// 	return false;
// }
// 
// /////////////////////////////////////////////////////////////////////////////////////////
// 
// static bool test10()
// {
// 	qbuPropertyMap pc;
// 	qbuProperty prop;
// 
// 	QString strSQL = QString("SELECT *\n FROM Table\n WHERE StudyID < 10");
// 
// 	prop.setObjectName("SQL");
// 	prop.SetData(strSQL);
// 	pc.insert(prop);
// 
// 	prop.setObjectName("Name");
// 	prop.SetData(QString("John M. Drescher"));
// 	pc.insert(prop);
// 
// 	prop.setObjectName("Sex");
// 	prop.SetData(QChar(' '));
// 	pc.insert(prop);
// 
// 	QString str = pc.toXML();
// 
// 	qbuPropertyMap pc1;
// 
// 	bool retVal = pc1.fromXML(str);
// 
// 	QString str1 = pc1.toXML();
// 
// 	if (retVal) {
// 		retVal = (str.compare(str1, Qt::CaseInsensitive) == 0);
// 	}
// 
// 	if (retVal) {
// 		QString strTest;
// 		
// 		qbuPropertyMap::iterator it = pc1.find("SQL");
// 
// 		retVal = (it != pc1.end());
// 
// 		if (retVal) {
// 			qbuProperty* pProp = *it;
// 
// 			retVal = (pProp != nullptr);
// 
// 			if (retVal) {
// 				strTest = pProp->GetData().toString();
// 
// 				if (retVal) {
// 					retVal = (strTest.trimmed().compare(strSQL.trimmed(), Qt::CaseInsensitive) == 0);
// 				}
// 			}
// 
// 			if (retVal) {
// 				QString strMsg = QString("The SQL matches between (%1) and (%2)").arg(strSQL).arg(strTest);
// 				std::cout << qPrintable(strMsg) << std::endl;
// 			}
// 			else
// 			{
// 				QString strMsg = QString("The SQL does NOT match between (%1) and (%2)").arg(strSQL).arg(strTest);
// 				std::cout << qPrintable(strMsg) << std::endl;
// 			}
// 		}
// 		
// 	}
// 
// 	if (!retVal) {
// 		QString("%1 failed. A string containing the '<' character will not work in an xml export / import");
// 	}
// 
// 	return retVal;
// }
// 
// 
// /////////////////////////////////////////////////////////////////////////////////////////
// 
// static bool test11()
// {
// 	qbuPropertyMap pc;
// 	qbuProperty prop;
// 
// 	QString strSQL = QString("SELECT *\n FROM Table\n WHERE StudyID > 10");
// 
// 	prop.setObjectName("SQL");
// 	prop.SetData(strSQL);
// 	pc.insert(prop);
// 
// 	prop.setObjectName("Name");
// 	prop.SetData(QString("John M. Drescher"));
// 	pc.insert(prop);
// 
// 	prop.setObjectName("Sex");
// 	prop.SetData(QChar(' '));
// 	pc.insert(prop);
// 
// 	QString str = pc.toXML();
// 
// 	qbuPropertyMap pc1;
// 
// 	bool retVal = pc1.fromXML(str);
// 
// 	QString str1 = pc1.toXML();
// 
// 	if (retVal) {
// 		retVal = (str.compare(str1, Qt::CaseInsensitive) == 0);
// 	}
// 
// 	if (!retVal) {
// 		QString("%1 failed. A string containing the '>' character will not work in an xml export / import");
// 	}
// 
// 	return retVal;
// }

/////////////////////////////////////////////////////////////////////////////////////////

int  QCmdTestXMLPerformance::Execute()
{
	int nTest;

	GetArg("Test",nTest);

	bool bVal;
	switch(nTest) {
	case 0:
		bVal = m_pPrivate->test0();
		break;
	case 1:
		bVal = m_pPrivate->test1();
		break;
	case 2:
		bVal = m_pPrivate->test2();
		break;
	default:
		bVal = false;
	}

	return bVal ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;
}


/////////////////////////////////////////////////////////////////////////////////////////


