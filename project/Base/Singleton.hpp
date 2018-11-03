#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template<typename T>
class Singleton
{
public:
	static T& instance()
	{
		static T t;
		return t;
	}
};


#endif