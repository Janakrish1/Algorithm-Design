#include "bits/stdc++.h"
using namespace std;

// Function to merge two sorted subarrays using an auxiliary array
void mergeWithAux(vector<int> &A, int m, int n) {
    // Determine the smaller subarray and create the auxiliary array
    bool auxFromFirst = m <= n;
    int auxLen = min(m, n);

    vector<int> Aux(auxLen);

    // Copy elements into the auxiliary array
    if (auxFromFirst) {
        // Copy the first m elements into the auxiliary array
        for (int i = 0; i < auxLen; i++) {
            Aux[i] = A[i];
        }
    } else {
        // Copy the last n elements into the auxiliary array
        for (int i = 0; i < auxLen; i++) {
            Aux[i] = A[m + i];
        }
    }

    // i is pointer for the non-aux part (larger subarray)
    // j is pointer for the auxiliary array
    // k is the pointer to merge elements back into the original array
    int i = auxFromFirst ? m : 0;  // Start of the larger subarray
    int j = 0;                     // Pointer for auxiliary array
    int k = 0;                     // Pointer to merge elements back

    // Merge the two subarrays
    while (i < m + n && j < auxLen) {
        if (auxFromFirst) {
            // Merging auxiliary array with the second subarray
            if (Aux[j] <= A[m + k]) {
                A[k++] = Aux[j++];
            } else {
                A[k++] = A[m + k];
            }
        } else {
            // Merging first subarray with auxiliary array
            if (A[i] <= Aux[j]) {
                A[k++] = A[i++];
            } else {
                A[k++] = Aux[j++];
            }
        }
    }

    // If there are remaining elements in the auxiliary array
    while (j < auxLen) {
        A[k++] = Aux[j++];
    }

    // If there are remaining elements in the larger subarray
    while (i < m + n) {
        A[k++] = A[i++];
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
