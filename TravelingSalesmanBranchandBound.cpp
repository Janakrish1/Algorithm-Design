// C++ program to solve Traveling Salesman Problem 
// using Branch and Bound.
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>
#include <climits>
#include <chrono> 
#include <fstream>
#include <iomanip>
using namespace std::chrono;
using namespace std;

int N;
// Sentinal value for representing infinity
#define INF INT_MAX

vector<int> solution_list; 

// State Space Tree nodes
struct Node
{
	// stores edges of state space tree
	// helps in tracing path when answer is found
	vector<pair<int, int>> path;

	// stores the reduced matrix
	// int reducedMatrix[N][N];
	vector<vector<int>> reducedMatrix;

	// stores the lower bound
	int cost;

	//stores current city number
	int vertex;

	// stores number of cities visited so far
	int level;
};

// Function to allocate a new node (i, j) corresponds to visiting
// city j from city i
Node* newNode(vector<vector<int>>& parentMatrix, vector<pair<int, int>> const &path,
			int level, int i, int j)
{
	Node* node = new Node;

	// stores ancestors edges of state space tree
	node->path = path;
	// skip for root node
	if (level != 0)
		// add current edge to path
		node->path.push_back(make_pair(i, j));
	
	// copy data from parent node to current node
	// memcpy(node->reducedMatrix, parentMatrix,
	// 	sizeof node->reducedMatrix);
	node->reducedMatrix = parentMatrix;
	
	// Change all entries of row i and column j to infinity
	// skip for root node
	for (int k = 0; level != 0 && k < N; k++)
	{
		// set outgoing edges for city i to infinity
		node->reducedMatrix[i][k] = INF;

		// set incoming edges to city j to infinity
		node->reducedMatrix[k][j] = INF;
	}
	
	// Set (j, 0) to infinity
	// here start node is 0
	node->reducedMatrix[j].at(0) = INF;

	// set number of cities visited so far
	node->level = level;

	// assign current city number
	node->vertex = j;

	// return node
	return node;
}

// Function to reduce each row in such a way that
// there must be at least one zero in each row
void rowReduction(vector<vector<int>>& reducedMatrix, vector<int>& row)
{
	for (int i=0; i<N; i++)
		row.push_back(INF);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (reducedMatrix[i][j] < row[i])
				row.at(i) = reducedMatrix[i][j];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (reducedMatrix[i][j] != INF && row[i] != INF)
				reducedMatrix[i][j] -= row[i];
}

// Function to reduce each column in such a way that
// there must be at least one zero in each column
void columnReduction(vector<vector<int>>& reducedMatrix, vector<int>& col)
{
	for (int i=0; i<N; i++)
		col.push_back(INF);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (reducedMatrix[i][j] < col[j])
				col.at(j) = reducedMatrix[i][j];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (reducedMatrix[i][j] != INF && col[j] != INF)
				reducedMatrix[i][j] -= col[j];
}

// Function to get the lower bound on
// on the path starting at current min node
int calculateCost(vector<vector<int>>& reducedMatrix)
{
	int cost = 0;

	vector<int> row;
	rowReduction(reducedMatrix, row);

	vector<int> col;
	columnReduction(reducedMatrix, col);

	for (int i = 0; i < N; i++)
		cost += (row[i] != INT_MAX) ? row[i] : 0,
			cost += (col[i] != INT_MAX) ? col[i] : 0;

	return cost;
}

// print list of cities visited following least cost
void printPath(vector<pair<int, int>> const &list)
{
    cout << "\nTravelling Salesperson Path:\n";
	for (int i = 0; i < list.size(); i++)
		cout << list[i].first << " - " << list[i].second << endl;
}

// Comparison object to be used to order the heap
struct comp {
	bool operator()(const Node* lhs, const Node* rhs) const
	{
		return lhs->cost > rhs->cost;
	}
};

// Function to solve Traveling Salesman Problem using Branch and Bound
int solve(vector<vector<int>>&  costMatrix)
{
	// Create a priority queue to store live nodes of search tree;
	priority_queue<Node*, std::vector<Node*>, comp> pq;

	vector<pair<int, int>> v;
	
	// create a root node and calculate its cost
	// The TSP starts from first city i.e. node 0
	Node* root = newNode(costMatrix, v, 0, -1, 0);
	
	// get the lower bound of the path starting at node 0
	root->cost = calculateCost(root->reducedMatrix);

    cout << "Initial Bound - " << root->cost << endl;
	// Add root to list of live nodes;
	pq.push(root);

	// Finds a live node with least cost, add its children to list of
	// live nodes and finally deletes it from the list
	while (!pq.empty())
	{
		// Find a live node with least estimated cost
		Node* min = pq.top();

		// The found node is deleted from the list of live nodes
		pq.pop();

		// i stores current city number
		int i = min->vertex;
        cout << "\nCurrent Vertex - " << i << endl; 
        cout << "Compute Bound to be " << min->cost << endl;       

		// if all cities are visited
		if (min->level == N - 1)
		{
			// return to starting city
			min->path.push_back(make_pair(i, 0));

			// print list of cities visited;
			printPath(min->path);

			// return optimal cost
			return min->cost;
		}

		// do for each child of min
		// (i, j) forms an edge in space tree
		for (int j = 0; j < N; j++)
		{
			if (min->reducedMatrix[i][j] != INF)
			{

				// create a child node and calculate its cost
				Node* child = newNode(min->reducedMatrix, min->path,
					min->level + 1, i, j);

				/* Cost of the child =
					cost of parent node +
					cost of the edge(i, j) +
					lower bound of the path starting at node j
				*/
				child->cost = min->cost + min->reducedMatrix[i][j]
							+ calculateCost(child->reducedMatrix);

                // cout << "Vertex - " << j << " \nCompute Bound to be " << child->cost << endl;
				// Add child to list of live nodes
				pq.push(child);
			}
		}

		// free node as we have already stored edges (i, j) in vector.
		// So no need for parent node while printing solution.
		delete min;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	
	std::cin >> N;

	vector<vector<int>> costMatrix(N, vector<int>(N));

	for (size_t i = 0; i < N; i++){
		for (size_t j = 0; j < N; j++){
			if (costMatrix[i][j] == -1){
				costMatrix[i][j] = INF;
			}
			std::cin >> costMatrix[i][j];
		}
	}

	auto start = high_resolution_clock::now();
	int cost = solve(costMatrix);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start);
	
    cout << "Minimum Tour = " << cost;
	

	return 0;
}


