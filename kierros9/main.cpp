#include <iostream>
#include <chrono>

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

void move(int count, int start, int finish, int temp,
          float& transfer_orders,
          float& move_calls) {
  move_calls += 1;

  if (count > 0) {
    move(count - 1, start, temp, finish, transfer_orders, move_calls);
    // cout << "Move disk "  << count << " from" << start << " to " << finish << "." << endl;
    transfer_orders += 1;
    move(count - 1, temp, finish, start, transfer_orders, move_calls);
  }
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

  cout << "Tehtävä 3" << endl;
  double previous_time_ms = 0.0;
  for (int disks = 10; disks <= 15; ++disks) {
      float transfer_orders = 0; // show algorithmic work of Hanoi operations
      float move_calls = 0; // show recursion overhead

    auto start = chrono::high_resolution_clock::now();
      move(disks, 1, 3, 2, transfer_orders, move_calls);
    auto end = chrono::high_resolution_clock::now();

    double elapsed_ms = chrono::duration<double, milli>(end - start).count();

    cout << "disks=" << disks
        << " transfer_orders=" << transfer_orders
        << " move_calls=" << move_calls
         << " time_ms=" << elapsed_ms;

    if (previous_time_ms > 0.0) {
      cout << " time_ratio=" << (elapsed_ms / previous_time_ms);
    }

    cout << endl;
    previous_time_ms = elapsed_ms;
  }

  return 0;
}