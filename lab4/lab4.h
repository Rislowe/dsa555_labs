#include <iostream>

template <typename T>
class DList{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	DList(){
		front_=nullptr;
		back_=nullptr;
	}
	void push_front(const T& data);
	~DList();

	class const_iterator{
		friend class DList;		//established friend class
	protected:
		Node* curr_;			//let the current node held in the iterator be curr_
		const DList* theList_;	//let the address of the list be stored in theList_

		//Constructor that sets the addresses of the current node and the current list
		const_iterator(Node* n, const DList* list){
			curr_=n;
			theList_ = list;
		}

	public:
		const_iterator(){
			curr_=nullptr;
			theList_ = nullptr;
		}
		//++it
		const_iterator operator++(){
			curr_ = curr_->next_;
			return *this;
		}

		//it++
		const_iterator operator++(int){
			const_iterator old = *this;
			curr_ = curr_->next_;
			return old;
		}

		//--it
		const_iterator operator--(){
			if (curr_)
			{
				curr_ = curr_->prev_;
			}
			else 
			{
				if (theList_ != nullptr)
				{
					curr_ = theList_->back_;
				}
			}
			
			return *this;
		}

		//it--
		const_iterator operator--(int){
			const_iterator old = *this;
			if (curr_)
			{
				curr_ = curr_->prev_;
			}
			else
			{
				if (theList_ != nullptr)
				{
					curr_ = theList_->back_;
				}
			}
			return old;
		}
		
		//this operator returns true if the operators are the same.
		bool operator==(const_iterator rhs){
			if (curr_ != nullptr)
			{
				return curr_ == rhs.curr_;
			}
			else
			{
				return theList_ == rhs.theList_ && curr_ == rhs.curr_;
			}
		}

		//this operator returns true if the address of the current node is not the same or if the
		//address of the current list is not the same as the values on the right hand side
		bool operator!=(const_iterator rhs){
			if (curr_ != nullptr)
			{
				return curr_ != rhs.curr_;
			}
			else
			{
				return theList_ != rhs.theList_ || curr_ != rhs.curr_;
			}
		}

		//This function returns the data from the node address stored in the iterator.
		const T& operator*()const{
			return curr_->data_;
		}
	};
	class iterator:public const_iterator{
		friend class DList;
		iterator(Node* n, DList* list): const_iterator(n, list){}
	public:
		iterator();
		iterator operator++(){
			this->curr_ = this->curr_->next_;
			return *this;
		}
		iterator operator++(int){
			iterator old = *this;
			this->curr_ = this->curr_->next_;
			return old;
		}
		iterator operator--(){
			if (this->curr_)
			{
				this->curr_ = this->curr_->prev;
			}
			else
			{
				if (this->theList_ != nullptr)
				{
					this->curr_ = this->theList_->back_;
				}
			}

			return *this;
		}
		iterator operator--(int){
			const_iterator old = *this;
			if (this->curr_)
			{
				this->curr_ = this->curr_->prev_;
			}
			else
			{
				if (this->theList_ != nullptr)
				{
					this->curr_ = this->theList_->back_;
				}
			}
			return old;
		}
		T& operator*(){
			return this->curr_->data_;
		}
		const T& operator*()const{
			return this->curr_->data_;
		}

	};
	const_iterator cbegin() const{
		return const_iterator(front_, this);
	}
	iterator begin(){
		return iterator(front_, this);
	}
	const_iterator cend() const{
		return const_iterator(nullptr, this);
	}
	iterator end(){
		return iterator(nullptr, this);
	}
};


template <typename T>
void DList<T>::push_front(const T& data){
	Node* nn = new Node(data, front_);
	if (front_ != nullptr) {
		front_->prev_ = nn;
	}
	else {
		back_ = nn;
	}
	front_ = nn;
}


template <typename T>
DList<T>::~DList(){
	while (front_ != nullptr)
	{
		back_ = back_->prev_;
		delete back_->next_;
		back_->next_ = nullptr;
		
		if (back_ == front_)
		{
			back_ = nullptr;
			delete front_;
			front_ = nullptr;
		}
	}
}

template <typename T>
class Sentinel{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	Sentinel(){
		front_=new Node();
		back_=new Node();
		front_->next_=back_;
		back_->prev_=front_;
	}
	void push_front(const T& data);
	~Sentinel();

	class const_iterator{
		friend class Sentinel;
	protected:
		Node* curr_;

		const_iterator(Node* n)
		{
			curr_ = n;
		}
	public:
		const_iterator(){
			curr_ = nullptr;
		}
		const_iterator operator++(){
			curr_ = curr_->next_;
			return *this;
		}
		const_iterator operator++(int){
			const_iterator old = *this;
			curr_ = curr_->next_;
			return old;
		}
		const_iterator operator--(){
			
			curr_ = curr_->prev_;

			return *this;
		}
		const_iterator operator--(int){
			const_iterator old = *this;
			curr_ = curr_->prev_;
			return *this;
		}
		bool operator==(const_iterator rhs){
			return curr_ == rhs.curr_;
		}
		bool operator!=(const_iterator rhs){
			return curr_ != rhs.curr_;
		}
		const T& operator*()const{
			return curr_->data_;
		}
	};
	class iterator:public const_iterator{
		friend class Sentinel;
		iterator(Node* n):const_iterator(n){}
	public:
		iterator() :const_iterator() { }
		iterator operator++(){
			this->curr_ = this->curr_->next_;
			return *this;
		}
		iterator operator++(int){
			iterator old = *this;
			this->curr_ = this->curr_->next_;
			return old;
		}
		iterator operator--(){
			this->curr_ = this->curr_->prev_;
			return *this;
		}
		iterator operator--(int){}

		T& operator*(){
			return this->curr_->data_;
		}
		const T& operator*()const{
			return this->curr_->data_;
		}
	};
	const_iterator cbegin() const{
		return const_iterator(front_->next_);
	}
	iterator begin(){
		return iterator(front_->next_);
	}
	const_iterator cend() const{
		return const_iterator(back_);
	}
	iterator end(){
		return iterator(back_);
	}
};


template <typename T>
void Sentinel<T>::push_front(const T& data){
	Node* nn = new Node(data, front_->next_, front_);
	front_->next_->prev_ = nn;
	front_->next_ = nn;
}


template <typename T>
Sentinel<T>::~Sentinel(){
	Node* current = nullptr;
	while (front_->next_ != back_)
	{
		current = front_->next_;
		front_->next_ = current->next_;
		delete current;
	}
	current = nullptr;
	delete front_;
	delete back_;
}
