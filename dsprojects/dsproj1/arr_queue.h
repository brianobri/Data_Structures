#ifndef ARR_QUEUE_H
#define ARR_QUEUE_H
#include <cassert>
#include <iostream>

class arr_queue
{

    private:
        // the size of the array arbitary value to cover any size in test_palindrome
        int max_size = 50;
        // the number of elements in the queue
        int count = 0;
        // the index of the front
        int front = 0;
        // the array itself
        char* list;
        char emptychar = NULL;

    public:
        arr_queue();
        ~arr_queue();
        void enqueue(char&);
        char dequeue();
        char& peek();
        void clear() { front =0; count = 0; }
        int size() { return count; }

};

#endif // QUEUE_H
