#include "bits/stdc++.h"

using namespace std;

bool isSafe(int row, int col, int n, vector<int> &colQueens, vector<int> &leftDia, vector<int> &rightDia) {
  if(colQueens[col] || rightDia[row + col] || leftDia[row - col + n - 1])
    return false;
  return true;
}

int countNQueensSolutions(vector<vector<int>> &chessBoard, int row, int n, vector<int> &colQueens, vector<int> &leftDia, vector<int> &rightDia) {
  // Base case
  if(row == n)
    return 1;

  int ans = 0;
  for(int col = 0;col < n;col++) {
    if(isSafe(row, col, n, colQueens, leftDia, rightDia)) {
      
      colQueens[col] = 1;
      rightDia[row + col] = 1;
      leftDia[row - col + n - 1] = 1;

      ans += countNQueensSolutions(chessBoard, row + 1, n, colQueens, leftDia, rightDia);
      
      colQueens[col] = 0;
      rightDia[row + col] = 0;
      leftDia[row - col + n - 1] = 0;

    }
  }
  return ans;
}


int nQueens(int n) {
  vector<vector<int>> chessBoard(n, vector<int> (n, 0));
  vector<int> colQueens(n, 0);
  vector<int> leftDia(2 * n - 1, 0);
  vector<int> rightDia(2 * n - 1, 0);

  return countNQueensSolutions(chessBoard, 0, n, colQueens, leftDia, rightDia);
}

int main() {
  int testcases, n;
  cin >> testcases;
  
  while(testcases--) {
    cin >> n;
    cout << "The count of solutions for N Queens problem where n = " << n << " is ";
    cout << nQueens(n) << endl;
  }

  return 0;
}