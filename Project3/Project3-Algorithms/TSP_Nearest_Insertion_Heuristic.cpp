#include "../../bits/stdc++.h"
#include <filesystem>
#include <chrono>

using namespace std;

namespace fs = filesystem;
using namespace chrono;

class Graph {
private:
    struct Pair {
        int vertex;
        double distance;
    };
    int N;
    vector<vector<Pair>> graph;

public:
    Graph() : N(0) {}

    void clear() {
        this->N = 0;
        graph.clear();
    }

    void setSize(int size) {
        N = size;
        graph.resize(N);
    }

    void readInputs(string filename) {
        string line, token;
        ifstream file(filename);

        for (int i = 0; i < N; i++) {
            getline(file, line);
            stringstream stream(line);

            for (int j = 0; j < N && getline(stream, token, ','); j++) {
                if (i != j) {
                    double dist = stod(token);
                    if (dist > 0) {
                        graph[i].push_back({j, dist});
                    }
                }
            }
        }
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

    void nearestInsertionAlgorithm() {
        vector<vector<double>> distances(N, vector<double>(N, LONG_MAX));
        
        for (int i = 0; i < N; i++) {
            for (auto& edge : graph[i]) {
                distances[i][edge.vertex] = edge.distance;
            }
        }

        double minDistance = LONG_MAX;
        int start = 0, end = 0;
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (distances[i][j] < minDistance) {
                    minDistance = distances[i][j];
                    start = i;
                    end = j;
                }
            }
        }

        vector<int> tour = {start, end};
        double totalDistance = distances[start][end];
        set<int> visited = {start, end};

        while (tour.size() < N) {
            int nearestNode = -1;
            double nearestDistance = LONG_MAX;

            for (int node = 0; node < N; node++) {
                if (visited.count(node) == 0) {
                    for (int tourNode : tour) {
                        if (distances[node][tourNode] < nearestDistance) {
                            nearestDistance = distances[node][tourNode];
                            nearestNode = node;
                        }
                    }
                }
            }

            int bestPosition = 0;
            double minIncrease = LONG_MAX;
            for (int i = 0; i < tour.size(); i++) {
                int nextNode = tour[(i + 1) % tour.size()];
                double increase = distances[tour[i]][nearestNode] + distances[nearestNode][nextNode] - distances[tour[i]][nextNode];

                if (increase < minIncrease) {
                    minIncrease = increase;
                    bestPosition = i + 1;
                }
            }

            tour.insert(tour.begin() + bestPosition, nearestNode);
            totalDistance += minIncrease;
            visited.insert(nearestNode);
        }

        totalDistance += distances[tour.back()][tour[0]];
        tour.push_back(tour[0]);

        printPath(tour, totalDistance);
    }
};

pair<string, int> trim(string filename) {
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

void TravellingSalesmanProblem(string filename) {
    pair<string, int> data = trim(filename);
    cout << "Filename - " << data.first << endl;

    Graph G;

    G.setSize(data.second);
    G.readInputs(filename);
    G.nearestInsertionAlgorithm();
    cout << endl;
}

int main() {
    string inputFolder = "Project3/Project3-Input-Files";

    for (const auto &entry : fs::directory_iterator(inputFolder)) {
        if (entry.path().extension() == ".csv") {
            string filename = entry.path().string();
            TravellingSalesmanProblem(filename);
        }
    }

    return 0;
}
