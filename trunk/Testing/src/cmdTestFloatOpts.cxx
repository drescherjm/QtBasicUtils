QCmdTestFloatOpts::QCmdTestFloatOpts(QString strName, QString strDescription) :
QCmd(strName,strDescription)
{
	AddArg("CaseNumber","The case number","",(quint32)0);

	float fTemp = 32.0f;
	AddOpt("T","Temperature","Temperature in Fahrenheit",fTemp);
}

int QCmdTestFloatOpts::Execute()
{
	quint32 nCase;
	GetArg("CaseNumber",nCase);

	std::cout << "CaseNumber=" << nCase << std::endl;

	float fTemp = 100.0f;
	GetOpt("T",fTemp);

	std::cout << "Temperature=" << fTemp << std::endl;

	return QCmdParseError::STATUS_OK;
}