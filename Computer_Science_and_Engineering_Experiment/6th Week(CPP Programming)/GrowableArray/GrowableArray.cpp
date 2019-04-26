#include <iostream>
template <typename T>
GrowableArray<T>::GrowableArray(int size){
	if(size<=0){
		std::cout<<"Size Must Be Positive\n";
	}else{
		this->len = size;
		this->data = new T[this->len];
	}

}
template <typename T>
T& GrowableArray<T>::operator[](int i){
	static T tmp;
	T *nGA; 
	if(i>=0 && i< this->len){
		return (this->data)[i];
	}else if(i>=this->len){
		int tmp = this->len;
		while(this->len<=i){
			this->len *= 2;
		}
		nGA = new T[this->len];
		for(int j=0;j<tmp;j++){
			nGA[j] = (this->data)[j];
		}
		for(int j=tmp;j<this->len;j++){
			nGA[j] = 0;
		}
		T *t = this->data;
		this->data = nGA;
		delete[] t;
		return (this->data)[i];
	}else{
		std::cout<<"GrowableArray Bound Error"<<std::endl;
		return tmp;
	}
}
