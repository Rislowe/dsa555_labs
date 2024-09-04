/*******************************************************************/
/*                                                                 */
/*  A1 Part 2: SortedList starter file                             */
/*                                                                 */
/*  version 1.1: fixed class declaration to include merge          */
/*                                                                 */
/*  Author1 Name: Royston Ng                                       */
/*                                                                 */
/*******************************************************************/


template <typename T>

class SortedList{
	struct Node{

		//Node Constructor: Creates a new node that binds the passed T data object, and two Node pointers
		Node(const T& data=T{},Node* nx=nullptr,Node* pr=nullptr){ //pointers nx and pr are set to nullptr by default
			this->data = data;
			this->next = nx;
			this->prev = pr;
			
		}
		//Let the node have 3 private data members T data, Node* next, and Node* prev
		T data;
		Node* next;
		Node* prev;
	};
	Node* front;
	Node* back;

public:
	class const_iterator{
		friend class SortedList;
	protected:
		//let the node address currently being held by the iterator be current
		//let the address of the current Node's list be theList
		Node* current;
		const SortedList* theList;

		//This constructor creates a new const_iterator by accepting 2 pointers and assigning the Node* to current
		//and the list pointer to theList
		const_iterator(Node* n, const SortedList* list)
		{
			current = n;
			theList = list;
		}
	public:

		//This constructor creates an empty const_iterator
		const_iterator(){
			current = nullptr;
			theList = nullptr;
		}

		//Prefix ++ operator
		const_iterator& operator++(){
			current = current->next;		//set the current node to the next node
			return *this;					//return the current const_iterator
		}

		//postfix ++ operator
		const_iterator operator++(int){
			const_iterator old = *this;		//create a new const_iterator called old that is a copy of the current iterator
			current = current->next;		//reassign current to the next node
			return old;						//return the copy of the old const_iterator
		}

		//prefix -- operator
		const_iterator& operator--(){

			if (current)						//if the current node is not a nullptr
			{
				current = current->prev;		//set the current node to the previous node
			}
			else
			{
				if (theList != nullptr)			//if the list not pointing to a nullptr
				{
					current = theList->back;	//set the current node to the back of the list
				}
			}
			return *this;						//return the current iterator
		}

		//postfix -- operator
		const_iterator operator--(int){
			const_iterator old = *this;			//let const_iterator old to the current const_iterator
			if (current)						//if the current node is not a nullptr
			{
				current = current->prev;		
			}
			else
			{
				if (theList != nullptr)			//if the current list is not empty
				{
					current = theList->back;	
				}
			}
			return old;							//return the old const_iterator
		}

		//Compares iterators to see if they point to the same node
		//This function passes a const_iterator rhs which is the const_iterator to be compared
		bool operator==(const_iterator rhs){
			if (current != nullptr)												//if the current node is not a nullptr
			{
				return current == rhs.current;									//return true if the current node address is equal to the node address held by the other const_iterator
																				//or return false
			}
			else
			{
				return theList == rhs.theList && current == rhs.current;		//return the result of comparing the list addresses and the node addresses
																				//only return true if both list addresses and both node addresses are the same
			}
		}

		//Compares iterators to see if they do not point to the same node
		//let rhs be the const_iterator being compared to the current const_iterator
		bool operator!=(const_iterator rhs){
			if (current != nullptr)												//if the current node address is not a nullptr
			{
				return current != rhs.current;									//return the result of comparing the node addresses held by the const_iterators
																				//return true if they are different, return false if they match
			}
			else
			{
				return theList != rhs.theList || current != rhs.current;		//return the result of comparing the list addresses and the node addresses
																				//only return true if both list addresses and both node addresses are different
			}
		}

		//Returns readable copy of Node pointer
		const T& operator*()const{
			return current->data;		//returns the data stored in the current node
		}
	};
	class iterator:public const_iterator{
		friend class SortedList;
		iterator(Node* n, SortedList* list): const_iterator(n, list){}
	public:
		iterator():const_iterator(){}	//creates an empty iterator
		
		//this function increments the iterator before returning the result
		iterator& operator++(){
			if (this->current->next == nullptr)
			{
				this->current = nullptr;
			}
			else
			{
				this->current = this->current->next;
			}
			return *this;
		}

		//This function creates a copy of the current iterator, before incrementing the current iterator, and returns the copy.
		iterator operator++(int){
			iterator old = *this;
			if (this->current->next == nullptr)
			{
				this->current = nullptr;
			}
			else
			{
				this->current = this->current->next;
			}
			return old;		//returns old iterator
		}

