/*
 圆方树 & 仙人掌学习笔记: https://www.cnblogs.com/cjyyb/p/9098400.html
 circle-square-tree Maximum independent set.
 圆方树最大独立集.
 最大独立集：在无向图中选出若干个点，这些点互相没有边连接，并使取出的点尽量多.
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
vector<int> E1[maxn], ET[maxn];
int m, n, N, fa[maxn], dp[maxn][2];
int len[maxn], dfn[maxn], dfs_clock;
bool inCircle[maxn];
int dp2[maxn][2];
inline void addEdge1(int x, int y) { E1[x].push_back(y); }
inline void addEdgeT(int x, int y) { ET[x].push_back(y); }

void input() {
  cin >> n >> m;
  N = n;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    addEdge1(u, v);
    addEdge1(v, u);
  }
}

void tarjan(int u) {
  dfn[u] = ++dfs_clock;
  for (int i = 0; i < (int)E1[u].size(); i++) {
    int v = E1[u][i];
    if (v == fa[u]) continue;
    if (!dfn[v]) {
      fa[v] = u;
      tarjan(v);
    }
    else if (dfn[v] < dfn[u]) {
      n++;
      len[n] = dfn[u] - dfn[v] + 1;
      fa[n] = v;
      addEdgeT(v, n);
      int temp = u;
      while (temp != v) {
        inCircle[temp] = true;
        addEdgeT(n, temp);
        temp = fa[temp];
      }
    }
  }

  if (!inCircle[u]) {
    addEdgeT(fa[u], u);
  }
  dfs_clock--;
}
void work(int x) {
  int sz = ET[x].size();
  if (sz == 2) {
    int son1 = ET[x][0];
    int son2 = ET[x][1];
    dp[x][0] = dp[son1][0] + dp[son2][0];
    dp[x][1] = max(dp[son1][0] + dp[son2][0],
                   max(dp[son1][0] + dp[son2][1], dp[son1][1] + dp[son2][0]));
    return;
  }
  dp2[0][0] = dp[ET[x][0]][0];
  dp2[0][1] = 0;
  for (int i = 1; i < sz; i++) {
    dp2[i][0] = max(dp2[i - 1][0], dp2[i - 1][1]) + dp[ET[x][i]][0];
    dp2[i][1] = dp2[i - 1][0] + dp[ET[x][i]][1];
  }

  dp[x][0] = dp2[sz - 1][0];
  dp[x][1] = dp2[sz - 1][0];
  dp2[sz][0] = dp2[sz][1] = 0;

  for (int i = sz - 1; i >= 0; i--) {
    dp2[i][0] = max(dp2[i + 1][0], dp2[i + 1][1]) + dp[ET[x][i]][0];
    dp2[i][1] = dp2[i + 1][0] + dp[ET[x][i]][1];
  }
  dp[x][1] = max(dp[x][1], max(dp2[0][0], dp2[0][1]));
}
void dfs(int u) {
  dp[u][0] = 0;
  dp[u][1] = 1;
  if (u > N) dp[u][0] = 0;
  for (int i = 0; i < (int)ET[u].size(); i++) {
    int v = ET[u][i];
    dfs(v);
    if (u <= N) {
      dp[u][0] += max(dp[v][1], dp[v][0]);
      dp[u][1] += dp[v][0];
    }
  }
  if (u > N) work(u);
}
int main() {
  input();
  tarjan(1);
  dfs(1);
  /*
  dp[u][0]表示只考虑 u的子树，u点不选的方案个数.
  dp[u][1]表示只考虑 u的子树，选了u点的方案个数.
  然后正常 DP，然后每次DP到所有环中离根最近的那个点时，单独拉出来算一下就可以了.
  */
  cout << max(dp[1][0], dp[1][1]) << endl;
  return 0;
}
