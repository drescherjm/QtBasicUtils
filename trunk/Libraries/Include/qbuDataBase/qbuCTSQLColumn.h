#pragma once

#ifndef QBUCTSQLCOLUMN_H
#define QBUCTSQLCOLUMN_H

/////////////////////////////////////////////////////////////////////////////////////////

struct qbuCTSQLColumn
{
public:
	qbuCTSQLColumn();
public:
	QString m_strColumnName;
	QString m_strDataType;
	QString m_strConstraints;
	bool	m_bPrimaryKey;
public:
	QString getColDef() const;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUCTSQLCOLUMN_H
