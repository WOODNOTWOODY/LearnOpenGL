#include "CoreStd.h"
#include "Mutex.h"

#if PLATFORM == PLATFORM_WINDOWS

LightWeightMutex::LightWeightMutex()
	: m_counter(0)
{
	m_semaphore = CreateSemaphore(NULL, 0, 1, NULL);
}

LightWeightMutex::~LightWeightMutex()
{
	CloseHandle(m_semaphore);
}

void LightWeightMutex::lock()
{
	if (_InterlockedIncrement(&m_counter) > 1)
	{
		WaitForSingleObject(m_semaphore, INFINITE);
	}
}

void LightWeightMutex::unlock()
{
	if (_InterlockedDecrement(&m_counter) > 0)
	{
		ReleaseSemaphore(m_semaphore, 1, NULL);
	}
}

bool LightWeightMutex::tryLock()
{
	LONG result = _InterlockedCompareExchange(&m_counter, 1, 0);
	return (result == 0);
}

#elif PLATFORM == PLATFORM_LINUX

LightWeightMutex::LightWeightMutex() 
{ 
	pthread_mutex_init(&m_mutex, NULL); 
}

LightWeightMutex::~LightWeightMutex() 
{ 
	pthread_mutex_destroy(&m_mutex); 
}

void LightWeightMutex::lock() 
{ 
	pthread_mutex_lock(&m_mutex); 
}

void LightWeightMutex::unlock() 
{ 
	pthread_mutex_unlock(&m_mutex); 
}

bool LightWeightMutex::tryLock() 
{ 
	return (pthread_mutex_trylock(&m_mutex) == 0); 
}

#endif