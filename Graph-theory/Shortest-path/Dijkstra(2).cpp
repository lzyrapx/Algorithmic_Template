#include <bits/stdc++.h>
using namespace std;
/*
dijkstra基本思想是采用贪心法，对于每个节点v[i]，维护估计最短路长度最大值，每次取出一个使得该估计值最小的t，
并采用与t相连的边对其余点的估计值进行更新，更新后不再考虑t。
在此过程中，估计值单调递减，所以可以得到确切的最短路。
*/
/*
The time complexity of the implementation is O(n+mlogm), because
the algorithm goes through all nodes of the graph and adds for each edge at most
one distance to the priority queue.
*/
#define INF 0x7fffffff
const int max_v = 100010;
typedef long long ll;
typedef pair<int, int> P; //first 最短距离 second 顶点编号
struct edge {
    int to, cost;
};
vector<edge> G[max_v];
int d[max_v];
bool used[max_v];
int V;
void dijkstra(int s)
{
    priority_queue<P, vector<P>, greater<P> > que; //从小到大按first排序
    for(int j = 0; j < max_v; j++) d[j] = INF;
    d[s] = 0;
    que.push(P(0, s));
    while(!que.empty())
    {
        P p = que.top();
        que.pop();
        int v = p.second;
        if(d[v] < p.first) continue;
        for(int i = 0; i < G[v].size(); i++)
        {
            edge e = G[v][i];
            if(d[e.to] > d[v] + e.cost)
            {
                d[e.to] = d[v] + e.cost;
                que.push(P(d[e.to], e.to));
            }
        }
    }
}
int n, m, s, t, u, v, w;
int main(int argc, char *argv[])
{
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    dijkstra(s);
    printf("%d\n", d[t]);
    return 0;
}