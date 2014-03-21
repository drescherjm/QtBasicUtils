#ifndef __PROPERTYLIST_H__
#define __PROPERTYLIST_H__

/////////////////////////////////////////////////////////////////////////////////////////

#include "qbuBase/Property.h"
#include "UserPropery.h"
#include <QList>



/////////////////////////////////////////////////////////////////////////////////////////

	class PropertyList : public UserProperty
	{
		Q_OBJECT
	public:
		PropertyList();
		virtual ~PropertyList();
		PropertyList(const PropertyList & other);
		PropertyList& operator=(const PropertyList & other);
		bool operator==( const PropertyList & other ) const;
	public:
		typedef QList<Property*> List;
		typedef List::iterator iterator;
		typedef List::const_iterator const_iterator;

		void			push_back(Property* pProp);
		void			push_back(Property & prop);
		void			push_back(PropertyList * lst);
		void			push_front(Property* pProp);
		void			push_front(Property & prop);
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
		List			m_lstProps;
	protected:
		QString			CleanUpName(QString strName);
	public:
		static	int		m_nMetaID;
	private:
		void			copy( const PropertyList & other );
		void			destroy();
		
	};

/////////////////////////////////////////////////////////////////////////////////////////

	inline void PropertyList::clear()
	{
		destroy();
	}

/////////////////////////////////////////////////////////////////////////////////////////

	inline bool PropertyList::empty() const
	{
		return m_lstProps.empty();
	}

/////////////////////////////////////////////////////////////////////////////////////////

//Q_DECLARE_METATYPE(PropertyList)
Q_DECLARE_METATYPE(PropertyList*)

#endif //__PROPERTYLIST_H__