		//This function decrements the iterator and returns a reference to the result.
		//same as const_iterator function
		iterator& operator--(){
			if (this->current)
			{
				this->current = this->current->prev;
			}
			else
			{
				if (this->theList != nullptr)
				{
					this->current = this->theList->back;
				}
			}

			return *this;
		}

		//postfix operator
		//same as const_iterator function
		iterator operator--(int){
			iterator old = *this;
			if (this->current)
			{
				this->current = this->current->prev;
			}
			else
			{
				if (this->theList != nullptr)
				{
					this->current = this->theList->back;
				}
			}
			return old;
		}

		//This function returns an editable reference to the data stored in the current node
		T& operator*(){
			return this->current->data;
		}

		//This function returns a non-editable reference to the data stored in the current node
		const T& operator*()const{
			return this->current->data;
		}
	};
	SortedList();
	~SortedList();
	SortedList(const SortedList& rhs);
	SortedList& operator=(const SortedList& rhs);
	SortedList(SortedList&& rhs);
	SortedList& operator=(SortedList&& rhs);

	//returns an iterator to the front of the list
	iterator begin(){
		return iterator(front, this);
	}

	//this function returns an iterator pointing to the node after the end of the list
	iterator end(){
		return iterator(nullptr, this);		//current node is assigned to a nullptr
	}

	//const_iterator version of begin()
	const_iterator cbegin() const{
		return const_iterator(front, this);
	}

	//const_iterator version of end()
	const_iterator cend() const{
		return const_iterator(nullptr, this);
	}

	iterator insert(const T& data);
	iterator search(const T& data);
	const_iterator search(const T& data) const;
	iterator erase(iterator it);
	void merge(SortedList& other);
	bool empty() const;
	int size() const;
};

//This constructor creates an empty list
template <typename T>
SortedList<T>::SortedList(){
	front = nullptr;			//set the pointer to the front of the list to a nullptr
	back = nullptr;				//set the pointer to the back of the list as nullptr
}

//destroys sorted list object
template <typename T>
SortedList<T>::~SortedList(){
	iterator it = this->begin();	//create a new iterator pointing to the beginning of the list
	Node* holder = it.current;		//let holder be a pointer to the current node


	while (it!=this->end())		//while the current iterator is not pointing to the end of the list
	{
		++it;					
		delete holder;		
		holder = it.current;
	}
	//both front and back pointers are set to nullptr
	front = nullptr;
	back = nullptr;
}
template <typename T>
SortedList<T>::SortedList(const SortedList& rhs){
	//create a constant iterator for the right hand side
	Node* right = rhs.front;

	//let main keep track of the position in the main list
	Node* main = nullptr;

	//let holder be an empty node address
	Node* holder = nullptr;

	if (right == nullptr) //if list is empty
	{
		//set the front and back pointers to nullptr
		front = nullptr;
		back = nullptr;
	}
	else
	{

		while (right != nullptr)							//While the right list has not ended
		{
			if (main == nullptr)                              //If the current list is empty
			{
				holder = new Node(right->data, nullptr, nullptr);		
				front = holder;					
				main = holder;
			}
			else
			{
				holder = new Node(right->data);
				holder->prev = main;
				holder->prev->next = holder;
				main = holder;
			}
			if (right->next == nullptr)
			{
				right = nullptr;
			}
			else
			{
				right = right->next;
			}
		}
		back = main;	//when copy of all nodes is complete, set address of the back of the list to last
	}

}
template <typename T>
SortedList<T>& SortedList<T>::operator=(const SortedList& rhs){

	if (this != &rhs)		//Checks if the lists are the same
	{
		if (!this->empty())						//If the list is not empty
		{
			iterator it = this->begin();		//create a new iterator pointing to the beginnning of the list
			Node* holder = it.current;			//let holder be the address of the current node held by the iterator

			//while the current pointer is pointing to a null pointer
			while (it != this->end())		//while the iterator does not point to the end of the list
			{
				++it;						
				delete holder;				
				holder = it.current;	
			}
			//both front and back pointers are set to nullptr
			front = nullptr;
			back = nullptr;
		}

		if (rhs.front == nullptr) //if list is empty
		{
			//set the front and back pointers to nullptr
			front = nullptr;
			back = nullptr;
		}
		else
		{
			//create a constant iterator for the right hand side
			const_iterator right = rhs.cbegin();

			//let main keep track of the position in the main list
			iterator main = this->begin();

			//let holder point to an empty node address
			Node* holder = nullptr;		

			while (right != rhs.cend())		//While the right list has not ended
			{
				if (this->empty())		//if the list is not empty
				{
					holder = new Node(right.current->data);		//let holder point to a new node with the right iterator's current data
					this->front = holder;						//set the front of the list to holder
					main.current = holder;						//set the main iterator's held node to holder
				}
				else
				{
					holder = new Node(right.current->data, nullptr, main.current);	//let holder point to a new node that holds the data of the
																					//right hand side and whose prev pointer points to the node before
																					//the main iterator's held node
					main.current->next = holder;									
					main.current = holder;											
				}
				right++;	
			}
			back = main.current;	//when copy of all nodes is complete, set address of the back of the list to last
		}

	}

	return *this;	//return the current iterator
}

