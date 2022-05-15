#include <bits/stdc++.h>
using namespace std;

int graph_adj[10][10];
int n;
/*
 Find articulation point using DFS
 adj[]       Adjacency List representation of the graph
 u           The vertex to be visited next
 visited[]   keeps track of visited vertices
 disc[]      Stores discovery times of visited vertices
 low[]       Minimum node reachable from backedge.
 parent      Stores the parent vertex in DFS tree
 is_articulation_point[]      Stores articulation points
*/
void __find_articulation_point(vector<int> adj[], int u, bool visited[],
			int disc[], int low[], int& time, int parent,
			bool is_articulation_point[])
{
	// Count of children in DFS Tree
	int children = 0;

	// Mark the current node as visited
	visited[u] = true;

	// Initialize discovery time and low value
	disc[u] = low[u] = ++time;

	// Go through all vertices adjacent to this
	for (auto v : adj[u]) {
		if (!visited[v]) {
			children++;
			__find_articulation_point(adj, v, visited, disc, low, time, u, is_articulation_point);

			/* Check if the subtree rooted with v has
			   a connection to one of the ancestors of u
			*/
			low[u] = min(low[u], low[v]);

			/* If u is not root and low value of one of
			   its child is more than discovery value of u.
			*/
			if (parent != -1 && low[v] >= disc[u])
				is_articulation_point[u] = true;
		}

		// Update low value of u for parent function calls.
		else if (v != parent)
			low[u] = min(low[u], disc[v]);
	}

	// If u is root of DFS tree and has two or more children.
	if (parent == -1 && children > 1)
		is_articulation_point[u] = true;
}

void find_articulation_point(vector<int> adj[], int n)
{
	int disc[n] = { 0 };
	int low[n];
	bool visited[n] = { false };
	bool is_articulation_point[n] = { false };
	int time = 0, par = -1;

	for (int u = 0; u < n; u++)
		if (!visited[u])
			__find_articulation_point(adj, u, visited, disc, low,
				time, par, is_articulation_point);

	// Printing the Articulation points.
	for (int u = 0; u < n; u++)
		if (is_articulation_point[u] == true)
			cout << u << " ";
}

// Utility function to add an edge
void add_edge(vector<int> adj[], int u, int v)
{
    adj[u].push_back(v);
}

int main()
{
    cout << "Enter number of vertices \n";
    cin >> n;
    vector<int> adj[n];
    for (int i = 0; i < n; i++)
    {
       /* Get the adjacency Matrix */
        for(int j = 0; j< n; j++) {
            cout << "graph_adj["<<i<<"]"<<"["<<j<<"]  ";
            cin >> graph_adj[i][j];
            if(graph_adj[i][j] !=0 && graph_adj[i][j] !=1) {
                cout << "Only 0/1 values are allowed";
                exit(0);
            }
            /* For undirected graph a[i][j] equals to a[j][i] */
            if (graph_adj[j][i] == 0)
                graph_adj[j][i] = graph_adj[i][j];
            if(graph_adj[i][i] !=0) {
               cout << "a[i][i] should be always equal to 0";
               exit(0);
            }
            if ((graph_adj[i][j] != graph_adj[j][i])) {
                cout << "Please enter Undirected graph!!!. a[i][j] should be equal to a[j][i]";
                exit(0);
            }
        if (graph_adj[i][j] != 0)
            add_edge(adj, i, j);
        }
        cout<<endl;
    }
    cout << "Articulation points in the graph are:\n";
    find_articulation_point(adj, n);
    cout<<endl;
    return 0;
}
