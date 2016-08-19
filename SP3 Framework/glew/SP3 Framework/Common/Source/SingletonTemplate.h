#ifndef SINGLETON_H
#define SINGLETON_H

template <class Type>
class Singleton {

protected:
	//Constructor(s) & Destructor
	Singleton() {}
	virtual ~Singleton() {}

public:
	static Type& GetInstance() {
		static Type instance;

		return instance;
	}

};

#endif