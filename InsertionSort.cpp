#include "./bits/stdc++.h"

using namespace std;

void insertionSort(vector<int> &S, int n) {
    int i, j;
    int x;
    for(int i = 2;i <= n;i++) {
        x = S[i];
        j = i - 1;

        while(S[j] > x) {
            S[j + 1] = S[j];
            j--;
        }
        S[j + 1] = x;
    }
}

int main() {
  int n;
  cin >> n;
  vector<int> S(n + 1);
  S[0] = INT_MIN;
  
  for(int i = 0;i <= n;i++) {
    cin >> S[i + 1];
  }

  insertionSort(S, n);

  cout << "Sorted Array - ";
  for(int i = 1;i <= n;i++) {
    cout << S[i] << " ";
  }

  return 0;
}
