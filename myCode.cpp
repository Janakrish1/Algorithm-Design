#include "bits/stdc++.h"

using namespace std;

void path(int q, int r, vector < vector < long >> &p) {
  if(p[q][r] != 0) {
    path(q, p[q][r], p);
    cout << "v" << p[q][r] << " ";
    path(p[q][r], r, p);
  }
}

int main() {
  int n = 7;

  vector < vector < long >> d(n + 1, vector < long > (n + 1));
  vector < vector < long >> p(n + 1, vector < long > (n + 1, 0));
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      d[i][j] = INT_MAX;
      if (i == j) d[i][j] = 0;
    }
  }

  d[1][2] = 4, d[2][1] = 3, d[3][2] = 6, d[1][6] = 10;
  d[4][6] = 19, d[6][7] = 10, d[7][4] = 8, d[4][7] = 5;
  d[2][4] = 18, d[4][2] = 5, d[4][5] = 2, d[5][4] = 1;
  d[4][3] = 15, d[5][3] = 12;

  //   for(int k = 1;k <= n;k++) {
  //         for(int i = 1;i <= n;i++) {
  //             for(int j = 1;j <= n;j++) {
  //                 d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
  //             }        
  //         }
  //     }

  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (d[i][k] + d[k][j] < d[i][j]) {
          p[i][j] = k;
          d[i][j] = d[i][k] + d[k][j];
        }
      }
    }
  }

  path(7, 3, p);
  
  

  return 0;
}


