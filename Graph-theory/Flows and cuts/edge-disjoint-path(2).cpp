/* 
Time Complexity: O(E*(V^3)) 
[For BFS it is O(V^2), if adjacency list representation is used, 
then Time Complexity would be O(E*(V^2))] 
*/

#include <bits/stdc++.h>

using namespace std;

//  http://www.geeksforgeeks.org/find-edge-disjoint-paths-two-vertices/
//  C++ program to find maximum number of edge disjoint paths

bool BFS (vector< vector<int> > &resiGraph, int src, int sink, int parent[]) {
	int V = resiGraph.size();
	bool visited[V];
	for (int i = 0; i < V; i++) {
		visited[i] = false;
	}
	queue<int> q;
	q.push(src);
	visited[src] = true;
	parent[src] = -1;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v = 0; v < V; v++) {
			if ((!visited[v]) && (resiGraph[u][v] > 0)) {
				q.push (v);
				visited[v] = true;
				parent[v] = u;
			}
		}
	}
	return (visited[sink] == true);
}

//Ford–Fulkerson
int findDisjointPaths(vector< vector<int> > &graph, int src, int sink) {
	int V = graph.size();
	vector< vector<int> > resiGraph;
	for (int i = 0; i < V; i++) {
		vector<int> temp;
		for (int j = 0; j < V; j++) {
			temp.push_back(graph[i][j]);
		}
		resiGraph.push_back(temp);
		temp.erase(temp.begin(), temp.end());
	}
	int *parent = new int[V];
	int max_flow = 0;
	while (BFS (resiGraph, src, sink, parent)) {
		int path_flow = INT_MAX;
		for (int v = sink; v != src; v = parent[v]) {
			int u = parent[v];
			path_flow = min (path_flow, resiGraph[u][v]);
		}
		for (int v = sink; v != src; v = parent[v]) {
			int u = parent[v];
			resiGraph[u][v] -= path_flow;
			resiGraph[v][u] += path_flow;
		}
		max_flow += path_flow;
	}
	return max_flow;
}
/*
0 1 1 1 0 0 0 0
0 0 1 0 0 1 0 0
0 0 0 1 0 0 1 0
0 0 0 0 0 0 0 0
0 0 1 0 0 0 0 1
0 1 0 0 0 0 0 1
0 0 0 0 0 1 0 1
0 0 0 0 0 0 0 0

answer:
2
*/
int main () {

	vector< vector<int> > graph(8,std::vector<int>(8,0));

	for(int i=0;i<8;i++) {
    for(int j=0;j<8;j++) {
      std::cin >> graph[i][j];
    }
  }
	int src = 0;
	int sink = 7;
	cout << "There can be Maximum " << findDisjointPaths(graph, src, sink);
  	cout << " Edge-Disjoint Paths from " << src << " to " << sink << " in the given graph." << endl;
	return 0;
}