//Move Constructor. Let this function move the data from one SortedList object to another
//let rhs be the rvalue reference of a different SortedList object
template <typename T>
SortedList<T>::SortedList(SortedList&& rhs){
	front = rhs.front;		//set the front of the current list to point to the front of the rhs list
	back = rhs.back;		//set the back of the current list point to the back of the rhs list

	//empty the rhs list
	rhs.front = nullptr;
	rhs.back = nullptr;
}

//This function overloads the assignment operator
//let rhs be the sorted list on the right hand side
template <typename T>
SortedList<T>& SortedList<T>::operator=(SortedList&& rhs){
	if (this != &rhs)					//if the lists are not the same
	{

		Node* holder = front;			//let holder be a node pointer to aid in swapping information

		//set the front and back of the main list to the front and back of the rhs list
		front = rhs.front;
		rhs.front = holder;
		holder = back;
		back = rhs.back;
		rhs.back = holder;
	}
	return *this;		//return a reference to the current list
}


//This function inserts a new node containing the passed "data" argument and returns the iterator to that node
template <typename T>
typename SortedList<T>::iterator SortedList<T>::insert(const T& data){
	bool inserted = false;				//let inserted be the false if the data has not been inserted or true if otherwise
	Node* nn = new Node(data);			//let nn be a new node with the passed data
	iterator loc = this->begin();		//let loc be the iterator pointing to the beginning of the list

	if (this->front == nullptr)		//if the current list is not empty
	{
		//set front and back to nn and set loc to the beginning of the list
		front = nn;
		back = nn;
		loc = this->begin();

		return loc;		//return the loc iterator
	}
	else
	{
		while (inserted == false)		//while the node has not been inserted
		{
			if (loc == this->end())		//if loc is equal to the end of the list
			{
				back->next = nn;		
				nn->prev = back;		
				back = nn;				
				loc.current = nn;		

				inserted = true;		
			}
			else if (loc.current == this->front && nn->data < loc.current->data)	//if the front of the list is equal to the node held by loc
																					//and if the data in nn is less than the data in loc's current node
			{

				loc.current->prev = nn;		
				nn->next = loc.current;		
				this->front = nn;			

				loc.current = nn;			
				inserted = true;			//The node has been properly inserted

			}
			else if (loc.current->data < nn->data)	//if the data at the current location is less than the data in nn
			{
				loc++;
				inserted = false;
			}
			else if (loc.current->data == nn->data)	//if the data at the current location is equall to the data in nn
			{
				loc++;
				inserted = false;
			}
			else if (nn->data < loc.current->data)	//if the data in nn is less than the data in the current location
			{
				nn->next = loc.current;
				nn->prev = loc.current->prev;
				loc.current->prev->next = nn;
				loc.current->prev = nn;

				loc.current = nn;
				inserted = true;
			}
			else
			{
				loc++;
				inserted = false;
			}
		}

		return loc;		//return the location of the inserted node
	}
	

	
}


//This function looks through the the entire list and return the iterator to a node that matches the passed data
//let data be the piece of information we are searching for in the list
//returned iterator can point to the end() of the list
//Node in the iterator can then be edited
template <typename T>
typename SortedList<T>::iterator SortedList<T>::search(const T& data){
	bool found = false;				//let found be the status of whether the data has been found in the list
	iterator it = this->begin();	//let it be an iterator pointing to the beginning of the list
									//iterator iterates through the entire list looking for matching data

	while (it != this->end() && found == false)
	{
		if (it.current->data == data)
			found = true;
		else
		{
			it++;
		}
			
	}
	return it;
}

