#include "bits/stdc++.h"
#include <filesystem>

using namespace std;

namespace fs = filesystem;

struct Edge {
  int node1;
  int node2;
  double distance;
};

struct Pair {
  int node;
  double distance;
};

class Graph {
private:
  vector<Edge> edges;
  int MAX_SIZE;
  vector<vector<double>> graph;
  vector<vector<double>> shortestPath;
  vector<vector<int>> paths;

public:
  void clear() {
    edges.clear();
    
    MAX_SIZE = 0;
  }

  int readInputs(string filename) {
    int mx = 0;
    ifstream file(filename);
    string line, token;

    getline(file, line);

    while(getline(file, line)) {
      stringstream stream(line);
      
      getline(stream, token, ',');
      int u = stoi(token);

      getline(stream, token, ',');
      int v = stoi(token);

      getline(stream, token, ',');
      double dist = stod(token);

      mx = max({mx, u, v});
      edges.push_back({u, v, dist});
    }
    MAX_SIZE = mx + 1;
    return mx;
  }

  void createGraph() {
    graph.resize(MAX_SIZE, vector<double> (MAX_SIZE, 0));
    for(auto &e : edges) {
      int u = e.node1;
      int v = e.node2;
      double dist = e.distance;
      graph[u][v] = dist;
    }
  }

  void findShortestPathUsingFloyd() {
    shortestPath.resize(MAX_SIZE, vector<double> (MAX_SIZE));
    paths.resize(MAX_SIZE, vector<int> (MAX_SIZE, -1));
    
    for(int i = 0;i < MAX_SIZE;i++) {
      for(int j = 0;j < MAX_SIZE;j++) {
        if(i == j)
          shortestPath[i][i] = 0;
        else if(graph[i][j] > 0) {
          shortestPath[i][j] = graph[i][j];
          paths[i][j] = j;
        }
        else 
          shortestPath[i][j] = 1e9;
      }
    }

    for(int k = 0;k < MAX_SIZE;k++) {
      for(int i = 0;i < MAX_SIZE;i++) {
        for(int j = 0;j < MAX_SIZE;j++) {
          if(shortestPath[i][k] + shortestPath[k][j] < shortestPath[i][j]) {
            shortestPath[i][j] = shortestPath[i][k] + shortestPath[k][j];
            paths[i][j] = paths[i][k];
          }
        }
      }
    }
  }

  void printPath(int src, int dest) {
    if(paths[src][dest] == -1) {
      cout << "There is no path between " << src << " and " << dest << endl;
      return;
    }
    cout << "\nDistance from " << src << " to " << dest << ": " << shortestPath[src][dest] << " feet" << endl;
    
    vector<int> path = {src};

    while(src != dest) {
      src = paths[src][dest];
      path.push_back(src);
    }
    
    cout << "Path: [";
    int n = path.size();
    for(int i = 0;i < path.size() - 1;i++) {
      cout << path[i] << ", ";
    }
    cout << path[n - 1] << "]" << endl;
  }
};



void FloydUsingMatrix(string filename, string testCaseFilename) {
  Graph G;

  G.readInputs(filename);
  
  G.createGraph();

  if(filename == testCaseFilename) {
    int source, dest;
    for(int testcase = 0;testcase < 3;testcase++) {
      cin >> source >> dest;
      G.findShortestPathUsingFloyd();
      G.printPath(source, dest);
      cout << "-----------------------------------------------------------------------------------------------";
    }
  }

  G.findShortestPathUsingFloyd();
}

int main() {
  

  string inputFolder = "Project2_Input_File";
  string testCaseFilename = "Project2_Input_File/Project2_Input_File4.csv";
  
  for(const auto &entry : fs::directory_iterator(inputFolder)) {
    if(entry.path().extension() == ".csv") {
      string filename = entry.path().string();
      if(filename == testCaseFilename)
      FloydUsingMatrix(filename, testCaseFilename);
    }
  }

  return 0;
}