#include <cstdio>  
#include <cstring>  
#include <algorithm>  
using namespace std;  

const int N = 10005;  
const int M = 20005;  

struct Edge{  
    int u, v, id, next;  
    bool iscut;  
    Edge() {}  
    Edge(int u, int v, int id, int next): u(u), v(v), id(id), next(next), iscut(false) {}  
}E[M * 2], cut[M];  

int n, m, tot, bcc_cnt, dfs_clock, cut_cnt;
int head[N], val[N], pre[N], lowlink[N], bccno[N]; 

void init() {  
    memset(head, -1, sizeof(head));
    tot = 0;
}  

void AddEdge(int u, int v, int id) {  
    E[tot] = Edge(u, v, id, head[u]);
    head[u] = tot++;
    E[tot] = Edge(v, u, id, head[v]);
    head[v] = tot++;
}  

void dfs_cut(int u, int fa) {  
    pre[u] = lowlink[u] = ++dfs_clock;  
    for (int i = head[u]; ~i; i = E[i].next) {
        int v = E[i].v;
        if (E[i].id == fa) continue;
        if (!pre[v]) {  
            dfs_cut(v, E[i].id);  
            lowlink[u] = min(lowlink[u], lowlink[v]);  
            if (lowlink[v] > pre[u]) {  
                E[i].iscut = E[i^1].iscut = true;//标记割边  
                cut[cut_cnt++] = E[i];//存放割边  
            }  
        } else lowlink[u] = min(lowlink[u], pre[v]);  
    }  
}  

void find_cut() {  
    dfs_clock = cut_cnt = 0;  
    memset(pre, 0, sizeof(pre));  
    for (int i = 0; i < n; i++)  
        if (!pre[i]) dfs_cut(i, -1);  
}  

void dfs_bcc(int u) {  
    pre[u] = 1;  
    bccno[u] = bcc_cnt;  
    for (int i = head[u]; ~i; i = E[i].next) {  
        if (E[i].iscut) continue;  
        int v = E[i].v;  
        if (pre[v]) continue;  
        dfs_bcc(v);  
    }  
}  

void find_bcc() {  
    bcc_cnt = 0;  
    memset(pre, 0, sizeof(pre));  
    for (int i = 0; i < n; i++) {  
        if (!pre[i]) {  
            dfs_bcc(i);  
            bcc_cnt++;  
        }  
    }  
}  

int main() {  
    return 0;  
}  


//--------------------------------------------------------------------------------
#include <cstdio>
#include <cstring>
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

//pre纪录的是时间戳,lowlink纪录的是该点及其该子孙节点所能返回的最早时间戳是多少,bccno纪录的是该点当前是属于哪个bcc的
int head[MAXNODE], pre[MAXNODE], lowlink[MAXNODE], bccno[MAXNODE], Stack[MAXNODE], belong[MAXNODE];
int n, m, tot, bcc_cnt, dfs_clock, top; 

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

//边双连通
void dfs(int u, int fa) {
    pre[u] = lowlink[u] = ++dfs_clock;
    Stack[++top] = u;

    for (int i = head[u]; ~i; i = E[i].next) {
        int v = E[i].v;
        if (!pre[v]) {
            dfs(v, u);
            lowlink[u] = min(lowlink[u], lowlink[v]);
            if (lowlink[v] > pre[u]) { 
                E[i].bridge = E[i ^ 1].bridge = true;
                bcc_cnt++;
                while (1) {
                    int x = Stack[top--];
                    belong[x] = bcc_cnt;
                    if (x == v) break;
                }
            }
        }
        else if (pre[v] < pre[u] && v != fa) lowlink[u] = min(lowlink[u], pre[v]);
    }
}

void find_bcc() {
    memset(pre, 0, sizeof(pre));
    memset(bccno, 0, sizeof(bccno));
    dfs_clock = bcc_cnt = 0;
    for (int i = 0; i < n; i++) 
        if (!pre[i]) dfs(i, -1);
}

int main() {
    init();
    return 0;
}