//This function returns a const_iterator to the location of a node containing data that is the same as the passed data
//returned const_iterator is read-only
template <typename T>
typename SortedList<T>::const_iterator SortedList<T>::search(const T& data) const{
	bool found = false;						//let found be the status of whether the data has been found in the list
	const_iterator it = this->cbegin();		//let it be a const_iterator pointing to the beginning of the list
											//it iterates through the entire list looking for matching data

	while (it != this->cend() && found == false)
	{
		if (it.current->data == data)
			found = true;
		else
		{
			it++;
		}

	}

	return it;
}


//This function removes a node from the list
//The parts of the list before and after the removed node should be joined together after removal
template <typename T>
typename SortedList<T>::iterator SortedList<T>::erase(iterator it){
	Node* holder = nullptr;		//holder will be the pointer to the node that should be removed. set to nullptr by default.

	if (it.current != nullptr)
	{
		if (it.current == this->front && it.current == this->back)
		{
			delete it.current;
			it.current = nullptr;
		}
		else if (it.current == it.theList->front)
		{
			this->front = it.current->next;
			this->front->prev = nullptr;
			delete it.current;
			it.current = this->front;

		}
		else if (it.current == it.theList->back)
		{
			this->back = it.current->prev;
			this->back->next = nullptr;
			delete it.current;
			it.current = nullptr;
		}
		else
		{
			holder = it.current->next;
			holder->prev = it.current->prev;
			it.current->prev->next = holder;
			delete it.current;
			it.current = holder;
		}
	}
	
	return it;
}


//This function merges two SortedList objects into a single sortedList object
//this function accepts a SortedList object named other
//this function does not return a value but the current/main list will be permanently changed
template <typename T>
void SortedList<T>::merge(SortedList& other){
	iterator mainIt = this->begin();	//the main iterator is the current location in the main list	//this->begin == 1 + 3; 1 + 1+3 = 5
	iterator otherIt = other.begin();	//this is the iterator for the passed list						// 1 + 1 + 3 = 5

	Node* holder = nullptr;		//holder holds the address of the node to be inserted into the list		// 1

	while (otherIt != other.end())																		//other.end = 1+3 = 4; 1+1+3 = 5; while = n; 5n
	{
		if (mainIt == this->end())																		// If mainIt ends before otherIt 4n
		{
			if (this->empty())																				//3
			{
				front = other.front;                                                                       //1
				back = other.back;                                                                         //1
				otherIt = other.end();                                                                     //4
			}
			else
			{
				otherIt.current->prev = this->back;															//4
				this->back->next = otherIt.current;															//4
				this->back = other.back;																	//3
				otherIt = other.end();                                                                      //3
			}
		}
		else if (otherIt.current->data < this->front->data)												//if current data is less than front data otherIt = n; 5n
		{
			holder = otherIt.current;																	//2
			++otherIt;																					//1
			this->front->prev = holder;																	//3
			holder->next = this->front;																	//3
			this->front = holder;																		//2
		}
		else
		{
			if (otherIt.current->data < mainIt.current->data)											//5n
			{
				holder = otherIt.current;																//2n
				++otherIt;																				//n
				holder->next = mainIt.current;															//3n
				holder->prev = mainIt.current->prev;													//4n
				holder->next->prev = holder;															//3n
				holder->prev->next = holder;															//3n
			}
			else if (otherIt.current->data == mainIt.current->data)										//5n
			{
				mainIt++;																				//n
			}
			else if (mainIt.current->data < otherIt.current->data)										//5n
			{
				mainIt++;																				//n
			}
			
		}
		
	}
	other.front = nullptr;	//1
	other.back = nullptr;	//1
}

//analysis

//T(n) = 5+5+1+4+4+3+3+2+1+3+3+2+5n+4n+5n+5n+2n+1n+3n+4n+3n+3n+5n+n+5n+n
//	   = 52n+36
//T(n) = O(n)


//This function returns true if the list is empty
template <typename T>
bool SortedList<T>::empty() const{
	if (front == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//This function counts the number of nodes in the list, and returns the number of nodes
template <typename T>
int SortedList<T>::size() const{
	int count = 0;		//count is number of nodes in the list
	const_iterator it = this->cbegin();

	while (it != this->cend())
	{
		++count;
		it++;
	}

	return count;
}
