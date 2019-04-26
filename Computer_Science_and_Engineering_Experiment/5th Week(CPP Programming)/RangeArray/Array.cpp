// 2018.10.13 20171612 - Sungil Kim
// Array.cpp
// Define Function in Array.h
#include "Array.h"
#include <iostream>
// "using namespace std" can be danger.
// So, I'll use std::cout, std::endl
Array::Array(int size){
    if(size<=0){
        std::cout<<"Size Must Be Positive\n";
    }else{
        this->len = size;
        this->data = new int[this->len];
    }
}
Array::~Array(){
    delete [] this->data;
}
int Array::length(){
    return this->len;
}
int& Array::operator[](int i){
    static int tmp;
    if(i>=0 && i < len) {
		return (this->data)[i];
	}
	else {
		std::cout << "Array bound error!\n";
	}
    return tmp;
}
int Array::operator[](int i) const{
    if(i>=0 && i<=this->len){
        return (this->data)[i];
    }else{
        std::cout<<"Invalid Size\n";
    }
    return -1;
}
void Array::print(){
    std::cout<<"[ ";
    for(int i=0;i<this->len;i++){
        std::cout<<(this->data)[i]<<" ";
    }
    std::cout<<"]\n";
}
