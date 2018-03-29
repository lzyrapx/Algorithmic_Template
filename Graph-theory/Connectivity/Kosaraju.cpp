
/*
Kosaraju’s algorithm1----
is an efficient method for finding the strongly connected
components of a directed graph. The algorithm performs two depth-first searches:
the first search constructs a list of nodes according to the structure of the graph,
and the second search forms the strongly connected components.
*/

/*
The time complexity of the algorithm is O(n + m), because the algorithm performs two depth-first searches.
*/
#include <bits/stdc++.h>
using namespace std;
#define PB push_back
const int MXN = 1e6;

// Scc: Strongly Connected Components

struct Scc{
  int n, nScc, vst[MXN], bln[MXN];
  vector<int> E[MXN], rE[MXN], vec;
  void init(int _n){
    n = _n;
    for (int i=0; i<n; i++){
      E[i].clear();
      rE[i].clear();
    }
  }
  void add_edge(int u, int v){
    // u begin from 0
    // v begin from 0
    E[u].PB(v);
    rE[v].PB(u);
  }
  void DFS(int u){
    // std::cout << "DFS" << '\n';
    vst[u]=1;
    for (auto v : E[u])
      if (!vst[v]) DFS(v);
    vec.PB(u); //Each node will be added to the list after it has been processed.
    // std::cout << "u=" << u+1 << '\n';
  }
  void rDFS(int u){
    vst[u] = 1;
    bln[u] = nScc;
    for (auto v : rE[u])
      if (!vst[v]) rDFS(v);
  }
  void solve(){
    // std::cout << "solve" << '\n';
    nScc = 0;
    vec.clear();
    for (int i=0; i<n; i++) vst[i] = 0;
    for (int i=0; i<n; i++)
      if (!vst[i]) DFS(i);

    // the algorithm reverses every edge in the graph. This guarantees-
	// that during the second search, we will always find strongly connected components that do not have extra nodes.
  
    reverse(vec.begin(),vec.end());
    for (int i=0; i<n; i++) vst[i] = 0;
    for (auto v : vec){
      if (!vst[v]){
        rDFS(v);
        nScc++;
      }
    }
  }

}solver;

/*
1 2
2 1
1 2
5 4
3 2
6 5
3 7
6 3
7 6
2 5

answer:
4
*/
int main()
{
    solver.init(7);
    for(int i=1;i<=10;i++) {
      int u,v;
      std::cin >> u >> v;
      u--;v--;
      solver.add_edge(u,v);
    }
    solver.solve();
    std::cout << solver.nScc << '\n';
}
