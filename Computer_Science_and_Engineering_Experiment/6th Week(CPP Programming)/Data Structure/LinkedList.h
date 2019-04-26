#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_
template <typename T>
class Node{
public:
	T data;
	Node *link;
	Node(T element){
		data = element;
		link = 0;
	}
};
// Linked List class
template <typename T>
class LinkedList{
protected:
	Node<T> *first;
	int current_size;
public:
	LinkedList(){
		first = 0;
		current_size = 0;
	};
	int GetSize() { return current_size; };
	void Insert(T element);
	virtual bool Delete(T &element);
	void Print();
};
#include "LinkedList.cpp"
#endif
