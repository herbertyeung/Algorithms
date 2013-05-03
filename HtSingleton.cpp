#include "stdafx.h"
#include "HtSingleton.h"

template<class T>
T *HtSingleton<T>::m_pInstance = NULL;

template<class T>
HtSingleton<T>::HtSingleton(void)
{
	InitializeCriticalSection(&g_locker);
}

template<class T>
HtSingleton<T>::~HtSingleton(void)
{
	DeleteCriticalSection(&g_locker);
}

template<class T>
T* HtSingleton<T>::Instance()
{
	HtLock lock;
	if(m_pInstance == NULL)
		m_pInstance = new T();
	
	return m_pInstance;
}

template<class T>
void HtSingleton<T>::Destory()
{
	HtLock lock;
	if(m_pInstance != NULL)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}