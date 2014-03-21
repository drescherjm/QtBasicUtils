#ifndef __QUPDATETRACKER_H__
#define __QUPDATETRACKER_H__

namespace QTUTILS {

class QUpdateTracker
{
public:
	QUpdateTracker(bool bChanged=false);
public:
	virtual bool Modify();
	virtual bool HasChanged();
	virtual bool ForceUnmodified();
private:
	bool	m_bChanged;
};

/////////////////////////////////////////////////////////////////////////////////////////

inline QUpdateTracker::QUpdateTracker(bool bChanged) : m_bChanged(bChanged)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

inline bool QUpdateTracker::Modify()
{
	bool retVal = HasChanged();
	m_bChanged = true;
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

inline bool QUpdateTracker::HasChanged()
{
	return m_bChanged;
}

/////////////////////////////////////////////////////////////////////////////////////////

inline bool QUpdateTracker::ForceUnmodified()
{
	bool retVal = HasChanged();
	m_bChanged = false;
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

}; //namespace QTUTILS

#endif //__QUPDATETRACKER_H__
