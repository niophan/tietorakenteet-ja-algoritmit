#include <iostream>
#include <stack>
#include <string>
#include <cassert>

using namespace std;

const int maxstack = 10; // small value for testing
typedef int Stack_entry;
enum Error_code { success, overflow, underflow };

class Extended_stack {
    public:
        Extended_stack();
        Error_code pop();
        Error_code push(const Stack_entry &item);
        Error_code top(Stack_entry &item) const;
        bool empty() const;
        void clear(); // Reset the stack to be empty.
        bool full() const ; // If the stack is full, 
                             // return true; else return false.
        int size() const; // Return the number of entries 
                           // in the stack.

    private:
        int count;
        Stack_entry entry[maxstack];
};

Extended_stack::Extended_stack() : count(0) {};

Error_code Extended_stack::push(const Stack_entry &item)
/* Pre: None.
Post: If the Stack is not full, item is added to the top of the Stack. If the Stack is
full, an Error code of overflow is returned and the Stack is left unchanged.
*/
{
  Error_code outcome = success;
  if (count >= maxstack)
    outcome = overflow;
  else
    entry[count++] = item;
  return outcome;
}

Error_code Extended_stack::pop( )
/* Pre: None.
Post: If the Stack is not empty, the top of the Stack is removed. If the Stack is
empty, an Error code of underflow is returned. */
{
  Error_code outcome = success;
  if (count == 0)
    outcome = underflow;
  else --count;
    return outcome;
}


Error_code Extended_stack::top(Stack_entry &item) const
/* Pre: None.
Post: If the Stack is not empty, the top of the Stack is returned in item. If the Stack
is empty an Error code of underflow is returned. */
{
  Error_code outcome = success;
  if (count == 0)
    outcome = underflow;
  else
    item = entry[count - 1];
  return outcome;
}

bool Extended_stack::empty()const
/* Pre: None.
Post: If the Stack is empty, true is returned. Otherwise false is returned. */
{
bool outcome = true;
if (count > 0) outcome = false;
return outcome;
}

void Extended_stack::clear() {
  count = 0;
}

bool Extended_stack::full() const {
  return count == maxstack ? true : false;
}

int Extended_stack::size() const {
  return count;
}

int main( ) {
  Extended_stack exs;

  // clear()
  for (int i = 0; i < maxstack; i++) {
    exs.push(i);
  }
  exs.clear();
  assert(exs.size() == 0);
  cout << "clear() resert stack to empty stack - ok!" << endl;

  // full()
  assert(exs.full() == false);
  cout << "full() returns false - ok!" << endl;

  // size()
  assert(exs.size() == 0);
  cout << "size() returns empty stack - ok!" << endl;

}

