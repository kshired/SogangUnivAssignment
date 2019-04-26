// 2018.10.13 20171612 - Sungil Kim
// RangeArray.h
#ifndef RANGE_ARRAY_H_
#define RANGE_ARRAY_H_
#include "Array.h" // For inheritance, include "Array.h"
class RangeArray : public Array{
protected:
    int low; //low == baseVal
    int high; // high == endVal
public:
    RangeArray(int, int); // RangeArray initialize using length(baseValue and endValue)
    ~RangeArray(); // delete RangeArray
    int baseValue(); // Return Low
    int endValue(); // Return High
    int& operator[](int); // For Assigning value
    int operator[](int) const; // Return Value
};
#endif