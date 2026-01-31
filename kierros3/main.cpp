#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool is_palindrome(const string& text) {
  stack<char>pa;
  for (char c : text) pa.push(c);
  for (char c : text) {
    if (c != pa.top()) return false;
    pa.pop();
  }
  return true;
}


int main( )
/* Pre: The user supplies an integer n and n decimal numbers.
Post: The numbers are printed in reverse order.
Uses: The STL class stack and its methods */
{
  int n;
  char item;
  string m;
  stack<char> characters; // declares and initializes a stack of numbers
  cout << " Type in an integer n followed by n decimal numbers." << endl
        << " The text will be printed in reverse order." << endl;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> item;
    characters.push(item);
    m += item;
  }

  if(is_palindrome(m)) {
    cout << "Given string is a palindrome." << endl;
  } else {
    cout << "Given string is a normal text." << endl;
  }
  cout << endl << endl;
  while (!characters.empty( )) {
    cout << characters.top( ) << " ";
    characters.pop( );
  }
  cout << endl;
}