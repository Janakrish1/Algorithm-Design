#include "bits/stdc++.h"
using namespace std;

int binarySearch(vector<int> &A, int low, int high, int target) {
    while(low <= high) {
        int mid = (low + high) >> 1;
        if(target > A[mid])
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low;
}

void insert(vector<int> &A, int start, int pos, int temp) {
    for(int i = start;i < pos;i++) {
        A[i] = A[i + 1];
    }
    A[pos] = temp;
}

void sortWithoutAux(vector<int> &A, int m, int n) {
    // Base Case
    // If one subarray is empty other would be sorted so return A
    if(m == 0 || n == 0) 
        return;
 
    int totalLen = m + n;
    int start = 0;
    int i = 0;

    // Iterate until i reaches m
    while(i < m) {
        // Compare ith element always with the first element of the second subarray
        if(A[i] > A[m]) {
            // Find the position for which ith element should be inserted using binary search
            int pos = binarySearch(A, m, totalLen - 1, A[i]);
            // Keep a temp variable
            int curr = A[m];
            // Insert the ith element to it's correct position
            insert(A, m, pos - 1, A[i]);
            A[i] = curr;
        }
        i++;
    }
}

int main() {
    int testcase, m, n;

    cin >> testcase;

    for(int t = 0;t < testcase;t++) {
        cout << "Testcase " << t + 1 << ":" << endl;

        cin >> m >> n;
        vector<int> A(m + n);
        
        // Get the input arrayB
        for(int i = 0;i < m + n;i++) {
            cin >> A[i];
        }

        sortWithoutAux(A, m, n);


        for(int i = 0;i < m + n;i++) {
            cout << A[i] << " ";
        }
        cout << "\n---------------------------------------------------\n";
    }  
    return 0;
}