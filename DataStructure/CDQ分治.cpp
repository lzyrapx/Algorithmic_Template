
/*
CDQ分治解决高维数点问题
以经典的陌上花开例题为例~
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 200010;
const int mod = 1e9 + 7;

// https://www.lydsy.com/JudgeOnline/problem.php?id=3262
// 一朵花的级别是它拥有的美丽能超过的花的数量
// 统计评级为 0...n-1的每级花的数量
// solution :  O(n*logn*logn)

int n,k;

int s[maxn];
int ans[maxn];

struct Query
{
  int x,y,z;
  int ans,cnt;
}a[maxn],q[maxn];

inline int lowbit(int x)
{
  return x&(-x);
}
void update(int pos,int val)
{
  while(pos <= k) {
    s[pos] += val;
    pos += lowbit(pos);
  }
}
int query(int pos)
{
  int res = 0;
  while(pos > 0) {
    res += s[pos];
    pos -= lowbit(pos);
  }
  return res;
}

bool cmpy(Query a, Query b)
{
  if(a.y == b.y) return a.z < b.z;
  return a.y < b.y;
}

void cdq(int l, int r)
{
  if(l >= r) return;
  int mid = (l + r) >> 1;
  cdq(l, mid);
  cdq(mid + 1, r);
  // 每次把平分的两个数组进行排序
  sort(q + l, q  +  mid + 1, cmpy);
  sort(q + mid + 1, q + r + 1, cmpy);

  // 然后扫一遍.
  // 因为排过序.
  // 所以如果对于[low,mid]里的 i 对[mid+1,r]里的 j 有贡献的话，
  // 那么它对 j+1 也是有贡献的

  // 单独处理前一部分和处理前一部分对后一部分的影响，就是 CDQ 分治
  int low = l, high = mid + 1;
  for(high = mid + 1; high <= r; high ++)
  {
    while(low <= mid && q[low].y <= q[high].y)
    {
      update(q[low].z,q[low].cnt);
      low++;
    }
    // 统计树状数组中所有下标小于等于 q.z 的值之和累加到 q.ans中
    q[high].ans += query(q[high].z);
  }
  // 最后要去掉[l,low-1]的贡献, 相当于撤销操作
  // std::cout << "low = " << low << '\n';
  for(int i = l; i < low; i++) {
    update(q[i].z ,-q[i].cnt);
  }
}
bool cmpx(Query a, Query b)
{
   if(a.x == b.x && a.y == b.y) return a.z < b.z;
   else if(a.x == b.x) return a.y < b.y;
   return a.x < b.x;
}
int main(int argc, char const *argv[]) {
  // freopen("in.txt","r",stdin);
  std::cin >> n >> k;
  for(int i = 1; i <= n; i++) {
    std::cin >> a[i].x >> a[i].y >> a[i].z;
  }
  sort(a + 1, a + n + 1, cmpx); // 排序去掉其中一维
  int cnt = 0;
  int id = 0;
  for(int i = 1; i <= n; i++) {
    cnt ++; // 对于完全相同的点可以先合并起来, 后面统计在加起来=(q[i].cnt - 1)
    if(a[i].x != a[i+1].x || a[i].y != a[i+1].y || a[i].z != a[i+1].z)
    {
      q[++id] = a[i];
      q[id].cnt = cnt;
      cnt = 0;
    }
  }
  // std::cout << "id = " << id << '\n';
  cdq(1,id);
  // 最后统计评级为0...n-1的每级花的数量，n-1最高，即其他花都不能比
  for(int i = 1; i <= id; i++) {
    // std::cout << "ans = " << q[i].ans << '\n';
    ans[q[i].ans + (q[i].cnt - 1)] += q[i].cnt; // (q[i].cnt - 1) 表示被合并的，和 i 一样的其它的花，不算自己
  }
  for(int i = 0; i < n; i++) {
    std::cout << ans[i] << '\n';
  }
  return 0;
}
