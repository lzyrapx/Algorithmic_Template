
// 带权有向图，求源到其他所有各顶点的最短路径长度。
// 单源最短路径问题，但不能处理带负权边的图 
// 最短路：dijkstra算法

/*
The time complexity of the  implementation is O(n+mlogm), because
the algorithm goes through all nodes of the graph and adds for each edge at most
one distance to the priority queue.
*/

// 算法的实现模板：
#define MaxN 10010 //MaxN是点的个数
#define MaxInt 200000000  //MabInt表示不可达
int map[MaxN][MaxN],dist[MaxN];
bool mark[MaxN];
int start,end;

int dijlstra()
{
	for(int i=1;i<=end;i++) dist[i]=MaxInt;
      memset(mark,0,sizeof(mark));
      dist[start]=0;
      //把起点并入集合，搜索的就可以从起点寻找第一条最短的边了
	  for(int i=1;i<=end-1;i++)
	  {
	  	min1=MaxInt;
	  	for(int j=1;j<=end;j++)  //查找到原集合的最短的边 
	  	{
	  		if(!mark[j] && dist[j]<min1)
	  		{
	  			min1=dist[j];
	  			minj=j;
	  		}
	  	}
	  	mark[minj]=1;
		//每并入一个点都要对原来的变进行修正，保证任意时刻源点到目标点的距离都是最短的 
		  for(int j=1;j<=end;j++)
		  {
		  	if(!mark[j] && map[minj][j]>0)
			  {
			  	temp=dist[minj]+map[minj][j];
			  	if(temp<dist[j]) dist[j]=temp;
			  } 
		  } 
	  } 
	  return dist[end];
}
 
