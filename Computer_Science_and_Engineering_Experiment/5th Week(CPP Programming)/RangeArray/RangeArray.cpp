// 2018.10.13 20171612 - Sungil Kim
// RangeArray.cpp
// Define Function in RangeArray.h
#include "RangeArray.h"
#include <iostream>
// "using namespace std" can be danger.
// So, I'll use std::cout, std::endl
RangeArray::RangeArray(int baseValue, int endValue): Array(endValue-baseValue+1){
    this->low = baseValue;
    this->high = endValue;
}
RangeArray::~RangeArray(){
    // We generate array by Array Class.
    // So, doesn't have to Delete array in this Class
	// Array that has data will be delet in Array Class. Not in Range Array Class!
}
int RangeArray::baseValue(){
    return this->low;
}
int RangeArray::endValue(){
    return this->high;
}
int& RangeArray::operator[](int index){
    static int tmp;
    if(index>=(this->low) && (this->high)>=index) {
		return (this->data)[index-low];
	}
	else {
		std::cout << "Array bound error!\n";
	}
    return tmp;
}
int RangeArray::operator[](int index) const{
    if(index>=(this->low) && (this->high)>=index){
        return (this->data)[index-low];
    }else{
        std::cout<<"Invalid Size\n";
    }
    return -1;
}
