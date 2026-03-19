#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

int non_recursive(int x, int y) {
  if(x <= 0 || y <= 0) {
    return 0;
  }

  vector<int> a, b, result;

  for (int i = 1; i <= x; i ++) {
    if(x % i == 0) {
      a.push_back(i);
    }
  }

  for (int i = 1; i <= y; i ++) {
    if(y % i == 0) {
      b.push_back(i);
    }
  }

  for (int x : a) {
    for (int y : b) {
      if (x == y) {
        result.push_back(x);
        break;
      }
    }
  }

  int highest_number = 1;
  for (int x : result ) {
    if(x > highest_number) {
      highest_number = x;
    }
  }

  return highest_number;
}

int recursive(int x, int y) {
  if (x <= 0 || y <= 0) {
    return 0;
  }

  if(y == 0) return x;
  return recursive(y, x % y);
}

int iterative(int x, int y) {
  if (x <= 0 || y <= 0) {
    return 0;
  }

  while (y != 0) {
    int remainder = x % y;
    x = y;
    y = remainder;
  }

  return x;
}

int main() {

  cout << "Tehtävä 6.a " << endl;
  int a = non_recursive(9, 18);
  cout << a << endl;

  cout << "Tehtävä 6.b " << endl;
  int b = recursive(9, 18);
  cout << b << endl;

  cout << "Tehtävä 6.c " << endl;
  int c = iterative(9, 18);
  cout << c << endl;

  return 0;
}