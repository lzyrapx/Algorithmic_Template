// 狄利克雷卷积：
// 对于两个算术函数f和g，定义其狄利克雷卷积为f*g，其中f*g(n)=\sum_{d|n}
// f(d)g(n/d)}
// 狄利克雷卷积满足很多性质：
// 交换律：f*g=g*f,
// 结合律：(f*g)*h=f*(g*h)
// 逐点加法的分配律：f*(g+h)=f*g+f*h。
// 若f,g是积性函数，那么f*g也是积性函数。
// 狄利克雷卷积可以用O(nlogn)的筛法预处理出来。无脑枚举所有数的倍数。
// http://jcvb.is-programmer.com/posts/41846.html
int f[MAXN], g[MAXN], h[MAXN] = {0};
void calc(int n) {
  for (int i = 1; i * i <= n; i++)
    for (int j = i; i * j <= n; j++)
      if (j == i)
        h[i * j] += f[i] * g[i];
      else
        h[i * j] += f[i] * g[j] + f[j] * g[i];
}