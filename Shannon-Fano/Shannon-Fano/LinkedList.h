#pragma once

template<class NODE_TYPE> 
class LinkedList
{
public:
	//Constructor and Destructor
	LinkedList();
	~LinkedList();
	//Methods for working with Linked List
	void push_back(NODE_TYPE newEl);
	void push_front(NODE_TYPE newEl);
	void pop_back();
	void pop_front();
	void insert(NODE_TYPE newEl, size_t index);
	int at(size_t index) const;
	void remove(size_t index);
	size_t get_size();
	void print_to_console();
	void clear();
	void set(size_t index, NODE_TYPE newData);
	bool isEmpty();
	void sort();
	size_t find_first(LinkedList *list);

	bool isPrinted();

private:
	class Node
	{
		public:
			Node(NODE_TYPE data, Node* next = nullptr, Node* prev = nullptr)
			{
				this->data = data;
				this->next = next;
				this->prev = prev;
			}
			NODE_TYPE data;
			Node* next;
			Node* prev;
	};
	
	Node* head;
	Node* tail;
	size_t size;
};

#include "LinkedList.inl"