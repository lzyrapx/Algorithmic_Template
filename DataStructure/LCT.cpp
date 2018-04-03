const int N = 610000;

int f[N],son[N][2];

int val[N],sum[N],siz[N],mx[N];

int rev[N],flag[N];

void LCTInit(){
	memset(son,0,sizeof(son));
	memset(f,0,sizeof(f));
	memset(rev,0,sizeof(rev));
	memset(val,0,sizeof(val));
	memset(sum,0,sizeof(sum));
	memset(flag,0,sizeof(flag));
	memset(mx,0,sizeof(mx));
}

bool isroot(int x){
	return !f[x] || (son[f[x]][0] != x && son[f[x]][1] != x);
}

void reverse(int x){
	if (!x) return;
	swap(son[x][0],son[x][1]);
	rev[x]^=1;
}

void add(int x,int c){
	if (!x) return;
	sum[x] += c * siz[x];
	val[x] += c;
	mx[x] += c;
	flag[x] += c;
}

void pb(int x){
	if (rev[x])
	reverse(son[x][0]),reverse(son[x][1]),rev[x] = 0;
	if (flag[x])
	add(son[x][0],flag[x]),add(son[x][1],flag[x]),flag[x] = 0;
}

inline void up(int x){
	pb(x); siz[x] = 1; sum[x] = val[x]; mx[x] = val[x];
	if (son[x][0]) siz[x] += siz[son[x][0]],sum[x] += sum[son[x][0]],mx[x] = max(mx[x],mx[son[x][0]]);
	if (son[x][1]) siz[x] += siz[son[x][1]],sum[x] += sum[son[x][1]],mx[x] = max(mx[x],mx[son[x][1]]);
}

inline void rotate(int x){
	int y = f[x],w = son[y][1] == x;
	son[y][w] = son[x][w^1];
	if (son[x][w^1]) f[son[x][w^1]] = y;
	if (f[y]){
		int z = f[y];
		if (son[z][0] == y) son[z][0] = x;
		if (son[z][1] == y) son[z][1] = x;
	}
	f[x] = f[y]; f[y] = x;
	son[x][w^1] = y; up(y);
}

int tmp[N];

void splay(int x){
	int s = 1,i = x,y; tmp[1] = i;
	while(!isroot(i)) tmp[++s] = i = f[i];
	while(s) pb(tmp[s--]);
	while(!isroot(x)){
		y = f[x];
		if (!isroot(y)){
			if ((son[f[y]][0] == y) ^ (son[y][0] == x))
			rotate(x); else rotate(y);
		}
		rotate(x);
	}
	up(x);
}

//核心操作，打通x到目前根的一条链

void access(int x){
	for (int y = 0;x;y = x,x = f[x])
		splay(x),son[x][1] = y,up(x);
}


/* 
	get the root of the current set
	can be used as the union-find set
*/

int root(int x){
	access(x);
	splay(x);
	while(son[x][0]) x = son[x][0];
	return x;
}

void makeroot(int x){
	access(x);
	splay(x);
	reverse(x);
}

void link(int x,int y){
	makeroot(x);
	f[x] = y;
	access(x);
}

void cutf(int x){
	access(x);
	splay(x);
	f[son[x][0]] = 0;
	son[x][0] = 0;
	up(x);
}

void cut(int x,int y){
	makeroot(x);
	cutf(y);
}

int find(int x){
	access(x);
	splay(x);
	int y = x;
	while(son[y][0]) y = son[y][0];
	return y;
}

inline int lca(int x,int y){
	int ans; access(y); y = 0;
	do{
		splay(x); if (!f[x]) ans = x;
		x = f[y = x];
	}while(x);
	return ans;
}

int n,m,x,y;

int main(){

	while(cin >> n){

		LCTInit();

		for (int i = 1;i <= n;i++) siz[i] = 1;

		for (int i = 1;i < n;i++){
			scanf("%d%d",&x,&y);
			link(x,y);
		}

		for (int i = 1;i <= n;i++)
			scanf("%d",&val[i]),mx[i] = sum[i] = val[i];

		int q; scanf("%d",&q);

		while(q--){
			int ty,z,x,y;
			scanf("%d",&ty);
			scanf("%d%d",&x,&y);
			if (ty == 1){
                if (root(x) == root(y)){
                    printf("-1\n");
                    continue;
                }
                link(x,y);
			}
			if (ty == 2){
                if (root(x) != root(y) || x == y){
                    printf("-1\n");
                    continue;
                }
				makeroot(x);
				cutf(y);
			}
			if (ty == 3){
				scanf("%d",&z);
                if (root(z) != root(y)){
                    printf("-1\n");
                    continue;
                }
				makeroot(y);
				access(z);
				splay(z);
				add(z,x);
			}
			if (ty == 4){
                if (root(x) != root(y)){
                    printf("-1\n");
                    continue;
                }
				makeroot(x);
				access(y);
				splay(y);
				printf("%d\n",mx[y]);
			}
		}
		printf("\n");
	}
}