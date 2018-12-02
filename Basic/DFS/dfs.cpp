#include <bits/stdc++.h>

using namespace std;

const int maxn = 100010;
vector<vector<pair<long long, long long>> >graph(maxn);
vector<bool>vis(maxn, 0);
vector<long long>dist(maxn, 0);

void dfs(long long cur)
{
    vis[cur] = 1;
    for(auto x : graph[cur]) {
        if(vis[x.first] == true) continue;
        dist[x.first] = dist[cur] + x.second;
        dfs(x.first);
    }
}

int main(){
    int n; // number of node
    int m; // number of edge
    std::cin >> n >> m;
    for(int i = 0;i < m; i++) {
        long long u, v, val;
        cin >> u >> v >> val;
        // undirected graph
        graph[u].push_back(make_pair(v, val));
        graph[v].push_back(make_pair(u, val));
    }
    dfs(1);
    cout << "distance from node 1 to other node:" << endl;
    for(int i = 1; i<= n; i++) {
        std::cout << dist[i] << " ";
    }
    cout << endl;
    return 0;
}