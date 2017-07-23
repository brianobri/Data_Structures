#ifndef C_STACK_H
#define C_STACK_H
#include <iostream>
#include <cassert>
using namespace std;

class c_stack
{
    private:
        int current_size = 0;
        struct Stack_node{
            char value;
            Stack_node *next;
        };
        Stack_node *top;
    public:
        c_stack(){top = NULL;};
        ~c_stack();
        void push(char);
        void pop(char &);
        char peek();
        bool isempty();
};

#endif // STACK_H
