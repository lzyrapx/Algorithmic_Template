/*
有些问题中，只算出一个顶点到其他顶点的最短路径是不够的，需要算出每对顶点的最短距离，如果多次运行dijkstra算法，
则编程或者时间复杂度过高，所以有一种编程简单，时间效率更高的算法---Floyd算法

Floyd算法：可以是无向图或有向图，边权可正可负，唯一要求是不能有负环。 
*/

const int maxn=1001;

//mat存储图的信息
//dist存储最短长度
//pre存储i到j路劲中j的前一节点

int n; //n个点
void floyd()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			dist[i][j]=mat[i][j];
			pre[i][j]=i;
		}
		for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)
		{
			if(dist[i][k]!=INT_MAX && dist[k][j]!=INT_MAX &&dist[i][k]+dist[k][j]<dist[i][j])
				{
					dist[i][j]=dist[i][k]+dist[k][j];
					pre[i][j]=pre[k][j];
				}
		}
	}
}
