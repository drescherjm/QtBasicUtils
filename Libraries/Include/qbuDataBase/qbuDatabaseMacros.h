#pragma once

#ifndef QBUDATABASEMACROS_H
#define QBUDATABASEMACROS_H

/////////////////////////////////////////////////////////////////////////////////////////

#define IMPLEMENT_SA_SET(className,variableName, variableType, strColumName) \
	bool className::set##variableName( variableType _value ) \
	{ \
		qbuProperty prop; \
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

#define IMPLEMENT_SA_GET_CONST(className,variableName, variableType, strColumName) \
	bool className::get##variableName( variableType & _value ) const \
																{ \
		bool retVal; \
		retVal = className::getField<variableType>(strColumName,_value); \
		return retVal; \
																}

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUDATABASEMACROS_H
