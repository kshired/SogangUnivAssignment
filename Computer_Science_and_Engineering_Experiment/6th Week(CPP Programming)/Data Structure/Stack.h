#ifndef _STACK_H_
#define _STACK_H_
#include "LinkedList.h"

template <typename T>
class Stack:public LinkedList<T>{
public:
	bool Delete(T &element);
};
#include "Stack.cpp"
#endif
