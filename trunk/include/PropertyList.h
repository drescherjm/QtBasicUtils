#ifndef __PROPERTYLIST_H__
#define __PROPERTYLIST_H__

/////////////////////////////////////////////////////////////////////////////////////////

#include "Property.h"
#include "UserPropery.h"
#include <QList>

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

	class PropertyList : public UserProperty
	{
		Q_OBJECT
	public:
		PropertyList();
		virtual ~PropertyList();
		PropertyList(const PropertyList & other);
		PropertyList& operator=(const PropertyList & other);
		bool PropertyList::operator==( const PropertyList & other ) const;
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
		QString			toXML(bool bMakeRoot = true);
		bool			fromXML(QString strXML);
		bool			fromXML(QDomElement & domElem);
		bool			Load(QString strFile);
		bool			Save(QString strFile);
		void			Print(std::ostream & st);
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

}; // namespace QTUTILS

/////////////////////////////////////////////////////////////////////////////////////////

//Q_DECLARE_METATYPE(QTUTILS::PropertyList)
Q_DECLARE_METATYPE(QTUTILS::PropertyList*)

#endif //__PROPERTYLIST_H__
