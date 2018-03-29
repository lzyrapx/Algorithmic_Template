#include<bits/stdc++.h>
using namespace std;
/*
    Dinic   O(n^2*m)
   如果所有容量均为1,复杂度O(min(n^(2/3) * m, m^(1/2)) * m)
   对于二分图,复杂度O(n^(1/2) * m)
   构造层次图,然后在层次图上DFS找增光路,路径 d[u]=d[v]+1
   加当前弧优化,效率提高
*/
const int INF = 2147483647;
const int N = 10000;
struct Edge
{
    int u,v,cap;
}e[N*N];

int first[N],Next[N*N],d[N],cur[N];
int n,m,S,T,mt;

void addedge(int a,int b,int val)
{
    e[mt].u=a;
    e[mt].v=b;
    e[mt].cap=val;
    Next[mt]=first[a];
    first[a]=mt++;
    
    e[mt].u=b;
    e[mt].v=a;
    e[mt].cap=0;
    Next[mt]=first[b];
    first[b]=mt++;
}

int bfs()
{
    //std::cout << "bfs" << '\n';
    int u,i,j;
    queue<int> q;
    memset(d,0,sizeof(d));
    q.push(S);
    d[S]=1;
    while(!q.empty()){
        u=q.front();
        q.pop();
        //这里为什么是i！=-1呢？因为，标号是从0开始的
        for(i=first[u];i!=-1;i=Next[i]){
            if(e[i].cap && !d[e[i].v]){
                d[e[i].v]=d[u]+1;
                q.push(e[i].v);
            }
        }
    }
    return d[T];
}

int dfs(int u,int a)
{
    if(u==T || a==0) return a;// a 为瓶颈。
    int f = 0,flow=0;
    for(int& i=cur[u];i!=-1;i=Next[i]){      //当前弧优化,从上次的弧考虑
        if( d[u]+1==d[e[i].v] && (f=dfs(e[i].v,min(a,e[i].cap)) )){
            e[i].cap-=f;
            //这里的^是很常用的，因为前向星加边是两条一起加的，只是反向边一开始是为零的，
            //所以^1一下可以得到另一条边，比如0^1 = 1,1 ^ 1 = 0, 2^1 = 3,3 ^1 = 2;
            e[i^1].cap+=f;
            flow+=f;
            a-=f;
            if(!a)break;
        }
    }
    return flow;
}

int dinic()
{
    //std::cout << "dinic" << '\n';
    int flow=0;
    while(bfs()){
        for(int i=0;i<=n;i++)cur[i]=first[i];  //注意这里是所有点都要赋值！！！
        flow+=dfs(S,INF);
    }
    return flow;
}

int main()
{
    memset(cur,-1,sizeof(cur));
    memset(first,-1,sizeof(first));

    std::cin >> n >> m;
    S = 1, T = n;
    for(int i=1;i<=m;i++) {
      int u,v,cap;
      std::cin >> u >> v >> cap;
      addedge(u,v,cap);
    }
    std::cout << dinic() << '\n';
    return 0;
}
/*
6 8
1 2 5
1 4 4
2 3 6
4 5 1
3 6 5
5 6 2
4 2 3
3 5 8

answer: 
7

*/
