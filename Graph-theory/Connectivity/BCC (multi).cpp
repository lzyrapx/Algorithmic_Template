/*   BCC  O(E)
  tarjan算法
 -Node-Biconnected Component
 -Edge-Biconnected Component(可以处理重边)
 -Edge-Biconnected Component(不能处理重边)
 */
  
  
/* Node-Biconnected Component
  iscut[]为割点集
  bcc[]为双连通点集
  割顶的bccno[]无意义       */
struct Edge{
    int u,v;
}e[N*N];
bool iscut[N];
int first[N],next[N*N],low[N],pre[N],bccno[N];
int n,m,mt,dfs_clock,bcnt;
vector<int> bcc[N];
stack<Edge> s;

void adde(int a,int b)
{
    e[mt].u=a;e[mt].v=b;
    next[mt]=first[a];first[a]=mt++;
    e[mt].u=b;e[mt].v=a;
    next[mt]=first[b];first[b]=mt++;
}

void dfs(int u,int fa)
{
    int i,j,v,child=0;
    Edge t;
    pre[u]=low[u]=++dfs_clock;
    for(i=first[u];i!=-1;i=next[i]){
        child++;
        v=e[i].v;
        t.u=u;t.v=v;
        if(!pre[v]){   //没有访问过
            s.push(t);
            dfs(v,u);
            low[u]=Min(low[u],low[v]);
            if(low[v]>=pre[u]){   //点u为割点
                iscut[u]=true;
                Edge x;x.u=-1;
                bcnt++;bcc[bcnt].clear();
                while(x.u!=u || x.v!=v){
                    x=s.top();s.pop();
                    if(bccno[x.u]!=bcnt){bcc[bcnt].push_back(x.u);bccno[x.u]=bcnt;}
                    if(bccno[x.v]!=bcnt){bcc[bcnt].push_back(x.v);bccno[x.v]=bcnt;}
                }
            }
        }
        else if(v!=fa && pre[v]<pre[u]){   //存在反向边,更新low[u]
            s.push(t);
            low[u]=Min(low[u],pre[v]);
        }
    }
    if(fa==-1 && child==1)iscut[u]=false;  //根节点特判
}

void find_bcc()
{
    int i,j;
    bcnt=dfs_clock=0;mem(pre,0);
    mem(bccno,0);mem(iscut,0);
    for(i=1;i<=n;i++){
        if(!pre[i])dfs(i,-1);
    }
}

/* Edge-Biconnected Component(可以处理重边)
  iscut[]为割边集
  bccno[]为双连通点集,保存为编号        */
struct Edge{
    int u,v;
}e[N*N];
bool iscut[N*N];
int first[N],next[N*N],pre[N],low[N],bccno[N];
int n,m,mt,bcnt,dfs_clock;
stack<int> s;

void dfs(int u,int fa)
{
    int i,v;
    pre[u]=low[u]=++dfs_clock;
    s.push(u);
    int cnt=0;
    for(i=first[u];i!=-1;i=next[i]){
        v=e[i].v;
        if(!pre[v]){
            dfs(v,u);
            low[u]=Min(low[u],low[v]);
            if(low[v]>pre[u])iscut[i]=true;   //存在割边
        }
        else if(fa==v){  //反向边更新
            if(cnt)low[u]=Min(low[u],pre[v]);
            cnt++;
        }
        else low[u]=Min(low[u],pre[v]);
    }
    if(low[u]==pre[u]){  //充分必要条件
        int x=-1;
        bcnt++;
        while(x!=u){
            x=s.top();s.pop();
            bccno[x]=bcnt;
        }
    }
}

void find_bcc()
{
    int i;
    bcnt=dfs_clock=0;
    mem(pre,0);mem(bccno,0);
    for(i=1;i<=n;i++){
        if(!pre[i])dfs(i,-1);
    }
}


/* Edge-Biconnected Component(不能处理重边)
  iscut[]为割边集
  bccno[]为双连通点集,保存为编号        */
struct Edge{
    int u,v;
}e[N*N];
bool iscut[N*N];
int first[N],next[N*N],pre[N],low[N],bccno[N];
int n,m,mt,bcnt,dfs_clock;
stack<int> s;

void adde(int a,int b)
{
    e[mt].u=a;e[mt].v=b;
    next[mt]=first[a];first[a]=mt++;
    e[mt].u=b;e[mt].v=a;
    next[mt]=first[b];first[b]=mt++;
}

void dfs(int u,int fa)
{
    int i,v;
    pre[u]=low[u]=++dfs_clock;
    s.push(u);
    for(i=first[u];i!=-1;i=next[i]){
        v=e[i].v;
        if(!pre[v]){
            dfs(v,u);
            low[u]=Min(low[u],low[v]);
            if(low[v]>pre[u])iscut[i]=true;   //存在割边
        }
        else if(v!=fa && pre[v]<pre[u]){  //反向边更新
            low[u]=Min(low[u],pre[v]);
        }
    }
    if(low[u]==pre[u]){  //充分必要条件
        int x=-1;
        bcnt++;
        while(x!=u){
            x=s.top();s.pop();
            bccno[x]=bcnt;
        }
    }
}

void find_bcc()
{
    int i;
    bcnt=dfs_clock=0;mem(iscut,0);
    mem(pre,0);mem(bccno,0);
    for(i=1;i<=n;i++){
        if(!pre[i])dfs(i,-1);
    }
}
