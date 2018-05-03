/*    
  匈牙利算法
  最小点集覆盖 = 最大匹配数
  最小路径覆盖 = n - 最大匹配数
  最大独立集  = n - 最大匹配数      
 */

/*   邻接矩阵   O(n^3)  */
// TLE版本

int vis[maxn];
int y[maxn];
int g[maxn][maxn];
int n; // 点数

int dfs(int u)
{
  for(int v = 0; v < n ; v++) {
    if(g[u][v]  && vis[v] == 0) {
      vis[v] = 1;
      if(y[v] == -1 || dfs(y[v])) {
        y[v] = u;
        return 1;
      }
    }
  }
  return 0;
}
int match() //返回匹配的点数，所以一定是偶数
{
  int cnt = 0;
  memset(y,-1,sizeof(y));
  for(int i = 0; i < n; i++) {
    memset(vis,0,sizeof(vis));
    if(dfs(i)) {
      cnt++; 
    }
  }
  return cnt;
}
