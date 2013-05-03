#pragma once
#include <Windows.h>


static CRITICAL_SECTION g_locker;

template<class T>
class HtSingleton
{
public:
	HtSingleton(void);
	~HtSingleton(void);

	static T * Instance();
	static void Destory();
protected:
	static T *m_pInstance;
};



class HtLock
{
public:
	HtLock(){EnterCriticalSection(&g_locker); }
	~HtLock(){LeaveCriticalSection(&g_locker);}

};