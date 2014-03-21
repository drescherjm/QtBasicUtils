#pragma once

#ifndef __NONTHREADSAFESINGLETON_H__
#define __NONTHREADSAFESINGLETON_H__

/////////////////////////////////////////////////////////////////////////////////////////
//	
// Note this Singelton is perfectly safe to use as long as we can insure that only 1 
// thread calls instance() the first time. The simplest way to do this call instance() 
// before additional application threads are created.
//
/////////////////////////////////////////////////////////////////////////////////////////

template <class Super> 
class NonThreadSafeSingleton
{
public:
	static Super* instance()
	{
		static Super inst;
		return &inst;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // __NONTHREADSAFESINGLETON_H__

