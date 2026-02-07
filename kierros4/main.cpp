#include <iostream>
#include <stack>
#include <string>
#include <cassert>

using namespace std;

const int maxstack = 10;
typedef int Stack_entry;
enum Error_code { success, overflow, underflow };

class Stack;
Error_code copy_stack_c(Stack &dest, const Stack &source);

class Stack {
  public:
    Stack() : count(0) {}
      Stack(const Stack&) = default;
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
      // Version (c)
      friend Error_code copy_stack_c(Stack &dest, const Stack& source) {
        if (&dest == &source) return success;
        dest.count = source.count;
        for (int i = 0; i < source.count; i ++) {
          dest.entry[i] = source.entry[i];
        }
        return success;
      };

    private:
      int count;
      Stack_entry entry[maxstack];
};


// Version (a)
Error_code copy_stack_a(Stack& dest, const Stack&source) {
  if (&dest == &source) return success;
  dest = source;
  return success;
}

// Version (b)
Error_code copy_stack_b(Stack& dest, const Stack&source) {
  if( &dest == &source) return success;
  Stack s = source;
  Stack temp;
  Stack_entry x;

  while (!s.empty()) {
    s.top(x);
    s.pop();
    temp.push(x);
  }

  while (!temp.empty()) {
    temp.top(x);
    temp.pop();
    Error_code rc = dest.push(x);
    if (rc != success) {
      return rc;
    }
  }

  return success;
}


typedef Error_code (*CopyFunc)(Stack&, const Stack&);

void version_check(Stack& dest, Stack& source, CopyFunc copy_stack) {
  // Nearly full
  for (int i = 1; i <=9; i ++) {
    source.push(i);
  }
  cout << "Stack source (before): " << source.size() << endl;
  cout << "Stack dest (before): " << dest.size() << endl;

  Error_code full = copy_stack(dest, source);
  cout << "Return value of copy_stack: " 
  << (full == success ? "success" :
      full == overflow ? "overflow" :
      full == underflow ? "underflow" : "fail")
  << endl;

  cout << "Stack source (after): " << source.size() << endl;
  cout << "Stack dest (after): " << dest.size() << endl;
  source.clear();
  dest.clear();
  
  // Nearly empty
  for (int i = 1; i <=2; i ++) {
    source.push(i);
  }
  cout << "Stack source (before): " << source.size() << endl;
  cout << "Stack dest (before): " << dest.size() << endl;

  Error_code empty = copy_stack(dest, source);
  cout << "Return value of copy_stack: " 
  << (empty == success ? "success" :
      empty == overflow ? "overflow" :
      empty == underflow ? "underflow" : "fail")
  << endl;

  cout << "Stack source (after): " << source.size() << endl;
  cout << "Stack dest (after): " << dest.size() << endl;
  source.clear();
  dest.clear();
}

int main() {
  Stack source, dest;
  //version_check(dest, source, copy_stack_a);
  //version_check(dest, source, copy_stack_b);
  version_check(dest, source, copy_stack_c);

}