#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stack>
#include <string>

using namespace std;

const int maxstack = 10;
typedef double Stack_entry;
enum Error_code { success, overflow, underflow };

class Stack;
Error_code copy_stack_c(Stack &dest, const Stack &source);
class Stack {
  public:
      Stack() : count(0) {}
      Stack(const Stack& other) : count(other.count) {
        for (int i = 0; i < count; i++) {
          entry[i] = other.entry[i];
        }
      }
      Error_code pop() {
      Error_code outcome = success;
        if (count == 0)
          outcome = underflow;
        else --count;
          return outcome;
      }
      Error_code push(const Stack_entry &item) {
        Error_code outcome = success;
        if (count >= maxstack)
          outcome = overflow;
        else
          entry[count++] = item;
        return outcome;
      }
      Error_code top(Stack_entry &item) const {
        Error_code outcome = success;
        if (count == 0)
          outcome = underflow;
        else
          item = entry[count - 1];
        return outcome;
      }
      bool empty() const { return count == 0; }
      void clear() { count = 0; }
      bool full() const {
        return count == maxstack ? true : false;
      }
      int size() const { return count; }

    private:
      int count;
      Stack_entry entry[maxstack];
};

#endif