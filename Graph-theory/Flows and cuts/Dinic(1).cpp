#include<bits/stdc++.h>
using namespace std;

#define SZ(x) ((int)(x).size())
#define PB push_back


// O(n^2*m)

struct Dinic{
  static const int MXN = 10000;
  struct Edge{ int v,f,re; };
  int n,s,t,level[MXN];
  vector<Edge> E[MXN];
  void init(int _n, int _s, int _t){
    n = _n; s = _s; t = _t;
    for (int i=0; i<n; i++) E[i].clear();
  }
  void add_edge(int u, int v, int f){  //建图
    E[u].PB({v,f,SZ(E[v])});
    E[v].PB({u,0,SZ(E[u])-1});
  }
  bool BFS(){
    for (int i=0; i<n; i++) level[i] = -1;
    queue<int> que;
    que.push(s);
    level[s] = 0;
    while (!que.empty()){
      int u = que.front(); que.pop();
      for (auto it : E[u]){
        if (it.f > 0 && level[it.v] == -1){
          level[it.v] = level[u]+1;
          que.push(it.v);
        }
      }
    }
    return level[t] != -1;
  }
  int DFS(int u, int nf){
    if (u == t) return nf;
    int res = 0;
    for (auto &it : E[u]){
      if (it.f > 0 && level[it.v] == level[u]+1){
        int tf = DFS(it.v, min(nf,it.f));
        res += tf; nf -= tf; it.f -= tf;
        E[it.v][it.re].f += tf;
        if (nf == 0) return res;
      }
    }
    if (!res) level[u] = -1;
    return res;
  }
  int flow(int res=0){
    // std::cout << "flow" << '\n';
    while ( BFS() )
      res += DFS(s,2147483647);
    return res;
  }
}flow;

int main()
{
   int n,m;
   std::cin >> n >> m;
   int s = 0 ,t= n-1;
   flow.init(n+1,s,t); 
   for(int i=1;i<=m;i++) {
     int u,v,cap;
     std::cin >> u >> v >> cap;
     u--,v--;
     flow.add_edge(u,v,cap);
   }
   int ans = flow.flow(0);
   std::cout << ans << '\n';
    return 0;
}
/*
6 8
1 2 5
1 4 4
2 3 6
4 5 1
3 6 5
5 6 2
4 2 3
3 5 8

answer:
7
*/
