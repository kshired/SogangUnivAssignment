// 2018.10.13 20171612 - Sungil Kim
// Array.h
#ifndef ARRAY_H_
#define ARRAY_H_
class Array{
protected:
    int *data; // For saving data. raw array.
    int len; // length of array.
public:
    Array(int size); // Array initialize using length(=size)
    ~Array(); // delete data
    int length(); // return len
    int& operator[](int i); // For Assigning value 
    int operator[](int i) const; // Return Value
    void print(); // print Array
};
#endif