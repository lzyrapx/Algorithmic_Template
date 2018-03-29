//http://codeforces.com/blog/entry/14378

#include <bits/stdc++.h>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

const long long INF = (1ll << 50);
struct graph {
  typedef long long flow_type;
  struct edge {
    int src, dst;
    flow_type capacity, flow;
    size_t rev;
  };
  int n;
  vector<vector<edge>> adj;
  graph(int n) : n(n), adj(n) { }

  void add_edge(int src, int dst, int capacity) {
    adj[src].push_back({src, dst, capacity, 0, adj[dst].size()});
    adj[dst].push_back({dst, src, 0, 0, adj[src].size() - 1});
  }

  flow_type max_flow(int s, int t) {
    vector<flow_type> excess(n);
    vector<int> dist(n), active(n), count(2*n);
    queue<int> Q;
    auto enqueue = [&](int v) {
      if (!active[v] && excess[v] > 0) { active[v] = true; Q.push(v); }
    };
    auto push = [&](edge &e) {
      flow_type f = min(excess[e.src], e.capacity - e.flow);
      if (dist[e.src] <= dist[e.dst] || f == 0) return;
      e.flow += f;
      adj[e.dst][e.rev].flow -= f;
      excess[e.dst] += f;
      excess[e.src] -= f;
      enqueue(e.dst);
    };

    dist[s] = n; active[s] = active[t] = true;
    count[0] = n-1; count[n] = 1;
    for (int u = 0; u < n; ++u)
      for (auto &e: adj[u]) e.flow = 0;
    for (auto &e: adj[s]) {
      excess[s] += e.capacity;
      push(e);
    }
    while (!Q.empty()) {
      int u = Q.front(); Q.pop();
      active[u] = false;

      for (auto &e: adj[u]) push(e);
      if (excess[u] > 0) {
        if (count[dist[u]] == 1) {
          int k = dist[u]; // Gap Heuristics
          for (int v = 0; v < n; v++) {
            if (dist[v] < k) continue;
            count[dist[v]]--;
            dist[v] = max(dist[v], n+1);
            count[dist[v]]++;
            enqueue(v);
          }
        } else {
          count[dist[u]]--; // Relabel
          dist[u] = 2*n;
          for (auto &e: adj[u])
            if (e.capacity > e.flow)
              dist[u] = min(dist[u], dist[e.dst] + 1);
          count[dist[u]]++;
          enqueue(u);
        }
      }
    }

    flow_type flow = 0;
    for (auto e: adj[s]) flow += e.flow;
    return flow;
  }
};
int read(){ int v = 0, f = 1;char c =getchar();
while( c < 48 || 57 < c ){if(c=='-') f = -1;c = getchar();}
while(48 <= c && c <= 57) v = v*10+c-48, c = getchar();
return v*f;}
int main() {

  int n,m,s,t;
//  scanf("%d%d%d%d", &n, &m,&s,&t);
  n=read(),m=read(),s=read(),t=read();
  graph g(n);
  for (int i = 0; i < m; ++i) {
      int u, v, w;
      //scanf("%d %d %d", &u, &v, &w);
      u=read(),v=read(),w=read();
      u--,v--;
      g.add_edge(u, v, w);
  }
  printf("%d\n", g.max_flow(s-1, t-1));
  return 0;
}