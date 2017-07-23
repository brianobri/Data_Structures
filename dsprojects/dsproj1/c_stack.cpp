#include "c_stack.h"
#include <cassert>
void c_stack::push(char in)
{
    ++current_size;
    // create an empty node
    Stack_node *newnode = NULL;
    newnode = new Stack_node;
    newnode->value = in;
    // place node in the place its suppose to go
    if(isempty())
    {
        top = newnode;
        newnode->next = NULL;
    }
    else
    {
        newnode->next = top;
        top = newnode;
    }
}

void c_stack::pop(char &in)
{
    --current_size;
    Stack_node *temp = NULL;
    //delete next value
    if (!isempty())
    {
        in = top->value;
        temp = top->next;
        delete top;
        top = temp;
    }

}
// delete every thing in stack
c_stack::~c_stack()
{
   Stack_node *tempnode, *nextnode;
   tempnode = top;
   while (tempnode != NULL)
   {
       nextnode = tempnode->next;
       delete tempnode;
       tempnode = nextnode;
   }
}

//shows next value in stack
char c_stack::peek()
{
    if(current_size > 0)
    {
        return top->value;
    }
    else
    {
         return NULL;
    }


}

// finds out if stack is empty
bool c_stack::isempty()
{
    bool temp_val;
    if (!top)
    {
        temp_val = true;
    }
    else
    {
        temp_val = false;
    }
    return temp_val;
}


