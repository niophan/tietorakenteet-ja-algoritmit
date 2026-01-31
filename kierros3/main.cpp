#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main( )
/* Pre: The user supplies a sequence of intergers.
Post: The integers are printed in reverse order.
Uses: The STL class stack and its methods */
{
  double item;
  bool check = true;
  stack<double> numbers; // declares and initializes a stack of numbers
  cout << " Type in a sequence of integers of increasing value." << endl
        << " The interger will be printed in decreasing order." << endl;

  do {
    cin >> item;
    if(numbers.empty()) {
      numbers.push(item);
    } else if(item < numbers.top()) {
      check = false;
      cout << "Program ends!" << endl;
    } else {
      numbers.push(item);
    }
  } while(check);

  cout << endl << endl;
  while (!numbers.empty()) {
    cout << numbers.top( ) << " ";
    numbers.pop();
  }

  cout << endl;
}

