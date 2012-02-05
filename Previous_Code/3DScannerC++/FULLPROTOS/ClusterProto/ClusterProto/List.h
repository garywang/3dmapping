/************************
*     Original Code     *
*   Will Oursler 2010   *
*ninjinuity.blogspot.com*
************************/

#ifndef _LIST_H_
#define _LIST_H_

template <class type>
struct node
{
	type* _data;
	node* _next;
	bool _protected;
	node(type* data, node* next, bool Protected=true)
	{
		_data=data;
		_next=next;
		_protected=Protected;
	};
	~node()
	{
		if(!_protected)
			delete _data;
	};
};

template <class type>
class list
{
private:
	node<type>* first;
	node<type>* last;
	bool _protected;
public:
	list(bool Protected=true){
		first=NULL;
		last=NULL;
		_protected=Protected;
	}
	list(list* tocopy){
		list();
		this.add(tocopy);
	};
	~list(){
		node<type>* temp;
		while(first!=NULL)
		{
			temp=first->_next;
			delete first;
			first=temp;
		};
	};
	void add(type* data){
		if(first==NULL)
		{
			first=new node<type>(data, NULL,_protected);
			last=first;
		}
		else
		{
			last->_next=new node<type>(data, NULL,_protected);
			last=last->_next;
		}
	}
	void add(list<type>* data){
		for(int i=0; i<data->size(); i++)
			this->add(data->get(i));
	};
	type* get(int i){
		node<type>* curr=first;
		for(int j=0; j<i; j++)
		{
			if(curr==NULL)
				break;
			curr=curr->_next;
		};
		if(curr==NULL)
			return NULL;
		return curr->_data;
	}
	void remove(int i){
		node<type>* curr=first;
		node<type>* prev=NULL;
		for(int j=0; j<i; j++)
		{
			if(curr==NULL)
				break;
			prev=curr;
			curr=curr->_next;
		};
		if(curr==NULL)//this element doesn't exist, don't do anything
			return;
		//remove curr from the list;
		if(prev!=NULL)
			prev->_next=curr->_next;
		else
			first=curr->_next;
		//dispose of curr
		delete curr;
	};
	int size(){
		int size=0;
		node<type>* curr=first;
		while(curr!=NULL)
		{
			size++;
			curr=curr->_next;
		}
		return size;
	}
};
#endif