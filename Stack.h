#pragma once
#include <cstddef>
using namespace std; 
class Element
{
private:
	int value;
public:
	Element* next;
	Element(int val)	//2
	{
		value = val;	//1
		next = NULL;	//1
	}
	int getvalue()
	{
		return value;
	}
	
};

class Stack
{
protected:
	Element* top = NULL;
	unsigned long Count = 0;
public:
	unsigned long long int N_op = 0;
	void Init()					//4*Count + 1
	{
		Element* tmp;
		while (top != NULL)		//1
		{
			tmp = top;			//1
			top = tmp->next;	//2
			delete(tmp);
			N_op += 4;
		}
		Count = 0;				//1
	}
	~Stack()					//4*Count
	{
		Element* tmp;			
		while (top != NULL)		//1
		{
			tmp = top;			//1
			top = tmp->next;	//2
			delete(tmp);		
		}
	}
	bool isempty()				//1
	{
		N_op++;
		return top == NULL;		//1
	}
	unsigned long count()		//1
	{
		return Count;			//1
	}

	void push(int val);
	int	 pop();
};

inline void Stack::push(int val)//8
{
	Element* el_ptr, * tmp_ptr;	
	el_ptr = new Element(val);	//3
	el_ptr->next = top;			//2
	top = el_ptr;				//1
	Count++;					//2
	N_op += 8;
}
inline int Stack::pop()			//8
{
	Element* tmp;				
	int val = top->getvalue();	//2
	tmp = top->next;			//2
	delete(top);				//1
	top = tmp;					//1
	Count--;					//2
	N_op += 8;
	return val;
}

