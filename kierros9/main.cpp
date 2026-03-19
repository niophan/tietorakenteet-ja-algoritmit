#include <iostream>

using namespace std;

int f(int n) {
  if(n == 0) return 0;
  if (n > 0) {
    if(n % 2 == 0) {
      return f(n/2);
    } else {
      return 1 + f(n-1);
    }
  }

  return -1;
}

int f2(int n) {
  if(n <= 1) return n;
  if (n > 0) {
    if(n % 2 == 0) {
      return n + f2(n/2);
    } else {
      return f2((n + 1) / 2) +  f2((n - 1) / 2);
    }
  }

  return -1;
}



int main() {

  cout << "Tehtävä 1" << endl;
  cout << f(1) << endl;
  cout << f(2) << endl;
  cout << f(3) << endl;
  cout << f(99) << endl;
  cout << f(100) << endl;
  cout << f(128) << endl;

  cout << "Tehtävä 2" << endl;
  cout << f2(1) << endl;
  cout << f2(2) << endl;
  cout << f2(3) << endl;
  cout << f2(4) << endl;
  cout << f2(5) << endl;
  cout << f2(6) << endl;


  return 0;
}