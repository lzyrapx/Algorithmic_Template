
#include <bits/stdc++.h>
using namespace std;

class Gragh {
public:
  Gragh(int num_nodes):adj_list(num_nodes),dist(num_nodes,-1){}

  void add_edge(int start, int end);
  vector<vector<int>>adj_list;
  vector<int>dist;
};
void bfs(Gragh &g, int source);
void print(const Gragh& g);
/*
Input format:
  node_num edg_num source
  u -> v
  u -> v
*/
void bfs(Gragh &g, int source){
  vector<bool>vis(g.adj_list.size(),false);
  queue<int>que;
  que.push(source);
  vis[source] = true;
  g.dist[source] = 0;
  while(!que.empty()) {
    int cur_node = que.front();
    vector<int>cur_node_adj = g.adj_list[cur_node];
    for(int i = 0; i < (int)cur_node_adj.size(); i++) {
      int adj_node = cur_node_adj[i];
      if(vis[adj_node] == true) continue;
      vis[adj_node] = true;
      g.dist[adj_node] = g.dist[cur_node] +  1;
      que.push(adj_node);
    }
    que.pop();
  }
}
void print(const Gragh &g) {
  std::cout << "node ids" << " ";
  for(int i = 0; i < (int)g.adj_list.size(); i++) {
    std::cout << "  " << i;
  }
  std::cout << '\n';
  for(auto dis : g.dist) {
    std::cout << dis<< " ";
  }
  std::cout << '\n';
}

void Gragh::add_edge(int start, int end) {
  adj_list[start].push_back(end);
}

int main(int argc, char const *argv[]) {
  int node_num, edge_node;
  int source;
  std::cin >> node_num >> edge_node >> source;

  Gragh g(node_num);
  // node's id start at zero
  for(int i = 0; i < edge_node; i++) {
    int u, v;
    std::cin >> u >> v;
    g.add_edge(u, v);
  }
  // std::cout << "input done !" << '\n';
  // calc the distance from source to other node
  bfs(g, source);
  std::cout << "source: " << source << '\n';
  print(g);
  return 0;
}

