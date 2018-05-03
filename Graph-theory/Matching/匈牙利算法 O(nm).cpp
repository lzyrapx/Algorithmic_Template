/*
匈牙利算法
*/

// vector邻接表： O(nm)

std::vector<int> link[maxn];
int match[maxn];
int n;
int vis[maxn];
int dfs(int u)
{
  int m = link[u].size();
  for(int i = 0; i < m; i++) {
    if(!vis[link[u][i]]) { // u->i有边,且节点i未被搜索
    	
      vis[link[u][i]] = 1; //标记节点已被搜索

      //如果 i 不属于前一个匹配 M 或被 i 匹配到的节点可以寻找到增广路
      if(match[link[u][i]] == -1 || dfs(match[link[u][i]])) {
        match[link[u][i]] = u; //更新匹配
        return 1;
      }
    }
  }
  return 0;
}
int hungary()
{
  int cnt = 0;
  memset(match,-1,sizeof(match));
  for(int i = 0; i < n; i++) {
    memset(vis,0,sizeof(vis));
    if(dfs(i)) {
      cnt++;
    }
  }
  return cnt;
}

// 建图： link[x].push_back(y);
