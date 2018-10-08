#ifndef __BLADE_MUTEX_H__
#define __BLADE_MUTEX_H__

#if BLADE_PLATFORM == BLADE_PLATFORM_WINDOWS
#include<Windows.h>
#else
#include<pthread.h>
#endif

BLADE_NAMESPACE_BEGIN

class ConditionVariable;

#if BLADE_PLATFORM == BLADE_PLATFORM_WINDOWS

class BLADE_CORE_API Mutex
{
public:
	Mutex() { InitializeCriticalSection(&m_criticalSection); }
	~Mutex() { DeleteCriticalSection(&m_criticalSection); }

public:
	inline void lock() { EnterCriticalSection(&m_criticalSection); }
	inline void unlock() { LeaveCriticalSection(&m_criticalSection); }
	inline bool tryLock() { return (TryEnterCriticalSection(&m_criticalSection) == TRUE); }

private:
	CRITICAL_SECTION m_criticalSection;
	friend class ConditionVariable;

	// disable copy constructor and assignment
	Mutex(const Mutex&);
	Mutex& operator = (const Mutex&);
};

#elif PLATFORM == PLATFORM_LINUX

class Mutex
{
public:
	Mutex() { pthread_mutex_init(&m_mutex, NULL); }
	~Mutex() { pthread_mutex_destroy(&m_mutex); }

public:
	inline void lock() { pthread_mutex_lock(&m_mutex); }
	inline void unlock() { pthread_mutex_unlock(&m_mutex); }
	inline bool tryLock() { return (pthread_mutex_trylock(&m_mutex) == 0); }

private:
	pthread_mutex_t m_mutex;

	// disable copy constructor and assignment
	Mutex(const Mutex&);
	Mutex& operator = (const Mutex&);
};

#endif

//////////////////////////////////////////////////////////////////////////

/** A lightweight mutex is a synchronization mechanism, very similar to a regular mutex.
Regular mutexes are well known to be expensive because they need to enter & leave
kernel mode.
@par
Lightweight mutexes usually make use of atomic instructions (in x86 they're referred to
as instructions with the "lock" prefix) to avoid entering kernel mode when no other
thread has acquired the lock.
@par
This comes with a couple caveats that we don't care for the applications we need,
but is important to keep them in mind:
1) LightweightMutexes can't be shared among processes
2) Priority inversion is not a concern
3) Recursive locks aren't supported (same thread calling lock() twice can deadlock)
Note that some LightweightMutex implementations may offer this functionality, but we don't
guarantee them in all platforms/architectures.
It is possible to write a lightweight mutex that supports recursive locks, but that requires
a call to GetCurrentThreadId (in Windows), which as much as saying just use a regular mutex.
@par
Windows users are familiar with the concept of LightweightMutexes because there is already
an implementation provided: CRITICAL_SECTION. We go further by reinventing the wheel and
writing it ourselves. If you ever wondered how a CRITICAL_SECTION works, now you know.
@par
Interesting reads:
http://preshing.com/20111124/always-use-a-lightweight-mutex
http://preshing.com/20120226/roll-your-own-lightweight-mutex
http://preshing.com/20120305/implementing-a-recursive-mutex
*/
class LightWeightMutex
{
public:
	LightWeightMutex();
	~LightWeightMutex();

public:
	void lock();
	void unlock();
	bool tryLock();

private:
#if PLATFORM == PLATFORM_WINDOWS
	long   m_counter;
	HANDLE m_semaphore;
#elif PLATFORM == PLATFORM_LINUX
	pthread_mutex_t m_mutex;
#endif
};

#endif