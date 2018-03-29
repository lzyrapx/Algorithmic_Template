#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
const int MAXNODE = 10005;
const int MAXEDGE = 100010;
const int INF = 0x3f3f3f3f;

struct Edge{
    int v, id, next;
    bool bridge;
    Edge() {}
    Edge(int v, int id, int next): v(v), id(id), next(next), bridge(false){}
}E[MAXEDGE * 2], cut[MAXEDGE];

struct Node {
    int u, v;
    Node() {}
    Node(int u, int v): u(u), v(v) {}
};

stack<Node> Stack;
//bcc表示的是一个bcc里面的点
vector<int> bcc[MAXNODE];
//pre纪录的是时间戳,lowlink纪录的是该点及其该子孙节点所能返回的最早时间戳是多少,bccno纪录的是该点当前是属于哪个bcc的
int head[MAXNODE], pre[MAXNODE], lowlink[MAXNODE], bccno[MAXNODE];
int n, m, tot, bcc_cnt, dfs_clock, cut_cnt; 
bool iscut[MAXNODE];

//双向边的添加
void AddEdge(int u, int v, int id) {
    E[tot] = Edge(v, id, head[u]);
    head[u] = tot++;
    E[tot] = Edge(u, id, head[v]);
    head[v] = tot++;
}

void init() {
    memset(head, -1, sizeof(head));
    tot = 0;
}

//点双连通
void dfs(int u, int fa) {
    pre[u] = lowlink[u] = ++dfs_clock;
    int child = 0;//纪录当前节点有多少个子节点
    for (int i = head[u]; ~i; i = E[i].next) {
        int v = E[i].v;
        if (!pre[v]) {
            Stack.push(Node(u, v));
            child++;
            dfs(v, u);
            lowlink[u] = min(lowlink[u], lowlink[v]);//更新
            //子节点最多返回到该点
            if (lowlink[v] >= pre[u]) {
                //该边为桥
                if (lowlink[v] > pre[u]) {
                    E[i].bridge = E[i ^ 1].bridge = true;
                    cut[cut_cnt++] = E[i];
                }
                iscut[u] = true;
                bcc_cnt++; bcc[bcc_cnt].clear();
                while (1) {
                    Node x = Stack.top(); Stack.pop();
                    if (bccno[x.u] != bcc_cnt) {
                        bcc[bcc_cnt].push_back(x.u);
                        bccno[x.u] = bcc_cnt;
                    }
                    if (bccno[x.v] != bcc_cnt) {
                        bcc[bcc_cnt].push_back(x.v);
                        bccno[x.v] = bcc_cnt;
                    }
                    if (x.u == u && x.v == v) break;
                }
            }
        }
        else if (v != fa && pre[v] < pre[u]) {//反向边
            Stack.push(Node(u, v));
            lowlink[u] = min(lowlink[u], pre[v]);
        }
    }
    //u是根结点，且只有一个孩子，那就不是割点了
    if (fa < 0 && child == 1) iscut[u] = 0;
}

void find_bcc() {
    memset(pre, 0, sizeof(pre));
    memset(iscut, 0, sizeof(iscut));
    memset(bccno, 0, sizeof(bccno));
    dfs_clock = bcc_cnt = cut_cnt = 0;
    for (int i = 0; i < n; i++) 
        if (!pre[i]) dfs(i, -1);
}

int main() {
    init();
    return 0;
}