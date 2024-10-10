#include "bits/stdc++.h"

using namespace std;


int main() {

  return 0;
}





int knapsackTabulation(size n, const number wt[],  const number P[], index W) {
  // Base Case
  const number DP[n + 1][W + 1];

  for(i = 0;i <= n;i++) {
    for(w = 0;w <= W;w++) {
      if(i == 0 || w == 0) 
        DP[i][w] = 0;
      else if(wt[i - 1] <= w) 
        DP[i][w] = max(P[i - 1] + DP[i - 1][w - wt[i - 1]], 
                      DP[i - 1][w]);
      else
        DP[i][w] = DP[i - 1][w];
    }
  }
  return DP[n][W];
}





int knapsackMemoization(size n, const number wt[],  const number P[], const number DP[][], index i, index W) {
  // Base Case
  if(i < 0) 
    return 0;
  // Check DP array
  if(DP[i][W])
    return DP[i][W];
  
  if(wt[i] > W) {
    DP[i][W] = knapsackMemoization(n, wt, P, DP, i - 1, W);
    return DP[i][W];
  }

  DP[i][W] = max(P[i] + knapsackMemoization(n, wt, P, DP, i - 1, W - wt[i]), 
                knapsackMemoization(n, wt, P, DP, i - 1, W));
  return DP[i][W];
}





