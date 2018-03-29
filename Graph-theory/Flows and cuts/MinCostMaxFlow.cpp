


/*
采用贪心的思想，每次找到一条从源点到达汇点的路径，增加流量，且该条路径满足使得增加的流量的花费最小，
直到无法找到一条从源点到达汇点的路径，算法结束。 
由于最大流量有限，每执行一次循环流量都会增加，因此该算法肯定会结束，且同时流量也必定会达到网络的最大流量；
同时由于每次都是增加的最小的花费，即当前的最小花费是所有到达当前流量flow时的花费最小值，因此最后的总花费最小。
*/
const int MAXN = 210;
const int MAXV = 210;
const int MAXE = 8 * MAXV;
const int INF = 0x7f7f7f7f;

struct MinCostMaxFlow {
    int head[MAXV];
    int to[MAXE], next[MAXE], cost[MAXE], flow[MAXE];
    int n, ecnt, st, ed;

    void init(int MAX_Size) {
        n = MAX_Size;
        memset(head, -1,sizeof(head));
        ecnt = 0;
    }
    void add_edge(int u, int v, int c, int w) {
        to[ecnt] = v; flow[ecnt] = c; cost[ecnt] = w; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; flow[ecnt] = 0; cost[ecnt] = -w; next[ecnt] = head[v]; head[v] = ecnt++;
    }
    bool vis[MAXV];
    int dis[MAXV], pre[MAXV];
    queue<int> que;
    bool spfa() {
        memset(vis, 0, sizeof(vis));
        memset(dis, 0x7f, sizeof(dis));
        dis[st] = 0; 
        que.push(st);
        while(!que.empty()) {
            int u = que.front(); que.pop();
            vis[u] = false;
            for(int p = head[u]; ~p; p = next[p]) {
                int &v = to[p];
                if(flow[p] && dis[v] > dis[u] + cost[p]) {
                    dis[v] = dis[u] + cost[p];
                    pre[v] = p;
                    if(!vis[v]) {
                        que.push(v);
                        vis[v] = true;
                    }
                }
            }
        }
        return dis[ed] < INF;
    }

    int maxFlow, minCost;
    pair<int,int>min_cost_flow(int source, int sink) {
        st = source, ed = sink;
        maxFlow = minCost = 0;
        while(spfa()) {
            int u = ed, tmp = INF;
            while(u != st) {
                tmp = min(tmp, flow[pre[u]]);
                u = to[pre[u] ^ 1];
            }
            u = ed;
            while(u != st) {
                flow[pre[u]] -= tmp;
                flow[pre[u] ^ 1] += tmp;
                u = to[pre[u] ^ 1];
            }
            maxFlow += tmp;
            minCost += tmp * dis[ed];
        }
        return {maxFlow,minCost};
    }
} flow;
