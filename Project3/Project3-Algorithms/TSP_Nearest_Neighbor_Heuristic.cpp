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

        for(int i = 0;i < N;i++) {
            getline(file, line);
            stringstream stream(line);

            for(int j = 0;j < N && getline(stream, token, ',');j++) {
                if(i != j) {
                    double dist = stod(token);
                    if(dist > 0) {
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

    void nearestNeighborAlgorithm() {
        int vertex = 0;
        int vis = 0;
        double tour = 0;
        int cnt = 0;
        vector<int> pathNodes;
        while(vis != ((1 << N) - 1)) {
            vis = vis | (1 << vertex);

            int mnVertex = vertex;
            double mnDist = LONG_MAX;
            
            pathNodes.push_back(vertex);

            auto row = graph[vertex];
            int size = row.size();

            for(int i = 0; i < size;i++) {
                int v = row[i].vertex;
                double d = row[i].distance;

                int mask = (1 << v);
                // Not visited
                if(!(mask & vis) && mnDist > d) { 
                    mnDist = d;
                    mnVertex = v;
                }
            }

            if(mnVertex == vertex) {
                pathNodes.push_back(0);
                tour += row[0].distance;
            }
            else {
                tour += mnDist;
                vertex = mnVertex;
            }
        }

        printPath(pathNodes, tour);
    }

};

pair<string, int> trim(string filename) {
    string file;
    stringstream stream(filename);
    getline(stream, file, '/');
    getline(stream, file, '/');
    getline(stream, file, '/');

    string s;
    for(auto ch : file) {
        if(ch == 'n') break;
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
    G.nearestNeighborAlgorithm();
    cout << endl;
}

int main() {
  
  string inputFolder = "Project3/Project3-Input-Files";
  
  for(const auto &entry : fs::directory_iterator(inputFolder)) {
    if(entry.path().extension() == ".csv") {
      string filename = entry.path().string();
      TravellingSalesmanProblem(filename);
    }
  }

  return 0;
}