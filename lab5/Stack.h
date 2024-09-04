#include "lab4.h"
#include <string>

template<typename T>
class Stack
{
	Sentinel<T>* stackList;
public:
	Stack();
	~Stack();
	void push(T letter);
	void pop();
	T top();
	bool empty();
};

template <typename T>
Stack<T>::Stack()
{
	stackList = new Sentinel<T>();
}

template <typename T>
Stack<T>::~Stack()
{
	delete stackList;
}

template <typename T>
void Stack<T>::push(T letter)
{
	stackList->push_front(letter);
}

template <typename T>
void Stack<T>::pop()
{
	typename Sentinel<T>::iterator it = stackList->begin();
	if (it != stackList->end())
	{
		stackList->pop_front();
	}
}

template <typename T>
T Stack<T>::top()
{
	return *(stackList->begin());
}

template<typename T>
bool Stack<T>::empty()
{
	if (stackList->cbegin() == stackList->cend())
		return true;
	else
		return false;
}