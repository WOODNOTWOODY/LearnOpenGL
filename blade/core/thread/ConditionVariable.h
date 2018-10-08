#ifndef __CONDITION_VARIABLE_H__
#define __CONDITION_VARIABLE_H__

#include "Mutex.h"

#if PLATFORM == PLATFORM_WINDOWS

class ConditionVariable
{
public:
	ConditionVariable(Mutex* m)
		: m_pMutex(m)
	{
		InitializeConditionVariable(&m_cond);
	}

	~ConditionVariable() {}

public:
	inline void beginSynchronized() { m_pMutex->lock(); }
	inline void endSynchronized() { m_pMutex->unlock(); }

	inline void wait() { SleepConditionVariableCS(&m_cond, &(m_pMutex->m_criticalSection), INFINITE); }
	inline void signal() { WakeConditionVariable(&m_cond); }
	inline void broadcast() { WakeAllConditionVariable(&m_cond); }

private:
	CONDITION_VARIABLE m_cond;
	Mutex*             m_pMutex;

	// disable copy constructor and assignment
	ConditionVariable(const ConditionVariable&);
	ConditionVariable& operator = (const ConditionVariable&);
};

#elif PLATFORM == PLATFORM_LINUX

class ConditionVariable
{
public:
	ConditionVariable(Mutex* m)
		: m_pMutex(m)
	{
		pthread_cond_init(&m_cond, NULL);
	}

	~ConditionVariable() { pthread_cond_destroy(&m_cond); }

public:
	inline void beginSynchronized() { m_pMutex->lock(); }
	inline void endSynchronized() { m_pMutex->unlock(); }

	inline void wait() { pthread_cond_wait(&m_cond, &(m_pMutex->m_mutex)); }
	inline void signal() { pthread_cond_signal(&m_cond); }
	inline void broadcast() { pthread_cond_broadcast(&m_cond); }

private:
	pthread_cond_t     m_cond;
	Mutex*             m_pMutex;

	// disable copy constructor and assignment
	ConditionVariable(const ConditionVariable&);
	ConditionVariable& operator = (const ConditionVariable&);
};

#endif

#endif
