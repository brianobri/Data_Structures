#ifndef PALINDROME_HPP
#define PALINDROME_HPP
#include "arr_queue.h"
#include "c_stack.h"
#include <string>

class Palindrome {

public:
  Palindrome();
  int test_string(const std::string& s);

private:
  void recursive_push_enqueue(std::string,c_stack &,arr_queue&);
  int recusive_pop_dequeue(int,c_stack& ,arr_queue&);
};

#endif
