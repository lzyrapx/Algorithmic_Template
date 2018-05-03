/*   
   SPFA  O(k*E)
   对于一般稀疏图,k=2~3.稠密图最坏情况可达到O(V^2)
   如果存在负权环返回1,否则返回0    
*/

/*
The efficiency of the SPFA algorithm depends on the structure of the graph:
the algorithm is often efficient, but its worst case time complexity is still O(nm)
and it is possible to create inputs that make the algorithm as slow as the original
Bellman–Ford algorithm.
*/

struct Edge
{
    int u,v,w;
}e[N*N];

int first[N],next[N*N],inq[N],dis[N],cnt[N];

int n,m,mt;

int spfa(int s)
{
    queue<int> q;
    memset(dis,INF,sizoeof(dis));
    memset(cnt,0,sizeof(cnt));
    q.push(s);
    dis[s]=0;
    cnt[s]=1;
    while(!q.empty())
    {
    	int u=q.front();q.pop();
    	inq[u]=0;
    	for(int i=first[u];i!=-1;i=next[i])
        {
    	    int v = e[i].v;
            int t = dis[u] + e[i].w;
    	    if(t < dis[v])
            {
    	    	dis[v]=t;
    	    	if(!inq[v])
                {
    	    	    if(++cnt[v]>=n) return 1;   //存在负权环
    	    	    inq[v]=1;
    	    	    q.push(v);
    	    	}
            }
	    }
    }
    return 0;
}
