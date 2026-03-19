#include <iostream>
#include <chrono>

using namespace std;

void hanoi(int count, int start, int finish, int temp) {
  if (count > 0) {
    hanoi(count - 1, start, temp, finish);
    cout << "Move disk "  << count << " from " << start << " to " << finish << "." << endl;
    hanoi(count - 1, temp, finish, start);
  }
}

int main() {
  hanoi(3, 1, 3, 2);

  return 0;
}
