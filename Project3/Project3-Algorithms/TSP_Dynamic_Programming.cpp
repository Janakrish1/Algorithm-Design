#include "../../bits/stdc++.h"
#include <filesystem>
#include <chrono>

using namespace std;
namespace fs = filesystem;

class Graph {
private:
    int N;
    vector<vector<long>> graph;
    vector<vector<long>> dp;
    vector<vector<int>> parent;  // Used to track the optimal path
    vector<int> optimalPath;
    long minTour = LONG_MAX;

public:
    Graph() : N(0) {}

    void clear() {
        minTour = LONG_MAX;
        N = 0;
        graph.clear();
        optimalPath.clear();
        dp.clear();
        parent.clear();
    }

    void setSize(int size) {
        N = size;
        graph.resize(N, vector<long>(N));
        dp.resize(N, vector<long>(1 << N, LONG_MAX));  
        parent.resize(N, vector<int>(1 << N, -1));    
    }

    void readInputs(const string& filename) {
        ifstream file(filename);
        string line, token;
        for (int i = 0; i < N; i++) {
            getline(file, line);
            stringstream stream(line);
            for (int j = 0; j < N && getline(stream, token, ','); j++) {
                if (i != j) {
                    long dist = stol(token);
                    if (dist > 0) {
                        graph[i][j] = dist;
                    }
                }
            }
        }
    }

    long findTourPath(int i, int mask) {
        if (mask == (1 << N) - 1) {  
            return graph[i][0] > 0 ? graph[i][0] : LONG_MAX;  
        }

        if (dp[i][mask] != LONG_MAX) {
            return dp[i][mask];
        }

        long ans = LONG_MAX;
        for (int j = 0; j < N; j++) {
            if ((mask & (1 << j)) == 0 && graph[i][j] > 0) {  
                long newTour = graph[i][j] + findTourPath(j, mask | (1 << j));
                if (newTour < ans) {
                    ans = newTour;
                    parent[i][mask] = j;  
                }
            }
        }

        dp[i][mask] = ans;
        return ans;
    }

    void getOptimalTourPath() {
        int mask = 1, i = 0;
        optimalPath.push_back(0); 
        while (parent[i][mask] != -1) {
            i = parent[i][mask];
            optimalPath.push_back(i);
            mask |= (1 << i);  
        }
        optimalPath.push_back(0); 
    }

    void printPath(vector<int> &pathNodes, int tour) {
        cout << "Sequence of Nodes - [";
        int i = 0;
        for(i = 0;i < N;i++) {
            cout << pathNodes[i] << ", ";
        }
        cout << pathNodes[i] << "]" << endl;
        cout << "Tour = " << tour << endl;
    }

    void dynamicProgramming() {
        minTour = findTourPath(0, 1);  // Start tour from city 0
        getOptimalTourPath();
        printPath(optimalPath, minTour);
    }
};

pair<string, int> trim(const string& filename) {
    string file;
    stringstream stream(filename);
    getline(stream, file, '/');
    getline(stream, file, '/');
    getline(stream, file, '/');

    string s;
    for (auto ch : file) {
        if (ch == 'n') break;
        s += ch;
    }

    int size = stoi(s);
    return {file, size};
}

void TravellingSalesmanProblem(const string& filename) {
    pair<string, int> data = trim(filename);
    cout << "Filename - " << data.first << endl;

    Graph G;
    G.setSize(data.second);
    G.readInputs(filename);
    G.dynamicProgramming();
    cout << endl;
}

int main() {
    string inputFolder = "Project3/Project3-Input-Files";

    for (const auto& entry : fs::directory_iterator(inputFolder)) {
        if (entry.path().extension() == ".csv") {
            string filename = entry.path().string();
            TravellingSalesmanProblem(filename);
        }
    }

    return 0;
}
