#include "bits/stdc++.h"
using namespace std;


void sortByLeftShift(vector<int> &A, int m, int n, vector<int> &Aux) {
    int i = m - 1, j = m + n - 1;
    while(i >= 0 && j >= i) {
        if(Aux[i] > A[j]) {
            int temp = Aux[i];
            for(int k = i;k < j;k++) 
                A[k] = A[k + 1];
            A[j] = temp;
            i--;
        }
        j--;
    }
}

void sortByRightShift(vector<int> &A, int m, int n, vector<int> &Aux) {
    int i = 0, j = m;
    while(i < m && j < m + n) {
        if(A[i] > Aux[j]) {
            int temp = Aux[j];
            for(int k = j;k > i;k--) 
                A[k] = A[k - 1];
            A[i] = temp;
            j++;
        }
        i++;
    }
}

// Function to merge two sorted subarrays using an auxiliary array of size min(m, n)
void mergeWithAux(vector<int> &A, int m, int n) {
    // Determine the smaller subarray and create the auxiliary array
    int auxLen = min(m, n);
    int totalLen = m + n;
    vector<int> Aux(auxLen);
    bool isLeft = true;

    if(m <= n) {
        for(int i = 0;i < m;i++) 
            Aux[i] = A[i];
    }
    else {
        for(int i = m;i < m + n;i++)
            Aux[i] = A[i];
        isLeft = false;
    }

    if(isLeft) {
        sortByLeftShift(A, m, n, Aux);
    }   
    else {
        sortByRightShift(A, m, n, Aux);
    }

}

int main() {
    int testcase, m, n;

    cin >> testcase;

    for (int t = 0; t < testcase; t++) {
        cout << "Testcase " << t + 1 << ":" << endl;

        cin >> m >> n;
        vector<int> A(m + n);

        // Input array containing both subarrays
        for (int i = 0; i < m + n; i++) {
            cin >> A[i];
        }

        // Merge two sorted subarrays using auxiliary array
        mergeWithAux(A, m, n);

        // Output the merged and sorted array
        for (int i = 0; i < m + n; i++) {
            cout << A[i] << " ";
        }
        cout << "\n---------------------------------------------------\n";
    }

    return 0;
}

