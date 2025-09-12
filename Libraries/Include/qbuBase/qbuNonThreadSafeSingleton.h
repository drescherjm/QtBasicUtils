#pragma once

#ifndef QBUNONTHREADSAFESINGLETON_H
#define QBUNONTHREADSAFESINGLETON_H

/////////////////////////////////////////////////////////////////////////////////////////
//	
// Note this Singleton is perfectly safe to use as long as we can insure that only 1 
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

#endif // QBUNONTHREADSAFESINGLETON_H
