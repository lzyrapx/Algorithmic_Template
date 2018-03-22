/**
http://blog.csdn.net/tree__water/article/details/52140927?locationNum=11

Chinese-Remainder-Theorem

中国剩余定理（模数不必不互质）

模数不互质可以通过合并方程组来求解。
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll Mod;

ll gcd(ll a, ll b)
{
    if(b==0)
        return a;
    return gcd(b,a%b);
}

ll Extend_Euclid(ll a, ll b, ll&x, ll& y)
{
    if(b==0)
    {
        x=1,y=0;
        return a;
    }
    ll d = Extend_Euclid(b,a%b,x,y);
    ll t = x;
    x = y;
    y = t - a/b*y;
    return d;
}

//a在模n乘法下的逆元，没有则返回-1
ll inv(ll a, ll n)
{
    ll x,y;
    ll t = Extend_Euclid(a,n,x,y);
    if(t != 1)
        return -1;
    return (x%n+n)%n;
}

//将两个方程合并为一个
bool merge(ll a1, ll n1, ll a2, ll n2, ll& a3, ll& n3)
{
    ll d = gcd(n1,n2);
    ll c = a2-a1;
    if(c%d)
        return false;
    c = (c%n2+n2)%n2;
    c /= d;
    n1 /= d;
    n2 /= d;
    c *= inv(n1,n2);
    c %= n2;
    c *= n1*d;
    c += a1;
    n3 = n1*n2*d;
    a3 = (c%n3+n3)%n3;
    return true;
}

//求模线性方程组x=ai(mod ni),ni可以不互质
ll crt(int len, ll* a, ll* n)
{
    ll a1=a[0],n1=n[0];
    ll a2,n2;
    for(int i = 1; i < len; i++)
    {
        ll aa,nn;
        a2 = a[i],n2=n[i];
        if(!merge(a1,n1,a2,n2,aa,nn))
            return -1;
        a1 = aa;
        n1 = nn;
    }
    Mod = n1;
    return (a1%n1+n1)%n1;
}
ll a[1000],b[1000];
int main()
{

    int n;  // n个同余方程组
    while(scanf("%d",&n)!=EOF)
    {
        for(int i = 0; i < n; i++)
            scanf("%I64d %I64d",&a[i],&b[i]);
        printf("%I64d\n",crt(n,a,b));
    }
    return 0;
}
