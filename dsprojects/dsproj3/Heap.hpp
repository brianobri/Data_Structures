// making a heap

#ifndef HEAP_HPP
#define HEAP_HPP

#include "HNode.hpp"
#include <vector>

class Heap {
    public:
    std::vector<HNode*> the_tree;
    int count = 0; // need a position and a count
    int position = 0;
    Heap(){the_tree.resize(2);}
    //~Heap();
    void fix_up(int &);
    void fix_down(int &);
    void enqueue(HNode *);
    HNode* dequeue();
    void create_heap(std::vector<HNode*>& );
    void swap_position(int , int );
    void clear();
};

void Heap::enqueue(HNode*  x)
{
    if (count == the_tree.size() - 1) // resize tree if needed
    {
        int z = the_tree.size() * 2;
        the_tree.resize(z);
    }
    the_tree[++count] = x;
    fix_up(count);   // fix up every time enqueue
}


HNode* Heap::dequeue()
{
    HNode* temp;
    temp = the_tree[1];
    swap_position(1, count); // last position swapped with first
    count--; // reduce count
    return temp;

}
void Heap::fix_up(int& x)
{
    if(x == 1) // top position
    {
        return;
    }
    if (*the_tree[x] < *the_tree[x/2])  // if child value greater than parent value then swap
    {
        int z = x/2;
        swap_position(x, z);
        fix_up(z);
    }

}

void Heap::fix_down(int & x)  // swap down the tree if out of order
{

    int left = x * 2;
    int right = (x * 2) + 1;
    if(right <= count)
    {
        if (*the_tree[left] < *the_tree[x])
        {
            swap_position(left, x);
            fix_down(left);
        }

    }
    else if (*the_tree[right] < *the_tree[x])
    {
            swap_position(right,x);
            fix_down(right);

    }
    else if (left <= count)
    {
            if (*the_tree[left] < *the_tree[x])
            swap_position(left, x);
    }


}

void Heap::swap_position(int x , int y)
{
    // simple swap
    HNode* temp = the_tree[x];
    the_tree[x] = the_tree[y];
    the_tree[y] = temp;
}



void Heap::create_heap(std::vector<HNode*>& a) {
    if (a.size() > the_tree.size() - 1){
        the_tree.resize(a.size() + 1);
    }

    for(int i = 0; i < a.size(); ++i){
        the_tree[i + 1] = a[i];
    }

    position = a.size();

    for (int i = (position - (position / 2)); i > 0; --i){
        fix_down(i);
    }

}

void Heap::clear()
{
    the_tree.clear();// clear resizes to 0
    the_tree.resize(2); // so set it to size 2 so no segfault
}

#endif
