#include "CoreStd.h"
#include "Thread.h"

#if PLATFORM == PLATFORM_WINDOWS
void Thread::join()
{
	if (m_handle)
	{
		WaitForSingleObject(m_handle, INFINITE);
	}
}

void Thread::detach()
{
	if (m_handle)
	{
		HANDLE tmp = m_handle;
		m_handle = 0;
		CloseHandle(tmp);
	}
}

void Thread::Sleep(uint ms)
{
	::Sleep(ms);
}

ulong Thread::GetCurrentThreadId()
{
	return ::GetCurrentThreadId();
}

#else
void Thread::join()
{
	int expect = 0;
	if (m_threadClosed.compare_exchange_strong(expect, 1))
	{
		if (m_handle)
		{
			pthread_t tmp = m_handle;
			m_handle = 0;
			pthread_join(tmp, NULL);
		}
	}
}

void Thread::detach()
{
	int expect = 0;
	if (m_threadClosed.compare_exchange_strong(expect, 1))
	{
		if (m_handle)
		{
			pthread_t tmp = m_handle;
			m_handle = 0;
			pthread_detach(tmp);
		}
	}
}

void Thread::Sleep(uint ms)
{
	struct timespec t;
	t.tv_sec = ms / 1000;
	t.tv_nsec = (ms % 1000) * 1000000;
	nanosleep(&t, NULL);
}

ulong Thread::GetCurrentThreadId()
{
	return (ulong)pthread_self();
}


#endif
