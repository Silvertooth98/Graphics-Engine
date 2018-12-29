#ifndef SINGLETON_H
#define SINGLETON_H

template <class T>
class Singleton
{

public:

	static T* Instance();

private:

	Singleton() {}
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

};

//------------------------------------------------------------------------------------------------------
//template function that will create an instance of any type and return its address
//------------------------------------------------------------------------------------------------------
template <class T> T* Singleton<T>::Instance()
{

	static T* singletonObject = new T();
	return singletonObject;

}

#endif