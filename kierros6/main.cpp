#include "queue.h"
#include <cmath>
#include <string>

using namespace std;
bool get_line(string &first, string &second) {
  string input;
  cout << "Please input some two text part, either be seperated by a colon (:) or not:" << endl;
  getline(cin, input);
  int pos = input.find(":");
  if (pos == string::npos) {
    return false;
  }

  first = input.substr(0, pos);
  second = input.substr(pos + 1 );
  return true;
}


int main() {
  Extended_queue left_queue, right_queue;
  char x, y;
  int left, right;
  string first, second;
  bool check = true;
  if(!get_line(first, second)) { 
    cout << "N" << endl; 
  } else {
    for (char c : first) {
      left_queue.append(c);
    }
    left = left_queue.size();

    for (char c: second) {
      right_queue.append(c);
    }
    right = right_queue.size();

    if(left < right) {
      cout << "R" << endl;
    } else if (left > right) {
      cout << "L" << endl;
    } else {
      while(!left_queue.empty() || !right_queue.empty()) {
        left_queue.serve_and_retrieve(x);
        right_queue.serve_and_retrieve(y);
        (x == y) ? check : check = false;
      }
      if(check) {
        cout << "S" << endl;
      } else {
        cout << "D" << endl;
      }
    }
  }
}