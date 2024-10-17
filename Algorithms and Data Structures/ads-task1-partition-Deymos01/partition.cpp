#include <iostream>

long long partition(std::pair<int, int> p);

int main() {
  int n = 0;
  int k = 0;
  std::cin >> n >> k;
  std::cout << partition({n, k});
  return 0;
}

long long partition(std::pair<int, int> p) {
  int n = p.first;
  int k = p.second;
  auto *arr = new long long[n + 1]{0};
  for (int i = 1; i < n + 1; ++i) { arr[i] = 1; }

  long long prev1;
  long long prev2;
  for (int i = 2; i <= k; ++i) {
    prev1 = 0;
    for (int j = 1; j <= n; ++j) {
      if (j > i) { prev1 += arr[j - i]; }
      prev2 = arr[j];
      arr[j] = prev1;
      std::swap(prev1, prev2);
    }
  }
  long long res = arr[n];
  delete[] arr;
  return res;
}
