#ifndef __BLADE_THREAD_H__
#define __BLADE_THREAD_H__

#if BLADE_PLATFORM == BLADE_PLATFORM_WINDOWS
#include<Windows.h>
#else
#include<pthread.h>
#endif

BLADE_NAMESPACE_BEGIN

enum ThreadState
{
	THREADSTATE_NEW,
	THREADSTATE_RUNNABLE,
	THREADSTATE_RUNNING,
	THREADSTATE_BLOCKED = 2,
	THREADSTATE_TERMINATE = 3,
	THREADSTATE_DEAD = 4
};

class Runnable
{
	virtual bool       run() = 0;
};

class Thread
{
public:
	Thread();
	Thread(Runnable* target);
	Thread(const std::string& name);
	Thread(Runnable* target, const std::string& name);
	virtual ~Thread() {}

public:
	inline void               setName(const std::string& name) { m_name = name; }
	inline const std::string& getName() const { return m_name; }
	inline void               setThreadState(ThreadState state) { m_threadState = state; }
	inline ThreadState        getThreadState() { return m_threadState; }
	inline bool               isTerminated() { return m_threadState == THREADSTATE_TERMINATE; }

	virtual bool              shutdownThread()
	{
		if (m_threadState < THREADSTATE_TERMINATE)
		{
			m_threadState = THREADSTATE_TERMINATE;
			return true;
		}
		return false;
	}

	virtual bool       run() = 0;

	void               join();
	void               detach();

#if defined(_WIN32)
	inline HANDLE      getNativeHandle() const { return m_handle; }
#else
	inline pthread_t   getNativeHandle() const { return m_handle; }
#endif

	static long        nextThreadID();
	static void        yield();
	static void        sleep(uint ms);
	static ulong       getCurrentThreadId();

private:
	void               init(Runnable* target, const std::string& name);

protected:
	std::string              m_name;
	Runnable*                m_target;
	std::atomic<ThreadState> m_threadState;
	std::atomic<int>         m_threadClosed;

#if defined(_WIN32)
	HANDLE                   m_handle;
#else
	pthread_t                m_handle;
#endif
};

BLADE_NAMESPACE_END

#endif