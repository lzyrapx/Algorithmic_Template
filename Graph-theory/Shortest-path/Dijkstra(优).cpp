/* Dijkstra O(E * log V)
  p[]为路径
  不能处理负权图     */

struct Edge{
    int u,v,w;
}e[2*N];
int first[N],next[2*N],p[N],d[N];
int S,T,n,m,mt;

void adde(int a,int b,int c)
{
    e[mt].u=a,e[mt].v=b;e[mt].w=c;
    next[mt]=first[a],first[a]=mt++;
    e[mt].u=b,e[mt].v=a;e[mt].w=c;
    next[mt]=first[b],first[b]=mt++;
}

int dijkstra(int s)   //s is start
{
    int i,u;
    pii t;
    priority_queue<pii,vector<pii>,greater<pii> > q;
    mem(d,INF);d[s]=0;
    q.push(make_pair(d[s],s));
    while(!q.empty()){
        t=q.top();q.pop();
        u=t.second;
        if(t.first!=d[u])continue;
        for(i=first[u];i!=-1;i=next[i]){
            if(d[u]+e[i].w<d[e[i].v]){
                d[e[i].v]=d[u]+e[i].w;
                p[e[i].v]=i;
                q.push(make_pair(d[e[i].v],e[i].v));
            }
        }
    }
    return d[T];
}



/*   求最短路和次短路以及他们的路径数   
   d[i][0]为点i的最短路,d[i][1]为次短路
   cnt[i][0]为点i的最短路径数,cnt[i][0]为次短路径数
   转移方程：
   1,如果d[u][0]+w<d[u][0],分别更新v点的最短路和次短路
   2,如果d[u][0]+w==d[u][0],那么v点的最短路数加上u点的最短路数
   3,如果d[u][k]+w<d[u][1],更新v点的次短路数（根据k来定）
   4,如果d[u][k]+w==d[u][1],那么v点的次短路数加上u点的最短路数或者次短路数（根据k来定）  */
   
   
struct Node{
    int d,u,flag;
    bool operator < (const Node &oth) const{
        return d>oth.d;
    }
};
struct Edge{
    int u,v,w;
}e[N*N];
int first[N],next[N*N],d[N][2],cnt[N][2];
int s,T,n,m,mt;

void adde(int a,int b,int c)
{
    e[mt].u=a,e[mt].v=b;e[mt].w=c;
    next[mt]=first[a],first[a]=mt++;
}

int dijkstra(int s)
{
    int i,u,v,w,k,dis;
    Node t;
    priority_queue<Node> q;
    mem(d,0x3f);d[s][0]=d[s][1]=0;
    cnt[s][0]=cnt[s][1]=1;
    t.d=0,t.u=s,t.flag=0;
    q.push(t);
    while(!q.empty()){
        t=q.top();q.pop();
        u=t.u;dis=t.d;k=t.flag;
        if(dis!=d[u][k])continue;
        for(i=first[u];i!=-1;i=next[i]){
            v=e[i].v;w=e[i].w;
            if(dis+w<d[v][0]){
                cnt[v][1]=cnt[v][0];
                cnt[v][0]=cnt[u][0];
                d[v][1]=d[v][0];
                d[v][0]=dis+w;
                q.push(Node{d[v][0],v,0});
                q.push(Node{d[v][1],v,1});
            }
            else if(dis+w==d[v][0])cnt[v][0]+=cnt[u][0];
            else if(dis+w<d[v][1]){
                d[v][1]=dis+w;
                cnt[v][1]=cnt[u][k];
                q.push(Node{d[v][1],v,1});
            }
            else if(dis+w==d[v][1])cnt[v][1]+=cnt[u][k];
        }
    }
    return d[T][1];  //  返回次短路长度
}

