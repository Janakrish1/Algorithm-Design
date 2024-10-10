#include "bits/stdc++.h"

using namespace std;
static int cnt = 1;
int sum = 0;

void print(vector<int> &ans) {
  for(int k = 0;k < ans.size();k++) {
      cout << ans[k] << ", ";
    }
    cout << " }";
    cout << " W = " << sum ;
    cout << endl;
}

void subsetSum(vector<int> &ans, vector<int> &arr, int W, int n, int i) {
  if(W == 0) {
    cout << "\nValid Combination equals to target 52 = { ";
    print(ans);
    return;
  }
  if(i == n) 
    return;
  cout << "\n------------------------------------------------------------------------------------------------------\n\n";
  cout << "Step " << cnt << ":" << endl;
  cnt++;
  if(W - arr[i] >= 0) {
    cout << "Promising function returns true so we include weight " << arr[i] << endl;
    ans.push_back(arr[i]);
    sum += arr[i];
    cout << "Now the Include array looks like below:\n{ ";
    print(ans);
    
    subsetSum(ans, arr, W - arr[i], n, i + 1);
    cout << "\nBacktracking occurs here and now we remove the weight " << arr[i] << endl << endl;
    sum -= arr[i];
    ans.pop_back();
  }
  cout << "Now we backtrack and exlude the weight\n and call the function with the next index\n\n";
  cout << "Now the Include array looks like below:\n{ ";
    print(ans);
    
  subsetSum(ans, arr, W, n, i + 1);
}

int main() {
  int n = 6;
  int W = 52;
  vector<int> arr = {2, 10, 13, 17, 22, 42};
  vector<int> ans;
  subsetSum(ans, arr, W, n, 0);
  

  return 0;
}


