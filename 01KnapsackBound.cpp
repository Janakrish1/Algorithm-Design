#include "bits/stdc++.h"
using namespace std;

struct Sack {
    float p;  // profit
    float w;  // weight
    float r;  // profit/weight ratio
};

// Global variables to store the best solution found
float maxProfit = 0.0;
vector<bool> bestSet;


// Function to calculate if the node is promising based on the bound
pair<float, pair<float, bool>> promising(int i, float profit, float weight, float W, vector<Sack> &s) {
    if (weight >= W) {

        return {0, {0, false}};
    }

    // Calculate bound using the greedy method (fractional knapsack approach)
    float bound = profit;
    float totalWeight = weight;

    // Calculate the bound by adding items greedily
    while (i < s.size() && totalWeight + s[i].w <= W) {
        totalWeight += s[i].w;
        bound += s[i].p;
        i++;
    }

    // Add fractional part of the next item if we still have capacity
    if (i < s.size()) {
        bound += (W - totalWeight) * (s[i].p / s[i].w);
    }

    // If the bound is better than the current best profit, it's promising
    return {bound, {maxProfit, bound > maxProfit}};
}


// Recursive knapsack function with bound checking
void knapsackBound(int i, float profit, float weight, float W, vector<Sack> &s, vector<bool> &include) {
    if (weight <= W && profit > maxProfit) {
        // Found a better solution
        maxProfit = profit;
        bestSet = include;
        cout << "\nNow the current best = " << maxProfit << endl;
    }
    auto isValid = promising(i, profit, weight, W, s);
    if(isValid.second.second) {
      cout << "\nThis is promising because current bound is greater than the current best. Bound = " << isValid.first << " and Current Best = " << maxProfit;
    }
    else {
      cout << "\nThis is not promising because current bound is lesser than the current best. Current Best = " << maxProfit;
    }
    // If the node is promising, explore further
    if (i < s.size() && isValid.second.second) {
        // Include item i in the solution
        cout << "\nIncluded item " << i + 1 << " with profit " << s[i].p << " and weight " << s[i].w;
        include[i] = true;
        knapsackBound(i + 1, profit + s[i].p, weight + s[i].w, W, s, include);

        // Exclude item i from the solution
        include[i] = false;
        cout << "\n\nBacktracking here and excluded item " << i + 1;
        knapsackBound(i + 1, profit, weight, W, s, include);
    }
}



int main() {
    vector<Sack> s = {{20, 2, 10}, {30, 5, 6}, {35, 7, 5}, {12, 3, 4}, {3, 1, 3}};
    float W = 9; // Total knapsack capacity

    // Sort items based on profit/weight ratio
    sort(s.begin(), s.end(), [](const Sack &a, const Sack &b) {
        return a.r > b.r;
    });

    // Initialize variables
    vector<bool> include(s.size(), false);
    bestSet = vector<bool>(s.size(), false);

    // Call the knapsack function with bound checking
    cout << "Current Maximum Profit = 0" << endl;
    knapsackBound(0, 0.0, 0.0, W, s, include);

    // Output the maximum profit
    cout << "\nMax Profit = " << maxProfit << endl;

    return 0;
}
