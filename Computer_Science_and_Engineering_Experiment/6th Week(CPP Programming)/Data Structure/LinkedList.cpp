#include <iostream>
template <typename T>
void LinkedList<T>::Insert(T element){
	Node<T> *newnode = new Node<T>(element);
	newnode->link = first;
	first = newnode;
	current_size++;
}
template <typename T>
bool LinkedList<T>::Delete(T &element){
	if(first == 0)
		return false;
	Node<T> *current = first,*previous = 0;
	while(1){
		if(current->link == 0){
			if(previous)
				previous->link = current->link;
			else first = first->link;
			break;
		}
		previous = current;
		current = current->link;
	}
	element = current->data;
	delete current;
	current_size--;
	return true;
}
template <typename T>
void LinkedList<T>::Print(){
	Node<T> *cur = first;
	if(current_size==0) return;
	for(int i=1;;i++){
		std::cout<<"[ "<<i;
		std::cout<<"|"<<cur->data;
		std::cout<<"]";
		if(i==current_size) break;
		std::cout<<" -> ";
		cur = cur->link;
	}
	std::cout<<std::endl;
}
