#include <iostream>
template <typename T>
Array<T>::Array(int size){
    if(size<=0){
        std::cout<<"Size Must Be Positive\n";
    }else{
        this->len = size;
        this->data = new int[this->len];
    }
}
template <typename T>
Array<T>::~Array(){
    delete [] this->data;
}
template <typename T>
int Array<T>::length(){
    return this->len;
}
template <typename T>
T& Array<T>::operator[](int i){
    static T tmp;
    if(i>=0 && i < this->len) {
		return (this->data)[i];
	}
	else {
		std::cout << "Array bound error!\n";
	}
    return tmp;
}
template <typename T>
T Array<T>::operator[](int i) const{
    if(i>=0 && i<=this->len){
        return (this->data)[i];
    }else{
        std::cout<<"Invalid Size\n";
    }
    return -1;
}
template <typename T>
void Array<T>::print(){
    std::cout<<"[ ";
    for(int i=0;i<this->len;i++){
        std::cout<<(this->data)[i]<<" ";
    }
    std::cout<<"]\n";
}
