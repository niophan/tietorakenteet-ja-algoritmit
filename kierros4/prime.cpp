#include <iostream>
#include <stack>
#include <string>
#include <cassert>
#include <cmath>


using namespace std;

const int maxstack = 100;
typedef int Stack_entry;
enum Error_code { success, overflow, underflow };


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
    private:
      int count;
      Stack_entry entry[maxstack];
};

int main() {
  Stack prime;
  Stack_entry x;
  int input, r;
  int p = 2;
  cout << "Give an integer: ";
  cin >> input;
  while(input > pow(p, 2)) {
    while(input %p == 0) {
      input = input / p;
      prime.push(p);
    } 
    p++;
  }
  if(input > 1) {
    prime.push(input);
  }
  while(!prime.empty()) {
    prime.top(x);
    cout << " " << x;
    prime.pop();
  }
  cout << "." << endl;
}