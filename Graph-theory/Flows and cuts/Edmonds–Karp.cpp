#include<bits/stdc++.h>
using namespace std;

/*
The Edmonds–Karp algorithm chooses each path so that the number
of edges on the path is as small as possible. This can be done by using breadth-
first search instead of depth-first search for finding paths. It can be proven that
this guarantees that the flow increases quickly, and the time complexity of the
algorithm is O(n*m^2).

time complexity is O(VE^2).
*/
#define maxn 10010
int maxData = 0x7fffffff;
int capacity[maxn][maxn]; //记录残留网络的容量
int flow[maxn];                //标记从源点到当前节点实际还剩多少流量可用
int pre[maxn];                 //标记在这条路径上当前节点的前驱,同时标记该节点是否在队列中
int n,m;
queue<int> que;

int BFS(int src,int des)
{
    int i,j;
    while(!que.empty())       //队列清空
        que.pop();
    for(i=1;i<m+1;i++)
    {
        pre[i]=-1;
    }
    pre[src]=0;
    flow[src]= maxData;
    que.push(src);
    while(!que.empty())
    {
        int index = que.front();
        que.pop();
        if(index == des)            //找到了增广路径
            break;
        for(i=1;i<m+1;i++)
        {
            if(i!=src && capacity[index][i]>0 && pre[i]==-1)
            {
                 pre[i] = index; //记录前驱
                 flow[i] = min(capacity[index][i],flow[index]);   //关键：迭代的找到增量
                 que.push(i);
            }
        }
    }
    //如果n点找不到增广路，说明已经没增广路到汇点了
    if(pre[des]==-1)      //残留图中不再存在增广路径
        return -1;
    else
        return flow[des];
}

int maxFlow(int src,int des)
{
    int increasement= 0;
    int sumflow = 0;
    //不断通过bfs来找增广路，然后sumflow+=增广路上的流量。
    while((increasement=BFS(src,des))!=-1)
    {
         int k = des;          //利用前驱寻找路径
         while(k!=src)//不断调整流量大小。
         {
              int last = pre[k];
              capacity[last][k] -= increasement; //改变正向边的容量
              capacity[k][last] += increasement; //改变反向边的容量
              k = last;
         }
         sumflow += increasement;
    }
    return sumflow;
}

int main()
{
    int i,j;
    int S,T;
    int start,end,cap;
    while(cin>>n>>m>>S>>T)
    {
        memset(capacity,0,sizeof(capacity));
        memset(flow,0,sizeof(flow));
        for(i=0;i<m;i++)
        {
            cin>>start>>end>>cap;
            if(start == end)               //考虑起点终点相同的情况
               continue;
            capacity[start][end] +=cap;     //此处注意可能出现多条同一起点终点的情况
        }
        cout<<maxFlow(S,T)<<endl; //S 到 T的最大流
    }
    return 0;
}
/*

6 8 1 6
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
