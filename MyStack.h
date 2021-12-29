#pragma once
#include "Stack.h"
#include <stdio.h>
#include <iostream>
class MyStack : public Stack
{
private:
	int GetElemVal(unsigned long ind);
	void SetElemVal(unsigned long ind, int val);
	void Swap(unsigned long ind, unsigned long jnd);
	void Reverse();
	void hoarsort(const unsigned long first, const unsigned long last);
public:
	void sort(bool up);
	void print();
	void arr_fill(int *p, int cnt);
	void rnd_fill(unsigned long cnt, int downval, int upval);
};

void MyStack::arr_fill(int *p, int cnt)
{
	this->Init();
	if (p == NULL)
	{
		return;
	}
	for (int i = 0; i < cnt; i++)
	{
		this->push(p[i]);
	}
	Count = cnt; 
	N_op = 0;
}

void MyStack::rnd_fill(unsigned long cnt, int downval, int upval)
{
	this->Init();
	for (int i = 0; i < cnt; i++)
	{
		if (downval > 0) this->push(downval + rand() % (upval - downval));
		else this->push(downval + rand() % (abs(downval) + upval));
		Count = cnt;
		N_op = 0;
	}
}



inline int MyStack::GetElemVal(const const unsigned long ind)
{
	MyStack *tmp = new MyStack();
	int val; 
	unsigned long cnt;
	if (ind > Count-1)
	{
		cout << "Ошибка: индекс " << ind << " за границей стека!";
		exit(1);
	}
	for (int i = 0; i < ind; i++)
	{
		tmp->push(this->pop());
		N_op += 3;
	}
	N_op++;
	val = this->pop();N_op++;
	this->push(val);
	cnt = tmp->Count; N_op++;
	for (int i = 0; i < cnt; i++)
	{
		this->push(tmp->pop());
		N_op += 3;
	}
	N_op++;
	N_op += tmp->N_op;
	delete(tmp);
	return(val);
}

inline void MyStack::SetElemVal(unsigned long ind, const int val)
{
	MyStack* tmp = new MyStack();
	if (ind >= Count)
	{
		cout << "Ошибка: индекс за границей стека!";
		exit(1);
	}
	for (int i = 0; i < ind; i++)
	{
		tmp->push(this->pop());
		N_op += 3;
	}
	N_op++;
	tmp->pop();
	this->push(val);
	for (int i = 0; i < tmp->count(); i++)
	{
		this->push(tmp->pop());
		N_op += 3;
	}
	N_op++;
	N_op += tmp->N_op;
	delete(tmp);
}

inline void MyStack::Swap(const unsigned long ind1, const unsigned long ind2)
{
	MyStack *tmp1, *tmp2;
	tmp1 = new MyStack();
	tmp2 = new MyStack();
	unsigned long cnt1, cnt2;
	
	if (fmax(ind1, ind2) >= this->Count)
	{
		cout << "Индекс " << fmax(ind1, ind2) << " за пределами стека\n";
		exit(1);
	}
	for (int i = 0; i < fmin(ind1, ind2) + 1; i++)
	{
		tmp1->push(this->pop());
		N_op += 4;
	}
	N_op++;
	for (int i = 0; i < (fmax(ind1, ind2) - fmin(ind1, ind2)); i++)
	{
		tmp2->push(this->pop());
		N_op += 6;
	}
	N_op++;
	this->push(tmp1->pop());
	tmp1->push(tmp2->pop());
	cnt1 = tmp1->count(); N_op++;
	cnt2 = tmp2->count(); N_op++;
	for (int i = 0; i < cnt2; i++)
	{
		this->push(tmp2->pop());
		N_op += 3;
	}
	N_op++;
	for (int i = 0; i < cnt1; i++)
	{
		this->push(tmp1->pop());
		N_op += 3;
	}
	N_op += tmp1->N_op;
	delete(tmp1);
	N_op += tmp2->N_op;
	delete(tmp2);
}

inline void MyStack::Reverse()
{
	MyStack* tmp1, * tmp2;
	tmp1 = new MyStack();
	tmp2 = new MyStack();
	unsigned long cnt = this->Count;
	for (int i = 0; i < cnt; i++)
		tmp1->push(this->pop());
	for (int i = 0; i < cnt; i++)
		tmp2->push(tmp1->pop());
	for (int i = 0; i < cnt; i++)
		this->push(tmp2->pop());
	delete(tmp1);
	delete(tmp2);
}

inline void MyStack::hoarsort(const unsigned long first, const unsigned long last)
{
	int tmp, x;
	unsigned long i = first, j = last;
	N_op += 2;
	if((i>j)||(j>Count-1))
	{
		cout << "Ошибка: неверный индекс! - i : " << i << ", j : " << j;
		exit(1);
	}
	N_op += 2;
	x = this->GetElemVal((first + last) / 2); N_op += 2;
	do {
		while (this->GetElemVal(i) < x)
		{
			i++; N_op += 3;
		}
		while (this->GetElemVal(j) > x)
		{
			j--; N_op += 3;
		}
		if (i <= j)
		{
			if (i < j)
			{
				this->Swap(i, j);
			}
			N_op++;
			i++; N_op += 2;
			j--; N_op += 2;
		}
		N_op++;
		N_op++;
	} while (i <= j);
	if (i < last)
		hoarsort(i, last);
	if (first < j)
		hoarsort(first, j);
	N_op += 2;
}

inline void MyStack::sort(bool up)
{
	//Swap(0, 10);
	this->hoarsort(0, Count-1);
	N_op++;
	if (!up) this->Reverse();
}


inline void MyStack::print()
{
	Element* tmp = top;
	while (tmp != NULL)
	{
		cout << tmp->getvalue() << " ";
		tmp = tmp->next;
	}
	unsigned long cnt = Count;
	cout << "Number of elements: " << cnt << "\n";
}

