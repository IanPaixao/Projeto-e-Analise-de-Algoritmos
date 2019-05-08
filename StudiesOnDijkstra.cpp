#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
const int inf = 1 << 30;

// Abstraction of a graph

class Graph
{
private:
	int n;							// Number of vertices
	int** adj;						// Adjacency matrix
	int length;                     // Length of the Edge 
public:
	Graph(int size);				// Constructor
	~Graph();						// Destructor
	void addEdge(int x, int y, int z); 	// Add an edge the the graph
	void destroyEgde(int x, int y);
	bool isConnected(int x, int y);	// Check if two vertices are connected
	int Dijkstra(int A, int B);     // Dijkstra shortest path
  void DFS(int start, int end);	// Depth first search
};

// Constructor

Graph::Graph(int size)
{
	if (size < 2)				// The graph must have at least 2 vertices
	{
		n = 2;
	}
	else
	{
		n = size;
	}

	adj = new int*[n];			// Allocate memory for adjacency matrix

	for (int i = 0; i<n; ++i)
	{
		adj[i] = new int[n];	// Allocate memory for adjacency matrix
	}

	for (int i = 0; i<n; ++i)
	{
		for (int j = 0; j<n; ++j)
		{
			adj[i][j] = inf;		// Initialize the vertices to 0
		}
	}
}

// Destructor

Graph::~Graph()
{
	for (int i = 0; i<n; ++i)
	{
		delete[] adj[i];
	}
	delete[] adj;
}

// Add an edge to the graph

void Graph::addEdge(int x, int y, int z)
{
	adj[x][y] = adj[y][x] = z;
}

// Destroy an edge on the graph

void Graph::destroyEgde(int x, int y)
{
	adj[x][y] = adj[y][x] = inf;
}

// Check if two vertices are connected

bool Graph::isConnected(int x, int y)
{
	//return (adj[x - 1][y - 1] == 1);
	return ((adj[x][y] != 0) && (adj[y][x] != 0));
}

int Graph::Dijkstra(int A, int B) {
	vector<int> dist(n);
	vector<bool> vis(n);

	for (int i = 0; i < n; ++i) {
		dist[i] = inf;
	}
	dist[A] = 0;

	for (int i = 0; i < n; ++i) {
		int cur = -1;
		for (int j = 0; j < n; ++j) {
			if (vis[j]) continue;
			if (cur == -1 || dist[j] < dist[cur]) {
				cur = j;
			}
		}

		vis[cur] = true;
		for (int j = 0; j < n; ++j) {
				int path = dist[cur] + adj[cur][j];
			if (path < dist[j]) {
				dist[j] = path;
			}
		}
	}
	return dist[B];
}

void Graph::DFS(int start, int end)
{

	stack <int> s;	// Create a stack of ints
	bool* visited = new bool[n];	// Boolean array to represent which vertices we've visited
	long*  lengths = new long[n];

	for (int i = 0; i < n; ++i)	// Initialize all elements of visited to false
	{
		visited[i] = false;
		lengths[i] = 0;
	}

	s.push(start);	// Push the vertex onto the stack
	visited[start] = true;	// Mark this node as visited

	if (start == end)	// End the function if we're at our destination
	{
		return;
	}

	//cout << "Depth-first search starting from point: " << start << endl;

	while (!s.empty())	// While the stack is not empty
	{
		int k = s.top();	// Save the top element before popping it off
		s.pop();

		if (k == end)	// Break out of the loop if we've reached our destination
		{
			break;
		}

		//cout << k << " ";

		for (int i = 0; i < n; i++)	// For all adjacent vertices
		{
			if (isConnected(k, i) && !visited[i])	// If they're connected and we haven't visited it yet
			{
				s.push(i);	// Add it to our stack, and mark that we've visited it
				visited[i] = true;
				lengths[i] = lengths[k] + adj[k][i];
			}
		}
	}
	//cout << end << endl;
	cout << lengths[end] << " ";
	delete[] visited;	// De-allocate the visited array
}



int main()
{
Graph g(4);
g.addEdge(0, 1, 1);
g.addEdge(0, 2, 100);
g.addEdge(1, 2, 10);
g.addEdge(1, 3, 100);
g.addEdge(2, 3, 10);
g.addEdge(3, 0, 1000);
g.DFS(0, 3);
int result = g.Dijkstra(0, 3);
cout << result;

return 0;
}
