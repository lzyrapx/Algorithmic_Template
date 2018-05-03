
// 求无向图的最小生成树的主要算法有：prim算法和Kruskal算法
// 最小生成树：prim算法 

//算法的实现模板：

#define MIN INT_MAX
#define MAX_Point 120   //最大顶点数 
#define MAX_Edge 14400  //最大的边数 
int flag1 =0;
double sum;
double arr_list[MAX_Point][MAX_Point]; 
struct Edge
{
	int point;
	double lowcost;
	int flag;
};
Edge edge[MAX_Edge];

double prim(int n)
{
	int k=1,flag = 0;
	double min,sum2=0;
	int j=1;
	for(int i=1;i<=n;i++)
	{
		if(i!=j)
		{
			edge[i].point=i;
			edge[i].lowcost=arr_list[j][i];
			edge[i].flag=0;
		}
	}
	edge[j].lowcost=0;
	edge[j].flag=1;
	for(int i=2;i<=n;i++)
	{
		k=1;
		min=MIN;
		flag=0;
		for(int j=2;j<=n;j++)
		{
			if(edge[j].flag==0 && edge[j].lowcost<min)
			{
				k=j;
				min=edge[j].lowcost;
				flag=1;
			}
		}
		if(!flag) return -1;
		sum2+=min;
		edge[k].flag=1;
		for(int j=2;j<=n;j++)
		{
			if(edge[j].flag==0 && arr_list[k][j]<edge[j].lowcost)
			{
				edge[j].point=k;
				edge[j].lowcost=arr_list[k][j];
			}
		}
	}
	return sum2;
}