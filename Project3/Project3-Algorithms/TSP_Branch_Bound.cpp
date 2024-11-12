#include "../../bits/stdc++.h"
#include <filesystem>
#include <chrono>

using namespace std;
namespace fs = filesystem;
using namespace chrono;

struct Node {
    vector<int> path;   // stores the cities visited so far
    int level;          // depth of node in the tree (number of cities visited)
    long bound;         // lower bound of the path from this node
    long cost;          // total cost of the path so far
};

class Graph {
private:
    int N;
    vector<vector<long>> graph;
    vector<int> pathNodes;
    long minTour;

public:
    Graph() : N(0), minTour(LONG_MAX) {}

    void clear() {
        this->minTour = LONG_MAX;
        this->N = 0;
        graph.clear();
        pathNodes.clear();
    }

    void setSize(int size) {
        N = size;
        graph.resize(N, vector<long>(N, LONG_MAX));
    }

    void readInputs(const string& filename) {
        string line, token;
        ifstream file(filename);

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

    long calculateBound(Node &node) {
        long bound = node.cost;
        vector<bool> visited(N, false);
        for (int i : node.path) visited[i] = true;

        for (int i = 0; i < N; ++i) {
            if (!visited[i]) {
                long minCost = LONG_MAX;
                for (int j = 0; j < N; ++j) {
                    if (!visited[j] && i != j && graph[i][j] < minCost) {
                        minCost = graph[i][j];
                    }
                }
                bound += minCost;
            }
        }
        return bound;
    }

    struct Comp {
        bool operator()(const Node &a, const Node &b) {
            return a.bound > b.bound;
        }
    };

    void printPath(vector<int> &pathNodes, int tour) {
        cout << "Sequence of Nodes - [";
        int i = 0;
        for(i = 0;i < N;i++) {
            cout << pathNodes[i] << ", ";
        }
        cout << pathNodes[i] << "]" << endl;
        cout << "Tour = " << tour << endl;
    }

    void branchAndBound() {
        minTour = LONG_MAX;
        pathNodes.clear();
        priority_queue<Node, vector<Node>, Comp> pq;

        Node root;
        root.level = 0;
        root.cost = 0;
        root.path.push_back(0);  // starting city is 0
        root.bound = calculateBound(root);

        pq.push(root);

        while (!pq.empty()) {
            Node node = pq.top();
            pq.pop();

            if (node.bound < minTour) {
                for (int i = 1; i < N; ++i) {
                    if (find(node.path.begin(), node.path.end(), i) == node.path.end()) {
                        Node child = node;
                        child.path.push_back(i);
                        child.cost += graph[node.path.back()][i];

                        if (child.level == N - 2) {
                            child.path.push_back(0);
                            child.cost += graph[i][0];
                            if (child.cost < minTour) {
                                minTour = child.cost;
                                pathNodes = child.path;
                            }
                        } else {
                            child.level++;
                            child.bound = calculateBound(child);
                            if (child.bound < minTour) {
                                pq.push(child);
                            }
                        }
                    }
                }
            }
        }

        printPath(pathNodes, minTour);
    }
};

pair<string, int> trim(const string& filename) {
    string file;
    stringstream stream(filename);
    getline(stream, file, '/');
    getline(stream, file, '/');
    getline(stream, file, '/');

    string s;
    for (char ch : file) {
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
    G.branchAndBound();
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
