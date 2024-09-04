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
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	void print() const;
	void reversePrint() const;
	~DList();
};

//This function allows us to create a new node and push it to the fron of our list.
template <typename T>
void DList<T>::push_front(const T& data){
		Node* nn=new Node(data,front_);
		if(front_!=nullptr){
			front_->prev_=nn;
		}
		else{
			back_=nn;
		}
		front_=nn;
}

template <typename T>
void DList<T>::push_back(const T& data){
	//create new node pointer variable to hold pointer
	Node* nn = new Node(data, nullptr, back_);

	//if there is an existing back_ to the list
	if(back_ != nullptr)
	{
		//edit the existing back_'s next_ pointer to = nn
		back_->next_ = nn;
	}
	else
	{
		front_=nn; //if list is empty assign front_ to nn
	}
	back_ = nn; //assign back to nn
}

template <typename T>
void DList<T>::pop_front(){
	if(front_ != nullptr){
		Node* rm = front_;
		front_ = rm->next_;
		if(front_ != nullptr){
			front_->prev_=nullptr;
		}
		else{
			back_=nullptr;
		}
		delete rm;
	}

}

//This function removes a node from the back of the list
template <typename T>
void DList<T>::pop_back(){
	if (back_!=nullptr)
	{
		//let rm represent the address of the back of the list
		Node* rm = back_;
		back_ = rm->prev_; 	//let back represent the node before rm
							//if the node does not exist then back_ is a nullptr

		if(back_ != nullptr)	//if the node before rm exists
		{
			back_->next_ = nullptr;	//clear the pointer pointing to rm
		}
		else						//There is nothing before rm
		{
			front_ = nullptr;	//make the list completely empty
		}
		delete rm;	//delete the node
	}

}

template <typename T>
void DList<T>::print() const{
	Node* curr=front_;
	while(curr!=nullptr){
		std::cout << curr->data_ << " ";
		curr=curr->next_;
	}
	if(!front_){
		std::cout << "empty list";
	}
	std::cout << std::endl;
}
template <typename T>
void DList<T>::reversePrint() const{
	Node* curr=back_;
	while(curr!=nullptr){
		std::cout << curr->data_ << " ";
		curr=curr->prev_;
	}
	if(!back_){
		std::cout << "empty list";
	}
	std::cout << std::endl;
}
template <typename T>
DList<T>::~DList(){

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
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	void print() const;
	void reversePrint() const;
	~Sentinel();
};


template <typename T>
void Sentinel<T>::push_front(const T& data){
	Node* nn = new Node(data,front_->next_,front_);
	front_->next_->prev_=nn;
	front_->next_=nn;
}
template <typename T>
void Sentinel<T>::push_back(const T& data){
	Node* nn = new Node(data, back_, back_->prev_);
	back_->prev_->next_ = nn;
	back_->prev_ = nn;
}
template <typename T>
void Sentinel<T>::pop_front(){
	//if its an empty list... note that it means
	//front sentinel's next node is the back sentinel
	if(front_->next_!=back_){
		Node* rm = front_->next_;
		Node* B = rm ->next_;
		front_->next_= B;
		B->prev_=front_;
		delete rm;
	}
}
template <typename T>
void Sentinel<T>::pop_back(){
	if (back_->prev_ != front_)
	{
		Node* rm = back_->prev_;
		back_->prev_ = rm->prev_;
		rm ->prev_->next_ = back_;
		delete rm;
	}
	
}
template <typename T>
void Sentinel<T>::print() const{
	Node* curr=front_->next_;
	while(curr!=back_){
		std::cout << curr->data_ << " ";
		curr=curr->next_;
	}
	if(front_->next_==back_){
		std::cout << "empty list";
	}
	std::cout << std::endl;
}
template <typename T>
void Sentinel<T>::reversePrint() const{
	Node* curr=back_->prev_;
	while(curr!=front_){
		std::cout << curr->data_ << " ";
		curr=curr->prev_;
	}
	if(back_->prev_==front_){
		std::cout << "empty list";
	}
	std::cout << std::endl;
}
template <typename T>
Sentinel<T>::~Sentinel(){
	delete front_;
	delete back_;
}
