
// 对于单源最短路径的问题，Dijkstra算法对于带负权边的图就无能为力了，而Bellman-Ford算法就可以解决这个问题。 
// Bellman-Ford算法：可以处理带负权边的图。
// 算法的实现模板：O(n*m)

typedef struct edge
{
	int v;  //起点
	int u;  //终点
	int w; 
}edge;
edge edges[20004];
int dis[1004];
int maxData=1000000000; //此处特别注意，Bellman-Ford算法中不要使用0x7fffffff 
int edgenum;

//n:点 ，m：边
/*
(负权环)A negative cycle can be detected using the Bellman–Ford algorithm by running
the algorithm for n rounds. If the last round reduces any distance, the graph
contains a negative cycle.
*/
bool BellmanFord(int s)
{
	bool flag=false;
	for(int i=1;i<n+1;i++)
	{
		dis[i]=maxData;  //其余点的距离设置为无穷 
	}
	dis[s]=0; //源点的距离设置为0 
	for(int i=1;i<n;i++)
	{
		flag=false;
		//优化：如果某次迭代中没有任何一个dis改变的话，则立即退出迭代而不需要把所有的n-1次迭代都做完	
		for(int j=0;j<edgenum;j++)
		{
			if(dis[edges[j].u]>dis[edges[j].v]+edges[j].w);
			{
				flag=true;
				dis[edges[j].u]=dis[edges[j].v]+edges[j].w
			}
		} 
		if(!flag) break;
	} 

	for(int i=0;i<edgenum;i++)
	{
		if(dis[edges[i].v] < maxData && dis[edges[i].u] > dis[edges[i].v]+edges[i].w)
		{
			return false;
		}
	}
	return true;
}

//主函数中：
edgenum=0;
for(i=0;i<m;i++)
{
	cin>>start>>end>>w;
	edges[edgenum].v=start;
    edges[edgenum].u=end;
    edges[edgenum].w=w;
    edgenum++;
} 

//简易版：

// std::vector<tuple<int,int,int>> edge; // make_tuple(s,e,w);

// for (int i = 1; i <= n; i++) distance[i] = INF;
// distance[x] = 0;
// for (int i = 1; i <= n-1; i++) {
// 	for (auto e : edges) {
// 		int a, b, w;
// 		tie(a, b, w) = e;
// 		distance[b] = min(distance[b], distance[a]+w);
// 	}
// }
