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
  vector<LinkedListNode*> graph;
  int MAX_SIZE;
  vector<double> shortestPath;
  vector<int> paths;

public:
  void clear() {
    edges.clear();
    MAX_SIZE = 0;
    graph.clear();
  }

  void setSize(int size) {
    MAX_SIZE = size;
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

  int getMinDistanceIndex(vector<int> &vis, vector<double> &dist) {
    int u = 0;
    double d = INT_MAX;

    for(int i = 0;i < MAX_SIZE;i++) {
      if(vis[i] && dist[i] < d) {
        d = dist[i];
        u = i;
      }
    }
    return u;
  }

  void findShortestPathUsingDijkstra(int src) {
    shortestPath.clear();
    paths.clear();
    shortestPath.resize(MAX_SIZE, INT_MAX);
    paths.resize(MAX_SIZE);
    vector<int> vis(MAX_SIZE, 0);

    for(int i = 0;i < MAX_SIZE;i++)
      paths[i] = i;

    
    shortestPath[src] = 0;
    vis[src] = 1;
    int cnt = 1;

    while(cnt > 0) {
      int u = getMinDistanceIndex(vis, shortestPath);
      double distance = shortestPath[u];
      vis[u] = 0;
      cnt--;

      LinkedListNode *curr = graph[u]->next;
      while(curr) {
        int d = curr->distance;
        int v = curr->data;
        if(d + distance < shortestPath[v]) {
          shortestPath[v] = d + distance;
          vis[v] = 1;
          paths[v] = u;
          cnt++;
        }
        curr = curr->next;
      }
    }
  }

  void printPath(int source, int dest) {
    cout << "\nDistance from " << source << " to " << dest << ": " << shortestPath[dest] << " feet" << endl;
    
    vector<int> path;
    while(dest != paths[dest]) {
      path.push_back(dest);
      dest = paths[dest];
    }
    
    cout << "Path: [" << source;
    for(int i = path.size() - 1;i >= 0;i--) {
      cout << ", " << path[i];
    }
    cout << "]" << endl;
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



void DijkstraUsingLinkedList(string filename, string testCaseFilename) {
  auto start = high_resolution_clock::now();
  Graph G;
  G.clear();

  G.readInputs(filename);
  
  G.createGraph();

  if(filename == testCaseFilename) {
    int source, dest;
    for(int testcase = 0;testcase < 3;testcase++) {
      cin >> source >> dest;
      G.findShortestPathUsingDijkstra(source);
      G.printPath(source, dest);
      cout << "-----------------------------------------------------------------------------------------------";
    }
  }

  G.findShortestPathUsingDijkstra(0);
  G.destroy();

  auto end = high_resolution_clock::now();

  auto duration = duration_cast<microseconds>(end - start);
  double time_taken = duration.count() / 1e6; 
  time_performance.push_back({filename, time_taken});
}

void exportTimePerformance() {
  ofstream outFile("dijkstra_linkedlist_time.csv");
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
      DijkstraUsingLinkedList(filename, testCaseFilename);
    }
  }

  // exportTimePerformance();

  return 0;
}