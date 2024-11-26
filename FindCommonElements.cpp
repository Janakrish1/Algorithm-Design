#include "./bits/stdc++.h"

using namespace std;

void findCommonElements(vector<int> &s, vector<int> &t) {
    set<int> hashSet;
    vector<int> U;

    for(auto num : s) {
        hashSet.insert(num);
    }

    for(auto num : t) {
        if(hashSet.find(num) != hashSet.end()) {
            U.push_back(num);
            hashSet.erase(num);
        }
    }

    if(U.size() == 0) {
        cout << "There are no common elements.";
    }
    else {
        cout << "Common elements are: ";
        for(auto num : U) {
            cout << num << " ";
        }
    }
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> s(n), t(m);
  
  for(int i = 0;i < n;i++) {
    cin >> s[i];
  }

  for(int i = 0;i < m;i++) {
    cin >> t[i];
  }

  findCommonElements(s, t);

  return 0;
}
