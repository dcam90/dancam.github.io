#include <iostream>
#include <chrono>

using namespace std;

int main() {
  cout << "Test Timing" << endl;

  const auto begin = chrono::high_resolution_clock::now();

  int sum = 0;
  for (int i = 0; i < 10000; i++) {
  	++sum;
  }

  const auto end = chrono::high_resolution_clock::now();
    
  cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
  cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms" << endl;


}
