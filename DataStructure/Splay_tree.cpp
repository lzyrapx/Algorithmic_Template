/*  Spaly tree   O(log n)   
[NOI2005]维修数列：http://www.cnblogs.com/zhsl/p/3227535.html （区间反转，求和，删除，改变，最值） */

#define Key_value ch[ch[root][1]][0]
int pre[N],key[N],ch[N][2];  //分别表示父结点，键值，左右孩子(0为左孩子，1为右孩子),根结点，结点数量
int sz[N],st[N];   //子树规模，内存池
int root,tot,top;   //根节点，根节点数量，内存池容量
//题目特定数据
int num[N];
int val[N];
int add[N];
LL sum[N];
int n,m;
//debug部分copy from hh
void Treaval(int x) {
    if(x) {
        Treaval(ch[x][0]);
        printf("结点%2d:左儿子 %2d 右儿子 %2d 父结点 %2d size = %2d ,val = %2d , sum = %2d \n",x,ch[x][0],ch[x][1],pre[x],sz[x],val[x],sum[x]);
        Treaval(ch[x][1]);
    }
}
void debug() {printf("%d\n",root);Treaval(root);}
//以上Debug
//新建一个结点
void NewNode(int &x,int fa,int k)
{
    if(top)x=st[top++];
    else x=++tot;
    pre[x]=fa;
    sz[x]=1;
    val[x]=k;
    add[x]=0;
    sum[x]=k;
    ch[x][0]=ch[x][1]=0;  //左右孩子为空
}

void Push_Up(int x)
{
    sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1;
    sum[x]=sum[ch[x][0]]+sum[ch[x][1]]+val[x]+add[x];
}

void Push_Down(int x)
{
    if(add[x]){
        val[x]+=add[x];
        add[ch[x][0]]+=add[x];
        add[ch[x][1]]+=add[x];
        sum[ch[x][0]]+=(LL)add[x]*sz[ch[x][0]];
        sum[ch[x][1]]+=(LL)add[x]*sz[ch[x][1]];
        add[x]=0;
    }
}

//旋转，kind为1为右旋，kind为0为左旋
void Rotate(int x,int kind)
{
    int y=pre[x],z=pre[y];
    Push_Down(y);
    Push_Down(x);  //先把y的标记向下传递，再把x的标记往下传递
    //类似SBT，要把其中一个分支先给父节点
    ch[y][!kind]=ch[x][kind];
    pre[ch[x][kind]]=y;
    //如果父节点不是根结点，则要和父节点的父节点连接起来
    if(z)ch[z][ch[z][1]==y]=x;
    pre[x]=z;
    ch[x][kind]=y;
    pre[y]=x;
    Push_Up(y);  //维护y结点，不要维护x节点，x节点会再次Push_Down，最后维护一下x节点即可
}
//Splay调整，将根为r的子树调整为goal
void Splay(int x,int goal)
{
    int y,kind;
    while(pre[x]!=goal){
        //父节点即是目标位置，goal为0表示，父节点就是根结点
        y=pre[x];
        Push_Down(pre[y]);Push_Down(y);Push_Down(x);   //涉及到反转操作，要先更新，然后在判断!!
        if(pre[y]==goal){
            Rotate(x,ch[y][0]==x);
        }
        else {
            kind=ch[pre[y]][0]==y;
            //两个方向不同，则先左旋再右旋
            if(ch[y][kind]==x){
                Rotate(x,!kind);
                Rotate(x,kind);
            }
            //两个方向相同，相同方向连续两次
            else {
                Rotate(y,kind);
                Rotate(x,kind);
            }
        }
    }
    //更新根结点
    Push_Up(x);
    if(goal==0)root=x;
}
/*把第k个节点旋转到goal节点下面
注意：是加了两个虚拟节点后，虚拟节点不算，否则需要改为while(sz[ch[x][0]]!=k-1)  */
void RotateTo(int k,int goal)
{
    int x=root;
    Push_Down(x);
    while(sz[ch[x][0]]!=k){
        if(sz[ch[x][0]]>k)
            x=ch[x][0];
        else {
            k-=sz[ch[x][0]]+1;
            x=ch[x][1];
        }
        Push_Down(x);
    }
    Splay(x,goal);
}

int Insert(int k)
{
    int x=root;
    while(ch[x][k>key[x]]){
        //不重复插入
        if(key[x]==k){
            Splay(x,0);
            return 0;
        }
        x=ch[x][k>key[x]];
    }
    NewNode(ch[x][k>key[x]],x,k);
    //将新插入的结点更新至根结点
    Splay(ch[x][k>key[x]],0);
    return 1;
}
//找前驱，即左子树的最右结点
int Get_Pre(int x)
{
    if(!ch[x][0])return -INF;
    x=ch[x][0];
    while(ch[x][1])x=ch[x][1];
    return key[x];
}
//找后继，即右子树的最左结点
int Get_Suf(int x)
{
    if(!ch[x][1])return INF;
    x=ch[x][1];
    while(ch[x][0])x=ch[x][0];
    return key[x];
}
//建树，中间结点先建立，然后分别对区间两端在左右子树建立  
void BuildTree(int &x,int l,int r,int fa)
{
    if(l>r)return;
    int mid=(l+r)>>1;
    NewNode(x,fa,num[mid]);
    BuildTree(ch[x][0],l,mid-1,x);
    BuildTree(ch[x][1],mid+1,r,x);
    Push_Up(x);
}

void Init()
{
    ch[0][0]=ch[0][1]=pre[0]=sz[0]=0;
    add[0]=sum[0]=0;
    root=top=tot=0;
    NewNode(root,0,-1); 
    NewNode(ch[root][1],root,-1);     //头尾各加入一个空位
    sz[root]=2;

    for(int i=0;i<n;i++)
        scanf("%d",&num[i]);
    BuildTree(Key_value,0,n-1,ch[root][1]);    //让所有数据夹在两个-1之间  
    Push_Up(ch[root][1]);
    Push_Up(root);
}

void Update(int a,int b,int c)
{
    RotateTo(a-1,0);
    RotateTo(b+1,root);
    add[Key_value]+=c;
    sum[Key_value]+=sz[Key_value]*c;
}

LL Query(int a,int b)
{
    RotateTo(a-1,0);
    RotateTo(b+1,root);
    return sum[Key_value];
}
//第k个数的节点编号
int Get_Kth(int r,int k)
{
    Push_Down(r);
    int t=size[ch[r][0]]+1;
    if(t==k)return r;
    if(t>k)return Get_Kth(ch[r][0],k);
    else return Get_Kth(ch[r][1],k-t);
}
//内存池，删除的节点入栈
void erase(int r){
    if(!r) return;
    st[++top]=r;
    erase(ch[r][0]);
    erase(ch[r][1]);
}
//删除区间[a,b]的数,加了虚拟节点之后
void Delete(int a,int b)
{
    RotateTo(a-1,0);
    RotateTo(b+1,root);
    erase(Key_value);
    pre[Key_value]=0;
    Key_value=0;
    Push_Up(ch[root][1]);
    Push_Up(root);
}
