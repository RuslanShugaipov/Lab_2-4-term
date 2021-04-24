#include "LinkedList.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <iomanip>

using namespace std;

template<class NODE_TYPE>
LinkedList<NODE_TYPE>::LinkedList()//Constructor
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

template<class NODE_TYPE>
LinkedList<NODE_TYPE>::~LinkedList()//Destructor
{
	clear();
}

template<class NODE_TYPE>
void LinkedList<NODE_TYPE>::push_back(NODE_TYPE newEl)//Adding to the end of the list
{
	Node* temp;
	if (size == 0)
	{
		head = new Node(newEl);
		tail = head;
	}
	else
	{
		temp = tail;
		tail->next = new Node(newEl);
		tail = tail->next;
		tail->prev = temp;
	}
	size++;
}

template<class NODE_TYPE>
void LinkedList<NODE_TYPE>::push_front(NODE_TYPE newEl)//Adding to the beginning of the list
{
	Node* temp;
	if (size == 0)
	{
		head = new Node(newEl);
		tail = head;
	}
	else
	{
		temp = head;
		head = new Node(newEl, head);
		temp->prev = head;
	}
	size++;
}

template<class NODE_TYPE>
void LinkedList<NODE_TYPE>::pop_back()//Remove the last element
{
	if (size == 0)
		return;
	if (size == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		Node* cur = tail;
		cur = cur->prev;
		cur->next = nullptr;
		delete tail;
		tail = cur;
		cur->prev = tail->prev;
	}
	size--;
}

template<class NODE_TYPE>
void LinkedList<NODE_TYPE>::pop_front()//Remove the first element
{
	if (size == 0)
		return;
	if (size == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		Node* cur = head;
		cur = cur->next;
		cur->prev = nullptr;
		delete head;
		head = cur;
	}
	size--;
}

template<class NODE_TYPE>
void LinkedList<NODE_TYPE>::insert(NODE_TYPE newEl, size_t index)//Adding element by index
{
	Node* temp_pointer = nullptr, * cur;
	Node* temp = new Node(newEl);
	cur = head;
	int i = 0;
	if (index >= size || index < 0)
		throw out_of_range("Index is greater than list size");
	while (cur != NULL && i<int(index))
	{
		cur = cur->next;
		i++;
	}
	if (cur == NULL)
	{
		if (head == NULL)
		{
			cout << "List is empty\n";
			return;
		}
		return;
	}
	if (cur != head)
	{
		temp_pointer = cur->prev;
		cur->prev = temp;
		temp->next = cur;
		temp->prev = temp_pointer;
	}
	else
		push_front(newEl);
	if (temp_pointer != NULL)
		temp_pointer->next = temp;
	size++;
}

template<class NODE_TYPE>
int LinkedList<NODE_TYPE>::at(size_t index) const//Getting an item by index
{
	if (size == 0)
		cout << "List is empty\n";
	if (index >= size || index < 0) {
		throw out_of_range("Index is greater than list size");
	}
	if ((index < size) && (size != 0))
	{
		size_t counter = 0;
		Node* cur = head;
		while (counter != index)
		{
			cur = cur->next;
			counter++;
		}
		return cur->data;
	}
}

template<class NODE_TYPE>
void LinkedList<NODE_TYPE>::remove(size_t index)//Deleting an element by index
{
	size_t counter = 0;
	Node* cur = head;
	if (index >= size || index < 0)
		throw out_of_range("Index is greater than list size");
	while (counter != index)
	{
		cur = cur->next;
		counter++;
	}
	if (cur == head)
	{
		pop_front();
		return;
	}
	if (cur == tail)
	{
		pop_back();
		return;
	}
	Node* prev, * next;
	prev = cur->prev;
	next = cur->next;
	if (prev != NULL)
		prev->next = cur->next;
	if (next != NULL)
		next->prev = cur->prev;
	delete cur;
	size--;
}

template<class NODE_TYPE>
size_t LinkedList<NODE_TYPE>::get_size()//Getting list size
{
	return size;
}

template<class NODE_TYPE>
void LinkedList<NODE_TYPE>::print_to_console()//Printing list elements to console
{
	Node* cur = head;
	cout << "List elements:\t";
	while (cur != nullptr)
	{
		cout <<setw(3)<< cur->data <<' ';
		cur = cur->next;
	}
	cout << '\n';
}

template<class NODE_TYPE>
void LinkedList<NODE_TYPE>::clear()//Removing all list elements
{
	while (head)
	{
		tail = head->next;
		delete head;
		head = tail;
		size--;
	}
}

template<class NODE_TYPE>
void LinkedList<NODE_TYPE>::set(size_t index, NODE_TYPE newData)//Replacing the element by index with the passed element
{
	Node* cur = head;
	if (index >= size || index < 0)
		throw out_of_range("Index is greater than list size");
	size_t counter = 1;
	while (counter <= index)
	{
		counter++;
		cur = cur->next;
	}
	cout << "Element " << cur->data;
	cur->data = newData;
	cout << " replaced by " << cur->data << '\n';
}

template<class NODE_TYPE>
bool LinkedList<NODE_TYPE>::isEmpty()//Checking if the list is empty
{
	if (head != NULL)
		return true;
	else
		return false;
}

template<class NODE_TYPE>
inline void LinkedList<NODE_TYPE>::sort()
{
	Node* cur = head;
	while (cur->next)
	{
		if ((cur->data) < (cur->next->data))
		{
			NODE_TYPE temp = cur->next->data;
			cur->next->data = cur->data;
			cur->data = temp;
			cur = cur->next;
			sort();
		}
		else
		{
			cur = cur->next;
		}
	}
}

template<class NODE_TYPE>
bool LinkedList<NODE_TYPE>::isPrinted()//Is the list printed
{
	Node* cur = head;
	while (cur != nullptr)
	{
		cout << cur->data << ' ';
		cur = cur->next;
	}
	cout << '\n';
	if (cur == nullptr)
		return true;
	else
		return false;
}

template<class NODE_TYPE>
size_t LinkedList<NODE_TYPE>::find_first(LinkedList* list)//Finding the first occurrence of another list in the list
{
	int counter = 0;
	Node* curL1, * curL2;
	curL1 = (*list).head;
	curL2 = head;
	if (curL1 == nullptr || curL2 == nullptr)
		return 0;
	if ((*list).get_size() > size)
	{
		while (curL2->data != curL1->data && curL1->next != NULL)
		{
			curL1 = curL1->next;
			counter++;
		}
		while (curL2->data == curL1->data && curL2->next != NULL && curL1->next != NULL)
		{
			curL2 = curL2->next;
			curL1 = curL1->next;
		}
		if (curL2->next == NULL)
		{
			return counter;
		}
		else
			return 0;
	}
	else
	{
		if ((*list).get_size() == size)
			if (curL1->data == curL2->data)
				goto analysis;
			else
				return 0;
		while (curL1->data != curL2->data && curL2->next != NULL)
		{
			curL2 = curL2->next;
			counter++;
		}
	analysis:
		while (curL1->data == curL2->data && curL1->next != NULL && curL2->next != NULL)
		{
			curL1 = curL1->next;
			curL2 = curL2->next;
		}
		if (curL1->next == NULL)
		{
			return counter;
		}
		else
			return 0;
	}
}