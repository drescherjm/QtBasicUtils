#ifndef __SMDATABASEMACROS_H__
#define __SMDATABASEMACROS_H__

/////////////////////////////////////////////////////////////////////////////////////////

#define IMPLEMENT_SA_SET(className,variableName, variableType, strColumName) \
	bool className::set##variableName( variableType _value ) \
	{ \
		QTUTILS::Property prop; \
		prop.setObjectName(strColumName); \
		prop.SetData(_value); \
		\
		return (insert(prop) != end()); \
	}

/////////////////////////////////////////////////////////////////////////////////////////

#define IMPLEMENT_SA_GET(className,variableName, variableType, strColumName) \
	bool className::get##variableName( variableType & _value ) \
	{ \
		bool retVal; \
		retVal = className::getField<variableType>(strColumName,_value); \
		return retVal; \
	}

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMDATABASEMACROS_H__