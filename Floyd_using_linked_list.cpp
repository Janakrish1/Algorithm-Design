#include "bits/stdc++.h"
#include <filesystem>
#include <chrono>

using namespace std;

namespace fs = filesystem;

using namespace chrono;
vector<pair<string, double>> time_performance;

struct LinkedListNode {
  int data;
  double distance;
  LinkedListNode* next;

  LinkedListNode(int data, double distance) {
    this->data = data;
    this->distance = distance;
    this->next = NULL;
  }

  LinkedListNode(int data) {
    this->data = data;
    this->next = NULL;
  }
};

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
  vector<LinkedListNode*> graph;
  vector<vector<double>> shortestPath;
  vector<vector<int>> paths;

public:
  void clear() {
    edges.clear();
    graph.clear();
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

  void initNodes() {
    for(int i = 0;i < MAX_SIZE;i++) {
      LinkedListNode *newNode = new LinkedListNode(i);
      graph[i] = newNode;
    }
  }

  void addEdge(int u, int v, double dist) {
    LinkedListNode *newNode = new LinkedListNode(v, dist);
    LinkedListNode *temp = graph[u]->next;
    graph[u]->next = newNode;
    newNode->next = temp;
  }

  void createGraph() {
    graph.resize(MAX_SIZE, NULL);
    initNodes();
    for(auto &e : edges) {
      int u = e.node1;
      int v = e.node2;
      double dist = e.distance;
      addEdge(u, v, dist);
    }
  }

  void findShortestPathUsingFloyd() {
    shortestPath.resize(MAX_SIZE, vector<double> (MAX_SIZE, 1e9));
    paths.resize(MAX_SIZE, vector<int> (MAX_SIZE, -1));
    
    for(int i = 0;i < MAX_SIZE;i++) {
      shortestPath[i][i] = 0;
      int u = i;
      LinkedListNode* curr = graph[i]->next;

      while(curr) {
        int v = curr->data;
        double d = curr->distance;
        shortestPath[u][v] = d;
        paths[u][v] = v;
        curr = curr->next;
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

  void destroy() {
    for (int i = 0; i < MAX_SIZE; i++) {
        LinkedListNode* curr = graph[i];
        while (curr != NULL) {
            LinkedListNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
    graph.clear();
  }
};



void FloydUsingLinkedList(string filename, string testCaseFilename) {
  auto start = high_resolution_clock::now();
  
  Graph G;

  G.clear();

  G.readInputs(filename);
  
  G.createGraph();

  // if(filename == testCaseFilename) {
  //   int source, dest;
  //   for(int testcase = 0;testcase < 3;testcase++) {
  //     cin >> source >> dest;
  //     G.findShortestPathUsingFloyd();
  //     G.printPath(source, dest);
  //     cout << "-----------------------------------------------------------------------------------------------";
  //   }
  // }

  G.findShortestPathUsingFloyd();
  G.destroy();

  auto end = high_resolution_clock::now();

  auto duration = duration_cast<microseconds>(end - start);
  double time_taken = duration.count() / 1e6; 
  time_performance.push_back({filename, time_taken});
}

void exportTimePerformance() {
  ofstream outFile("floyd_linkedlist_time.csv");
  outFile << "Filename,TimeTaken(s)" << endl;
  for(auto &[filename, time] : time_performance) {
    stringstream ss(filename);
    string file;
    getline(ss, file, '/');
    getline(ss, file, '/');
    outFile << file << "," << time << endl;
  }
}

int main() {
  

  string inputFolder = "Project2_Input_File";
  string testCaseFilename = "Project2_Input_File/Project2_Input_File4.csv";
  
  for(const auto &entry : fs::directory_iterator(inputFolder)) {
    if(entry.path().extension() == ".csv") {
      string filename = entry.path().string();
      FloydUsingLinkedList(filename, testCaseFilename);
    }
  }

  exportTimePerformance();

  return 0;
}