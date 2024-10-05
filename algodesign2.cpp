#include "bits/stdc++.h"
using namespace std;

vector<int> howSum(int target, vector<int> &numbers) {
    // Tabulation technique
    int n = numbers.size();
    vector<vector<int>> table(target + 1, vector<int>());

    /*
    Time Complexity - O(target * n)
    Space Complexity - O(target * n) in worst case
    */
    
    // Base Case
    // For sum 0 there exists an empty vector/array
    table[0] = {};

    /*
    For each index t of the table, the value at table[t] represents 
    a list of numbers that add up to the sum t, or an empty list if 
    no such combination exists.
    */

    // Fill up the table iteratively using tabulation   
    for(int t = 0;t <= target;t++) {
        if(t == 0 || !table[t].empty()) {
            for(int num : numbers) {
                if(t + num <= target) {
                    if(table[t + num].empty()) {  // Only update if not already filled
                        table[t + num] = table[t];  // Copy the combination from table[t]
                        table[t + num].push_back(num);  // Add the current number
                    }
                }
            }
        }
    }

    return table[target];

}

int main() {
    int testcase, n, target;

    cin >> testcase;

    for(int i = 0;i < testcase;i++) {
        cout << "Testcase " << i + 1 << ":" << endl;

        cin >> target >> n;
        vector<int> numbers(n);

        cout << "Target = " << target << endl;
        
        // Get the input arrayB
        for(int j = 0;j < n;j++) {
            cin >> numbers[j];
        }


        vector<int> res = howSum(target, numbers);
        // Call the howSum() function and if it is true then combination exists
        if(res.size() > 0) {
            cout << "Combination that adds up to target " << target << " is:\n"; 
            for(auto num : res) {
                cout << num << " ";
            }
        }
        else {
            cout << "No valid Combination exists for target " << target;
        }
        cout << endl;
        cout << "--------------------------------------------" << endl;
    }  
    return 0;
}


