#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

/* C/C++ program for solution of Hamiltonian Cycle problem using backtracking */
/*
Hamiltonian Path in an undirected graph is a path that visits each vertex exactly once.
A Hamiltonian cycle (or Hamiltonian circuit) is a Hamiltonian Path such that there is an
edge (in graph) from the last vertex to the first vertex of the Hamiltonian Path
*/

#define V 5 // num of vertices

int path[V];
bool isSafe(int v, bool graph[V][V], int path[], int pos) {
  if(graph[path[pos - 1]][v] == 0) return false;
  for(int i = 0; i < pos; i++) {
    if(path[i] == v) {
      return false;
    }
  }
  return true;
}
bool dfs(bool graph[V][V], int path[], int pos) {
  if(pos == V) {
    if(graph[path[V - 1]][path[0]] == 1) {
      return true;
    }
    else {
      return false;
    }
  }
  for(int v = 1; v < V; v++) {
    if(isSafe(v, graph, path, pos)) {
      path[pos] = v;
      if(dfs(graph, path, pos + 1) == true) {
        return true;
        path[pos] = -1;
      }
    }
  }
  return false;
}
void printSolution(int path[]) {
  printf(
      "Solution Exists:"
      "Hamiltonian Cycle: \n");
  for (int i = 0; i < V; i++) printf(" %d ", path[i]);
  printf(" %d\n", path[0]);
}
void hamitltonCycle(bool graph[V][V]) {
  for(int i = 0; i < V; i++) {
    path[i] = -1;
  }
  path[0] = 0;
  if(!dfs(graph, path, 1)) {
    std::cout << "No solutions" << '\n';
  }
  printSolution(path);
}

int main(int argc, char const *argv[]) {
  bool graph1[V][V] = {{0, 1, 0, 1, 0},
                      {1, 0, 1, 1, 1},
                      {0, 1, 0, 0, 1},
                      {1, 1, 0, 0, 1},
                      {0, 1, 1, 1, 0},
                     };
                     /*
                     Let us create the following graph
                           (0)--(1)--(2)
                            |   / \   |
                            |  /   \  |
                            | /     \ |
                           (3)-------(4)
                     */
  hamitltonCycle(graph1);
  return 0;
}
