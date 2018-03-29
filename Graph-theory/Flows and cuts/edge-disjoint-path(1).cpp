#include <bits/stdc++.h>
using namespace std;


/*
The Ford–Fulkerson algorithm can finds the maximum flow in a graph. The
algorithm begins with an empty flow, and at each step finds a path from the
source to the sink that generates more flow. Finally, when the algorithm cannot
increase the flow anymore, the maximum flow has been found.

O(VE^2) = O(Km)
*/
const int maxn= 250;
const int inf=INT_MAX;

struct edge
{
    int to,cap,rev;
};

vector<edge> G[maxn];

bool used[maxn];

void addedge(int from ,int to,int cap)
{
    G[from].push_back((edge){to,cap,(int)G[to].size()});
    G[to].push_back((edge){from,0,(int)G[from].size()-1});
}

int dfs(int v,int t,int f)
{
    if(v==t) return f;
    used[v]=true;
    for(int i=0;i<G[v].size();i++)
    {
        edge &e=G[v][i];
        if(!used[e.to]&&e.cap>0)
        {
            int d=dfs(e.to,t,min(f,e.cap));
            if(d>0)
            {
                e.cap-=d;
                G[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s,int t)
{
    int flow=0;
    while(true)
    {
        memset(used,false,sizeof(used));
        int f=dfs(s,t,inf); //不断找从s到t的增广路
        if(f==0) return flow; //找不到了就回去
        flow += f; //找到一个流量f的路
    }
}

void init(int m)
{
    for(int i=0;i<m;i++) {
      G[i].clear();
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int n,m;
    while(cin>>n>>m)
    {
        init(m);
        for(int i=0;i<m;i++)
        {
            int u,v,cap;
            cin>>u>>v>>cap;
            addedge(u,v,cap);
        }
        cout<<max_flow(1,n)<<endl;
    }
    return 0;
}
/*
6 9
1 2 1
1 4 1
3 2 1
2 4 1
4 3 1
4 5 1
3 6 1
5 6 1
3 5 1

answer:
2
*/
