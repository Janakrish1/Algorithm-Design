#include "bits/stdc++.h"
using namespace std;

static int cnt = 0;
vector<string> co = {"red", "green", "white"};

bool valid(vector<vector<int>> &mat, int i, vector<int> &vcolor, int color) {
  for (int j = 0; j < mat.size(); j++) {
    if (mat[i][j] > 0 && vcolor[j] == color) 
      return false;
  }
  return true; 
}

void mColoring(vector<vector<int>> &mat, int m, vector<int> &vcolor, int i) {
  if (i == mat.size()) {
    cnt++;
    cout << "\nPossible Solution " << cnt << endl;
    for (int j = 0; j < mat.size(); j++) {
      cout << "V" << j + 1 << "(" << co[vcolor[j] - 1] << ") ";
    }
    // cout << endl<<  endl;
    return;
  }

  for (int color = 1; color <= m; color++) {
    if (valid(mat, i, vcolor, color)) {
      // cout << "Placing Color " << co[color - 1] << " to vertex " << i + 1 << endl; 
      vcolor[i] = color;
      mColoring(mat, m, vcolor, i + 1);

      // cout << "Backtrack by removing the color " << co[color - 1] << " from vertex " << i + 1 << endl;
      vcolor[i] = 0;
    }
  }
}

int main() {
  int m = 3;
  int n = 6; // Number of vertices
  vector<vector<int>> mat(n, vector<int>(n, 0));
  mat[0][1] = 1; mat[1][0] = 1;
  mat[0][3] = 1; mat[3][0] = 1;
  mat[1][2] = 1; mat[2][1] = 1;
  mat[1][4] = 1; mat[4][1] = 1;
  mat[2][5] = 1; mat[5][2] = 1;
  mat[3][4] = 1; mat[4][3] = 1;
  mat[4][5] = 1; mat[5][4] = 1;

  vector<int> vcolor(n, 0);
  mColoring(mat, m, vcolor, 0);

  return 0;
}
