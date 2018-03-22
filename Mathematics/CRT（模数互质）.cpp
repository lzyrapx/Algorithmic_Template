
//Chinese-Remainder-Theorem
// 模必须互质
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// a solution of ax + by = gcd(a, b)
void extend_Euclid(ll a, ll b, ll *x, ll *y, ll *g)
{
	if(a == 0)
	{
		*x = 0, *y = 1 , *g = b;
		return;
	}
	ll x1,y1;
	extend_Euclid(b%a, a, &x1, &y1, g);
	*x = y1 - (b/a)*x1;
	*y = x1;
}
//Chinese-remainder-theorem
ll crt(ll* a, ll* w, int len)//a存放的是余数，w存放的是两两互质的模数
{
	ll P = 1;
	for(int i=0; i<len; i++) P*=w[i];
	ll x = 0;
	for(int i=0; i<len; i++)
	{
		ll M, m, g, Ni = P/w[i];
		extend_Euclid(Ni , w[i], &M, &m, &g);
		x += a[i] * M % P * Ni % P;
		x %= P;
	}
	if(x < 0) x+=P;
	return x % P;
}

ll a[123];//余数
ll w[132];//两两互质的模数
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%lld%lld",&a[i],&w[i]);
	}
	ll ans=crt(a,w,n);
	cout<<ans<<endl;
  return 0;
}

/*
3
3 5
4 7
2 3

answer:
53

x = 3 mod 5
x = 4 mod 7
x = 2 mod 3
can create an infinite number of other
solutions,such as:
x = 3·21·1+4·15·1+2·35·2 = 263
*/
