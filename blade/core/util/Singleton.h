#ifndef __BLADE_SINGLETON_H__
#define __BLADE_SINGLETON_H__

BLADE_NAMESPACE_BEGIN

template<class T>
class Singleton
{
public:
	Singleton()
	{
		ms_pSingleton = static_cast<T*>(this);
	}

	~Singleton()
	{
		ms_pSingleton = NULL;
	}

private:
	/** \brief Explicit private copy constructor. This is a forbidden operation.*/
	Singleton(const Singleton<T>&);

	/** \brief Private operator= . This is a forbidden operation. */
	Singleton& operator = (const Singleton<T>&);

public:
	inline static T* Instance()
	{
		return ms_pSingleton;
	}

protected:
	static T	*ms_pSingleton;
};

template<class T>
T* Singleton<T>::ms_pSingleton = NULL;

BLADE_NAMESPACE_END

#endif
