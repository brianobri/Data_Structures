#include "Palindrome.hpp"
#include "arr_queue.h"
#include "c_stack.h"
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

//didn't need to use the constructor after all
Palindrome::Palindrome()
{

}

// test the palindrome from test_palindrome.cpp
int Palindrome::test_string(const std::string& my_string)
{
    // create a stack/queue,
    c_stack astack;
    arr_queue aqueue;

    //get rid of whitespace and other symbols other than the letters in the string and append it to an empty string
    int i = 0;
    std::string newstring = ""; // don't want it accessiable so I didnt make it a private variable
    while (i < my_string.length()+1)
    {
        if (((my_string.substr(i,1) >= "A") && (my_string.substr(i,1) <= "Z")) || ((my_string.substr(i,1) >= "a") && (my_string.substr(i,1) <= "z")))
        {
            newstring.append(my_string.substr(i,1));
        }
        i++;
    }
    //change string to all lowercase to make comparisons easy
    std::transform(newstring.begin(), newstring.end(), newstring.begin(), ::tolower);

    //Using recursion, add each alphanumeric character to both a stack and a queue.
    recursive_push_enqueue(newstring,astack,aqueue);
    //Using recursion, pop a character from the stack and dequeue a character from the queue.
    //If the characters are not equal -
    //Destroy the stack and queue appropriately. (this can be handled by the compiler if you wish, just make sure not to have memory leaks)
    //Return the number of correct matches before the mismatch occurred.
    //If they are equal, increment a counter for the correct number of matches.
    //When both the stack and queue are empty - return -1 to indicate it is a palindrome.

    int temp = recusive_pop_dequeue(0,astack,aqueue);
    return temp;
}

// recursive call pushing and enqueue
void Palindrome::recursive_push_enqueue(std::string rec_string,c_stack & astack,arr_queue & aqueue)
{
    //base case- nothing left in the string
    if(rec_string.length() == 0)
    {
        return;
    }
    else
    {
        char temp_ch= rec_string.substr((rec_string.length()-1),1)[0]; // put in last letter in string
        astack.push(temp_ch);
        aqueue.enqueue(temp_ch);
        rec_string.resize(rec_string.length()-1); // truncate last letter in string
        recursive_push_enqueue(rec_string, astack, aqueue); // call recursive_push_enqueue until all letters have been accounted for
    }
}

// recursive call poping, dequeing and comparing the letters
int Palindrome::recusive_pop_dequeue(int match_number,c_stack & astack,arr_queue & aqueue)
{
    // look at the next char in the stack and queue
    if (astack.peek() == aqueue.peek())
    {
        //a base case- if nothing in the stack and queue return that they are equal
        if (astack.peek() == NULL)
        {
            return -1;
        }
        match_number++; // number of matched letters from stack and queue
        char temp_char; // don't need the value from this char but need something to store return value from stack and queue
        astack.pop(temp_char);
        temp_char = aqueue.dequeue();
        match_number = recusive_pop_dequeue(match_number,astack, aqueue); // recursive call, look at next letter in line

    }

    return match_number; // if a mismatch somewhere in the palindrome string return the number of matches to either the next recursive call up or to the function

}


