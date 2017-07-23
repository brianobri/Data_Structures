#include "arr_queue.h"
#include <iostream>
using namespace std;

arr_queue::arr_queue()
{
    // create the array
    list = new char[max_size];
}

arr_queue::~arr_queue()
{
    // delete the array from memory
    delete [] list;
}

void arr_queue::enqueue(char& in)
{
    // make sure we aren't full
    assert(count < max_size);
    // set the element at the correct position (with wrapping) and update count

    list[(front + count++) % max_size] = in;
}

char arr_queue::dequeue()
{
    // make sure we aren't empty
    if (count > 0)
    {
        // store the element at the front
        char ret = list[front];
        // adjust front
        // also adjusts count
        // set front to 0 if there are no more elements the in queue
        front = (--count == 0 ? 0 : ++front % max_size);
        // return the element
        return ret;
    }
    else
    {
         return NULL;
    }

}

char& arr_queue::peek()
{
    // make sure the array isnt empty
    if (count > 0)
    {
        return list[front];
    }
    // return the front elements data

    return emptychar; // if nothing in array return NULL
}
