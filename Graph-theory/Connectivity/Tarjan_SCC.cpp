#include <bits/stdc++.h>
using namespace std;

const int N = 10000;
/*   
	SCC
    O(E)
   tarjan算法
   sccno[]强连通集合,用编号标示.
*/
struct Edge
{
    int u,v;
}e[N*N];

int first[N],Next[N*N],pre[N],sccno[N],low[N];
int n,mt,dfs_clock,scnt;
stack<int> s;

void addedge(int a,int b)
{
    e[mt].u=a;
    e[mt].v=b;
    Next[mt]=first[a];
    first[a]=mt++;
}

void tarjan(int u)
{
   // std::cout << "tarjan" << '\n';
    int i,j,v;
    pre[u]=low[u]=++dfs_clock;
    s.push(u);
    for(i=first[u];i!=-1;i=Next[i]){
        v=e[i].v;
        if(!pre[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!sccno[v]){    //反向边更新
            low[u]=min(low[u],low[v]);
        }
    }
    if(low[u]==pre[u]){   //存在强连通分量
        int x=-1;
        scnt++;
        while(x!=u){
            x=s.top();
            s.pop();
            sccno[x]=scnt;
        }
    }
}

void find_scc()
{
   // std::cout << "SCC" << '\n';
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
    scnt=dfs_clock=0;
    for(int i=1;i<=n;i++){
        if(!pre[i])tarjan(i);
    }
}

int main()
{
     n = 7;
    memset(first,-1,sizeof(first));
    memset(Next,-1,sizeof(Next));
    for(int i=1;i<=10;i++) {
      int u,v;
      std::cin >> u >> v;
      addedge(u,v);
    }
    // std::cout << "/* message */" << '\n';
    find_scc();
    std::cout << scnt << '\n';
}

/*
1 2
2 1
1 2
5 4
3 2
6 5
3 7
6 3
7 6
2 5

answer:
4
*/
