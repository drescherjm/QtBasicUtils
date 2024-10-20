#pragma once

#ifndef QBUPROPERTYLIST_H
#define QBUPROPERTYLIST_H

/////////////////////////////////////////////////////////////////////////////////////////

#include "qbuBase/qbuProperty.h"
#include "qbuBase/qbuUserPropery.h"
#include <QList>

/////////////////////////////////////////////////////////////////////////////////////////

class qbuPropertyList : public qbuUserProperty
{
	Q_OBJECT
public:
	qbuPropertyList();
	virtual ~qbuPropertyList();
	qbuPropertyList(const qbuPropertyList & other);
	qbuPropertyList& operator=(const qbuPropertyList & other);
	bool operator==( const qbuPropertyList & other ) const;
public:
	using List =  QList<qbuProperty*>;
	using iterator = List::iterator;
	using const_iterator = List::const_iterator;

	void			push_back(qbuProperty* pProp);
	void			push_back(qbuProperty & prop);
	void			push_back(qbuPropertyList * lst);
	void			push_front(qbuProperty* pProp);
	void			push_front(qbuProperty & prop);
	iterator		begin();
	iterator		end();
	const_iterator	begin() const;
	const_iterator	end() const;
	void			clear();
	int				size() const;
	bool			empty() const;
public:
	QString			toXML(bool bMakeRoot = true,qbuITKIndent indent = qbuITKIndent());
	bool			fromXML(QString strXML);
	bool			fromXML(QDomElement & domElem);
	bool			Load(QString strFile);
	bool			Save(QString strFile);
	void			Print(std::ostream & st,qbuITKIndent indent = qbuITKIndent());
	void			Print(QTextStream & st,qbuITKIndent indent = qbuITKIndent());

protected:
	virtual void	propertyInserted(qbuProperty* pProp);

protected:
	List			m_lstProps;
protected:
	QString			CleanUpName(QString strName);
public:
	static	int		m_nMetaID;
private:
	void			copy( const qbuPropertyList & other );
	void			destroy();
	
};

/////////////////////////////////////////////////////////////////////////////////////////

inline void qbuPropertyList::clear()
{
	destroy();
}

/////////////////////////////////////////////////////////////////////////////////////////

inline bool qbuPropertyList::empty() const
{
	return m_lstProps.empty();
}

/////////////////////////////////////////////////////////////////////////////////////////

//Q_DECLARE_METATYPE(qbuPropertyList)
Q_DECLARE_METATYPE(qbuPropertyList*)

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUPROPERTYLIST_H
