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
/* Pre: The user supplies a line of text.
Post: The characters are printed in reverse order.
Uses: The STL class stack and its methods */
{
  string text;
  stack<char> characters; // declares and initializes a stack of characters
  cout << " Type in a line of text." << endl
        << " The characters will be printed in reverse order." << endl;
  getline(cin, text);

  if(is_palindrome(text)) {
    cout << "Given string is a palindrome." << endl;
  } else {
    cout << "Given string is a normal text." << endl;
  }

  for (int i = 0; i < text.length(); i++) {
    characters.push(text[i]);
  }
  cout << endl << endl;
  while (!characters.empty( )) {
    cout << characters.top( );
    characters.pop( );
  }
  cout << endl;
}
