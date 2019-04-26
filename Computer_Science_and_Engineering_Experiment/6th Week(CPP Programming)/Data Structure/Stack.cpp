#include <iostream>
template <typename T>
bool Stack<T>::Delete(T &element){
	if(this->first==0) return false;
	
	Node<T> *cur = this->first;
	element = cur->data;
	this->first = this->first->link;
	delete cur;
	this->current_size--;

	return true;
}
