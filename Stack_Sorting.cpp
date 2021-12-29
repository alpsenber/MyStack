// Stack_Sorting.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "MyStack.h"
#include "stdio.h"
#include "time.h"


int main()
{
    setlocale(LC_ALL, "Russian");
    MyStack* stack;

    stack = new MyStack();
    stack->rnd_fill(200, 0, 500);
    stack->print();
    clock_t start = clock();
    stack->sort(1);
    clock_t end = clock();
    stack->print();
    double sec = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "\n" << "выполнено за " << stack->N_op << " операций и " << sec << " сек.";
    delete(stack);
}