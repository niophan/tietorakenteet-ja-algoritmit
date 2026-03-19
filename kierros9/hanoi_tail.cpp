#include <iostream>
#include <chrono>

using namespace std;

void hanoi_tail(int count, int start, int finish, int temp) {
  int swap;
  while(count > 0) {
    hanoi_tail(count-1, start, temp, finish);
    cout << "Move disk "  << count << " from " << start << " to " << finish << "." << endl;
    count --;
    swap = start;
    start = temp;
    temp = swap;
  }
}


int main() {
  hanoi_tail(3, 1, 3, 2);

  return 0;
}
