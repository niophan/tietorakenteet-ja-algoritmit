#include <iostream>
#include <chrono>

using namespace std;

int fibonacci(int n, int& fibonacci_call, int& max_depth, int& current_depth) {
  current_depth += 1;
  fibonacci_call += 1;
  if (current_depth > max_depth) {
    max_depth = current_depth;
  }

  float result;
  if (n <= 0) {
    result = 0;
  } else if (n == 1) {
    result = 1;
  } else {
    result = fibonacci(n - 1, fibonacci_call, max_depth, current_depth)
        + fibonacci(n - 2, fibonacci_call, max_depth, current_depth);
  }

  current_depth -= 1;
  return result;
}

int main() {
  cout << "Tehtävä 5" << endl;
  for (int n = 0; n <= 30; ++n) {
      int max_depth = 0;
      int current_depth = 0;
      int fibonacci_call = 0;

    auto start = chrono::high_resolution_clock::now();
      float fibo_value = fibonacci(n, fibonacci_call, max_depth, current_depth);
    auto end = chrono::high_resolution_clock::now();

    double elapsed_ms = chrono::duration<double, milli>(end - start).count();

    cout << "n=" << n
        << " Fibonacci value=" << fibo_value
        << " Fibonacci calls=" << fibonacci_call
        << " time_ms=" << elapsed_ms
        << " depth=" << max_depth
        << endl;
  }

  return 0;
}