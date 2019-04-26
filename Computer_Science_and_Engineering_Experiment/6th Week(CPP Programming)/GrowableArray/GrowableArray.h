#ifndef _GROWABLE_ARRAY_H_
#define _GROWABLE_ARRAY_H_
#include "Array.h"
template <typename T>
class GrowableArray:public Array<T>{
public:
	GrowableArray(int size);
	virtual T& operator[](int i);
};
#include "GrowableArray.cpp"
#endif
