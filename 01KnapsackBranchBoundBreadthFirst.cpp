#include "bits/stdc++.h"
using namespace std;

struct Sack {
    float p;  // profit
    float w;  // weight
    float r;  // profit/weight ratio
};

struct Data {
    int level;
    float p;
    float w;
    float bound;
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

class Cmp {
public:
    bool operator()(const Data &a, const Data &b) {
        return a.p < b.p;
    }
};


void knapsackBoundBreadthFirstSearch(int i, float profit, float weight, float W, vector<Sack> &s, vector<bool> &include) {
    priority_queue<Data, vector<Data>, Cmp> maxHeap;
    auto node = promising(0, 0, 0, W, s);
    float bound = node.first;
    maxHeap.push({-1, 0, 0, bound});

    while(!maxHeap.empty()) {
        auto top = maxHeap.top();
        maxHeap.pop();

        float bound = top.bound;
        float currW = top.w;
        float currP = top.p;
        int i = top.level;

        if(bound > maxProfit) {
            // Include item
            int j = i + 1;
            float w = currW + s[j].w;
            float p = currP + s[j].p;
            cout << "\nIncluded item " << j + 1 << " with profit " << s[j].p << " and weight " << s[j].w;
            auto isValid = promising(j, p, w, W, s);

            if(w <= W && p > maxProfit) {
                maxProfit = p;
                cout << "\nNow the current best = " << maxProfit << endl;
            }

            if(isValid.second.second) {
                cout << "\nThis is promising because current bound is greater than the current best. Bound = " << isValid.first << " and Current Best = " << maxProfit;
                maxHeap.push({j, p, w, isValid.first});
            }
            else {
                cout << "\nThis is not promising because current bound is lesser than the current best. Current Best = " << maxProfit;
            }   

            // Exclude item
            w = currW;
            p = currP;
            cout << "\n\nExcluded item " << j + 1 << endl;
            isValid = promising(j + 1, p, w, W, s);

            if(isValid.second.second) {
                maxHeap.push({j, p, w, isValid.first});
            }
        }
    }
}



int main() {
    vector<Sack> s = {{20, 2, 10}, {30, 5, 6}, {35, 7, 5}, {12, 3, 4}, {3, 1, 3}};
    float W = 13; // Total knapsack capacity

    // Sort items based on profit/weight ratio
    sort(s.begin(), s.end(), [](const Sack &a, const Sack &b) {
        return a.r > b.r;
    });

    // Initialize variables
    vector<bool> include(s.size(), false);
    bestSet = vector<bool>(s.size(), false);

    // Call the knapsack function with bound checking
    cout << "Current Maximum Profit = 0" << endl;
    knapsackBoundBreadthFirstSearch(0, 0.0, 0.0, W, s, include);

    // Output the maximum profit
    cout << "\nMax Profit = " << maxProfit << endl;

    return 0;
}