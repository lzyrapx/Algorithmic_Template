/*   
曼哈顿距离MST   O(n*logn)
性质：对于某个点，以他为中心的区域分为8个象限，对于每一个象限，只会取距离最近的一个点连边。
建图方法：
我们把所有的点按照x从小到大排序：x1≤x2≤…≤xn。
建立一个抽象数据结构T。T中的每个元素对应平面上的一个点(x,y)，该元素的第一关键字等于y-x，第二关键字等于y+x。
从Pn到P1逐个处理每个点。处理Pk的时候，令Pk+1, Pk+2, …, Pn都已经存入到T
中。某个点Q(x,y)如果落在Pk的R1区间内，必须满足：
1.       x≥xk
2.       y-x>yk-xk
要满足第一个条件，Q必须属于集合{Pk+1, Pk+2, …, Pn}，即Q必然在T中。
要满足第二个条件，Q在T中的第一关键字必须大于yk-xk(定值)。
因为我们要使得|PkQ|最小，所以我们实际上就是：从T的第一关键字大于某常数的所有元素中，寻找第二关键字最小的元素。
很明显，T可以用平衡二叉树来实现。按照第一关键字有序来建立平衡树，对于平衡树每个节点都记录以其为根的子树中第二关
键字最小的是哪个元素。查询、插入的时间复杂度都是O(logn)。
平衡二叉树也可以用线段树代替。
这里的代码用的BIT维护！
坐标变化：
   R1->R2：关于y=x对称，swap(x,y)
   R2->R3：考虑到代码的方便性，我们考虑R2->R7，x=-x。
   R7->R4：因为上面求的是R2->R7，因此这里还是关于y=x对称。   
 */
  

const int INF=0x3f3f3f3f;
   
struct Point{
    int x,y,id;
    bool operator<(const Point p)const{
        return x!=p.x?x<p.x:y<p.y;
    }
}p[N];
struct BIT{
    int min_val,pos;
    void init(){
        min_val=INF;
        pos=-1;
    }
}bit[N];
struct Edge{
    int u,v,d;
    bool operator<(const Edge e)const{
        return d<e.d;
    }
}e[N<<2];
int T[N],hs[N];
int n,mt,pre[N];

void addedge(int u,int v,int d)
{
    e[mt].u=u,e[mt].v=v;
    e[mt++].d=d;
}

int find(int x)
{
    return pre[x]=(x==pre[x]?x:find(pre[x]));
}
int dist(int i,int j)
{
    return abs(p[i].x-p[j].x)+abs(p[i].y-p[j].y);
}

inline int lowbit(int x)
{
    return x&(-x);
}

void update(int x,int val,int pos)
{
    for(int i=x;i>=1;i-=lowbit(i)){
        if(val<bit[i].min_val) {
            bit[i].min_val=val,bit[i].pos=pos;
        }
    }
}

int query(int x,int m)
{
    int min_val=INF,pos=-1;
    for(int i=x;i<=m;i+=lowbit(i)) {
        if(bit[i].min_val<min_val) {
            min_val=bit[i].min_val,pos=bit[i].pos;
        }
    }
    return pos;
}

int Manhattan_minimum_spanning_tree(int n,Point *p, int K)
{
    int w,fa,fb,pos,m;
    //Build graph
    mt=0;
    for(int dir=0;dir<4;dir++){
        //Coordinate transform - reflect by y=x and reflect by x=0
        if(dir==1||dir==3){
            for(i=0;i<n;i++)
                swap(p[i].x,p[i].y);
        }
        else if(dir==2){
            for(i=0;i<n;i++){
                p[i].x=-p[i].x;
            }
        }
        //Sort points according to x-coordinate
        sort(p,p+n);
        //Discretize
        for(int i=0;i<n;i++){
            T[i]=hs[i]=p[i].y-p[i].x;
        }
        sort(hs,hs+n);
        m=unique(hs,hs+n)-hs;
        //Initialize BIT
        for(int i=1;i<=m;i++)
            bit[i].init();
        //Find points and add edges
        for(int i=n-1;i>=0;i--){
            pos=lower_bound(hs,hs+m,T[i])-hs+1;   //BIT中从1开始'
            w=query(pos,m);
            if(w!=-1) {
                addedge(p[i].id,p[w].id,dist(i,w));
            }
            update(pos,p[i].x+p[i].y,i);
        }
    }
    //Kruskal - 找到第K小的边
    sort(e,e+mt);
    for(int i=0;i<n;i++)pre[i]=i;
    for(int i=0;i<mt;i++){
        fa=find(e[i].u);
        fb=find(e[i].v);
        if(fa!=fb){
            K--;
            pre[fa]=fb;
            if(K==0)return e[i].d;
        }
    }
}
