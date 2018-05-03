#include<bits/stdc++.h>
using namespace std;
struct point {  
    int v,next,cap;  
} edge[20010*10];  
  
int head[20010];  
int dis[20010];  
bool vis[20010];  
int len, n, m;  
  
void addedge(int from, int to, int cap)  
{  
    edge[len].v = to;  
    edge[len].cap = cap;  
    edge[len].next = head[from];  
    head[from] = len++;  
}  
  
void spfa(int start)  
{  
    queue<int>q;  
    for(int i = 1; i <= n; i++){  
        dis[i] = 999999999;  
        vis[i] = 0;  
    }  
    q.push(start);  
    dis[start] = 0;  
    vis[start] = 1;  
    while(!q.empty())  
    {  
        int x = q.front();  
        q.pop();  
        vis[x] = 0;  
        for(int i = head[x]; i != -1; i = edge[i].next)  
        {  
            int v = edge[i].v; 
            if(dis[v] > dis[x] + edge[i].cap){  
                dis[v] = dis[x] + edge[i].cap; 
                if(!vis[v]){  
                    vis[v] = 1;  
                    q.push(v);  
                }  
            }  
        }  
    }  
}  
int main()
{
	int s,t;
	len = 0;
	int u,v,w;
	scanf("%d%d%d%d",&n,&m,&s,&t);//s到t的最短路 
	memset(head,-1,sizeof(head));
	for(int i=1;i<=m;i++){
		cin>>u>>v>>w;
		addedge(u,v,w);
		addedge(v,u,w); 
	}
	spfa(s);
//	cout<<"finish"<<endl;
	cout<<dis[t]<<endl;
	return 0;	
} 