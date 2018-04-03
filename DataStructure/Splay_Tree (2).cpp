
//区间翻转：https://loj.ac/problem/105
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const int maxm = 100010;
int a[maxn];
int n, m;
namespace SplayTree{
    int siz[maxn], fa[maxn], ma[maxn], rev[maxn], lazy[maxn], val[maxn]; //siz代表节点的sz，fa代表父亲节点,ma代表最大值,rev翻转标记
    //lazy 区间+, val 值
    int ch[maxn][2], tot, root; //tot代表开新节点的时间戳,root代表splay的树根，ch[i][2],i的左右儿子
    void newnode(int &rt, int father, int k){
        rt = ++tot;
        siz[rt] = 1, fa[rt] = father;
        ma[rt] = val[rt] = k;
        rev[rt] = lazy[rt] = ch[rt][0] = ch[rt][1] = 0;
    }
    void pushup(int rt){ //pushup 从底向上更新
        siz[rt] = 1, ma[rt] = val[rt];
        if(ch[rt][0] != 0) siz[rt] += siz[ch[rt][0]], ma[rt] = max(ma[rt], ma[ch[rt][0]]);
        if(ch[rt][1] != 0) siz[rt] += siz[ch[rt][1]], ma[rt] = max(ma[rt], ma[ch[rt][1]]);
    }
    void pushdown(int rt){ //pushdown 从上向下更新
        if(!rt) return;
        if(lazy[rt]){ //区间+懒惰标记传递
            int l = ch[rt][0], r = ch[rt][1];
            if(l != 0) ma[l] += lazy[rt], val[l] += lazy[rt], lazy[l] += lazy[rt];
            if(r != 0) ma[r] += lazy[rt], val[r] += lazy[rt], lazy[r] += lazy[rt];
            lazy[rt] = 0;
        }
        if(rev[rt]){ //区间翻转懒惰标记传递
            int l = ch[rt][0], r = ch[rt][1];
            if(l != 0) rev[l] ^= 1, swap(ch[l][0], ch[l][1]);
            if(r != 0) rev[r] ^= 1, swap(ch[r][0], ch[r][1]);
            rev[rt] ^= 1;
        }
    }
    void rotate(int x){ //旋转，把x转到根节点,kind为1代表右旋,kind为0代表左旋
        int y = fa[x], kind = ch[y][1] == x;
        pushdown(y), pushdown(x);
        ch[y][kind] = ch[x][!kind];
        fa[ch[y][kind]] = y;
        ch[x][!kind] = y;
        fa[x] = fa[y];
        fa[y] = x;
        ch[fa[x]][ch[fa[x]][1] == y] = x;
        pushup(y), pushup(x);
    }
    void splay(int x, int goal) //伸展操作,把根为r的子树调整为goal
    {
        while(fa[x] != goal)
        {
            int y = fa[x], z = fa[y];
            if(z == goal) rotate(x);
            else if((ch[y][1] == x) == (ch[z][1] == y)) rotate(y), rotate(x);
            else rotate(x), rotate(x);
        }
        if(goal == 0) root = x;
    }
    void build(int &rt, int l, int r, int father){ //建立一颗空的splaytree
        if(l > r) return;
        int mid = (l + r) / 2;
        newnode(rt, father, a[mid]); //递归申请新节点
        build(ch[rt][0], l, mid - 1, rt);
        build(ch[rt][1], mid + 1, r, rt);
        pushup(rt);
    }
    int find(int x, int k){ //查找第k位置在splaytree中的位置
        pushdown(x);
        int lsum = siz[ch[x][0]] + 1;
        if(lsum == k) return x;
        else if(lsum < k) return find(ch[x][1], k - lsum);
        else return find(ch[x][0], k);
    }
    void update_val(int l, int r, int v){ //区间更新+
        splay(find(root, l), 0);
        splay(find(root, r + 2), root);
        lazy[ch[ch[root][1]][0]] += v;
        ma[ch[ch[root][1]][0]] += v;
        val[ch[ch[root][1]][0]] += v;
    }
    void update_rev(int l, int r){
        splay(find(root, l), 0);
        splay(find(root, r + 2), root);
        int tmp = ch[ch[root][1]][0]; //现在以tmp为根的splaytree就是l,r区间
        rev[tmp] ^= 1;
        swap(ch[tmp][0], ch[tmp][1]);
    }
    int querymax(int l, int r){ //查询区间最大值
        splay(find(root, l), 0);
        splay(find(root, r + 2), root);
        return ma[ch[ch[root][1]][0]];
    }
    void dfs(int x){
        pushdown(x);
        if(ch[x][0]) dfs(ch[x][0]);
        if(val[x] >= 1 && val[x] <= n) printf("%d ",val[x]);
        if(ch[x][1]) dfs(ch[x][1]);
    }
}
using namespace SplayTree;

int main()
{
    scanf("%d %d", &n,&m);
    for(int i=1; i<=n; i++) a[i] = i;
    newnode(root, 0, -1);
    newnode(ch[root][1], root, -1);
    build(ch[ch[root][1]][0],1,n,ch[root][1]);
    pushup(ch[root][1]);
    pushup(root);
    for(int i=1; i<=m; i++){
        int a,b;
        scanf("%d%d",&a,&b);
        update_rev(a,b);
    }
    dfs(root);
    return 0;
}