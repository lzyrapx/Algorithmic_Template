/* 
  K短路  
  A*
  首先求出所有点到汇点的最短路距离,然后A*搜索
  G1和edge1是正向图,G2和edge2是逆向图  
*/

struct Node{
    int d,u;
};
struct Edge{
    int from,to,dis;
};

int n,m,S,T,K;
int d[N],vis[N];
vector<Edge> edge1,edge2;
vector<int> G1[N],G2[N];

struct cmp1{
    bool operator()(const Node &a,const Node &b){
        return a.d>b.d;
    }
};
struct cmp2{
    bool operator()(const Node &a,const Node &b){
        return a.d+d[a.u]>b.d+d[a.u];
    }
};

void init(int n)
{
    edge1.clear();
    edge2.clear();
    for(int i=1;i<=n;i++) G1[i].clear();
    for(int i=1;i<=n;i++) G2[i].clear();
}

void dijkstra(int s,vector<Edge>& edge) {
    priority_queue<Node,vector<Node>,cmp1> q;
    for(int i=1;i<=n;i++)d[i]=INF;
    d[s]=0;
    memset(vis,0,sizeof(vis));
    q.push((Node){0,s});
    while(!q.empty()){
        int u=q.top().u;q.pop();
        if(vis[u])continue;
        vis[u]=1;
        for(int i=0;i<(int)G2[u].size();i++){
            Edge& e=edge[G2[u][i]];
            if(d[u]+e.dis<d[e.to]){
                d[e.to]=d[u]+e.dis;
                q.push((Node){d[e.to],e.to});
            }
        }
    }
}

int astar(int s,int t,int k,vector<Edge>& edge) {
    int cou[MAX];
    memset(cou,0,sizeof(cou));
    Node nod;
    priority_queue<Node,vector<Node>,cmp2> q;
    q.push((Node){d[s],s});
    if(s==t)k++;
    while(1){
        nod=q.top();q.pop();
        if(nod.u==t) cou[nod.u]++;
        if(cou[nod.u]==k) return nod.d;
        for(int i=0;i<G1[nod.u].size();i++){  //从当前点到所有邻接点
            Edge& e=edge[G1[nod.u][i]];
            q.push((Node){nod.d-d[nod.u]+d[e.to]+e.dis,e.to});
        }
    }
    return 0;
}
