#ifndef ARRAY_H_
#define ARRAY_H_
template <typename T>
class Array{
protected:
    T *data;
    int len;
public:
	Array(){}; 
    Array(int size);
    ~Array();
    int length();
    virtual T& operator[](int i);
    virtual T operator[](int i) const;
    void print();
};
#include "Array.cpp"
#endif
