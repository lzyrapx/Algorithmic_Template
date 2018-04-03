
/*
CDQ分治解决高维数点问题

*/

const int N = 401000;

int n,m;

typedef struct seg{
	int x,y,z,kind,id;
}seg;

seg v[N],quryx[N];

int c[N],maxv,ans[N];

bool cmpx(seg a,seg b){
	return a.x < b.x || (a.x == b.x && a.kind < b.kind);
}

bool cmpy(seg a,seg b){
	return a.y < b.y || (a.y == b.y && a.kind < b.kind);
}

int lowbit(int x){return x & (-x);}

int add(int x,int v){
	for (;x <= maxv;x += lowbit(x))
		c[x] += v;
}

int sum(int x){
	int ans = 0;
	for (;x;x -= lowbit(x))
		ans += c[x];
	return ans;
}

void xsolve(int l,int r){
	if (l >= r) return;
	for (int i = l;i <= r;i++){
		if (quryx[i].kind == 0) add(quryx[i].z,1);
		else ans[quryx[i].id] += sum(quryx[i].z);
	}
	for (int i = l;i <= r;i++){
		if (quryx[i].kind == 0) add(quryx[i].z,-1);
	}
}

void solve(int l,int r){
	if (l >= r) return;
	int mid = (l + r) >> 1;
	solve(l,mid);
	solve(mid+1,r);
	int num = 0;
	for (int i = l;i <= mid;i++)
		if (v[i].kind == 0) quryx[++num] = v[i];
	for (int i = mid+1;i <= r;i++)
		if (v[i].kind) quryx[++num] = v[i];
	sort(quryx+1,quryx+num+1,cmpy);
	xsolve(1,num);
}


int main(){
	int T; cin >> T;
	while(T--){
		scanf("%d",&n);
		memset(c,0,sizeof(c));
		memset(ans,0,sizeof(ans));
		memset(v,0,sizeof(v));
		for (int i = 1;i <= n;i++){
			scanf("%d%d%d",&v[i].x,&v[i].y,&v[i].z);
			v[n + i] = v[i];
			v[n + i].kind = 1;
			v[i].id = v[i + n].id = i;
			maxv = max(maxv,v[i].x);
			maxv = max(maxv,v[i].y);
			maxv = max(maxv,v[i].z);
		}
		sort(v+1,v+2*n+1,cmpx);
		solve(1,2*n);
		for (int i = 1;i <= n;i++)
            printf("%d\n",ans[i] - 1);
	}
}