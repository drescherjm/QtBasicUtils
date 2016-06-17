#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuCTSQLColumn.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuCTSQLColumn::qbuCTSQLColumn() : m_bPrimaryKey(false)
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuCTSQLColumn::getColDef() const
{
	QString retVal;
	retVal = m_strColumnName;
	if (!m_strDataType.isEmpty()) {
		retVal.append(" ");
		retVal.append(m_strDataType);
	}
	if (!m_strConstraints.isEmpty()) {
		retVal.append(" ");
		retVal.append(m_strConstraints);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////
