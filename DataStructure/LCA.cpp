/*   LCA    */


/*    

	DFS+ST    
	预处理：O( n*logn )
	查询：O(1)
  DFS处理：
     T=<V,E>，其中V={A,B,C,D,E,F,G},E={AB,AC,BD,BE,EF,EG},且A为树根。
     则图T的DFS结果为：A->B->D->B->E->F->E->G->E->B->A->C->A
  ST处理d[]数组
  dis为深度遍历计数
  d[]为树遍历节点的深度
  E[]为树遍历的节点的标号
  R[i]表示E数组中第一个值为i的元素下标
  f[i][j]为深度遍历[i,j]区间的最小深度的深度遍历编号
  如果有n个节点,那么E[]和R[]下标范围为2*n-1
  rmq下标范围为[1,n]
  注意他们的最近公共祖先为他们本身的情况!!!       

 */


struct Edge
{
    int u,v;
}e[N];
int first[N],next[N],f[N][20],d[N],E[N],R[N],vis[N];
int T,n,m,mt,dis,root;

void addedge(int a,int b)
{
    e[mt].u=a;
    e[mt].v=b;
    next[mt]=first[a]；
    first[a]=mt++;
}

int Minele(int i,int j)   //比较距离来获取下标
{
    return d[i]<d[j]?i:j;
}

void rmq_init(int n)
{
    int i,j;
    for(i=1;i<=n;i++)f[i][0]=i;
    for(j=1;(1<<j)<=n;j++){
        for(i=1;i+(1<<j)-1<=n;i++){
            f[i][j]=Minele(f[i][j-1],f[i+(1<<(j-1))][j-1]);
        }
    }
}

int rmq(int l,int r)
{
    int k=0;
    while((1<<(k+1))<=r-l+1)k++;
    return Minele(f[l][k],f[r-(1<<k)+1][k]);
}

void dfs(int u,int deep)
{
    d[dis]=deep;
    E[dis]=u;
    R[u]=dis++;
    int i;
    for(i=first[u];i!=-1;i=next[i]){
        dfs(e[i].v,deep+1);
        d[dis]=deep;
        E[dis++]=u;
    }
}

// O(n*logn)
void LCA_Init()
{
    dis=1;  //初始化为1
    dfs(root,0);   //传递根节点和深度
    rmq_init(2*n-1);  //传递E[]和R[]的长度
}

// o(1)
int LCA(int a,int b)   //返回a和b节点的最近祖先节点标号,注意他们的最近公共祖先为他们本身的情况 
{
    int left=R[a],right=R[b];
    if(left>right)swap(left,right);
    return E[rmq(left,right)];
}
