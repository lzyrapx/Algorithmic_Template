#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const long double PI=std::acos(-1);
const int maxn = 5e5+100;
const int M = 32768;

// https://www.luogu.org/problemnew/show/P4245
// 求两个多项式的卷积,系数对P取模,不保证P可以分解成P = a*2^k-1
// 即对NTT不适合的情况，就是任意模的情况
/*
MTT就是：
拆系数+FFT
基本上就是找个模数 
然后拆成4个多项式，分别是第一个多项式 / 模数 %模数 第二个多项式 / 模数 %模数 的值 
然后两两相乘，结果 乘上对应项数的模数次方然后%要取的模数 
这样的话是做4次DFT，4次IDFT 
然而单位复根的精度会出问题 
可以预处理，注意精度问题，开long double
*/

struct Complex{
    long double real,imag;
    Complex(){};
    Complex(long double _real,long double _imag):real(_real),imag(_imag){}
};
inline Complex operator + (Complex x,Complex y){return (Complex){x.real+y.real,x.imag+y.imag};}
inline Complex operator - (Complex x,Complex y){return (Complex){x.real-y.real,x.imag-y.imag};}
inline Complex operator * (Complex x,Complex y){return (Complex){x.real*y.real-x.imag*y.imag,x.real*y.imag+y.real*x.imag};}
int F[maxn],G[maxn],rev[maxn];
int l;
inline void FFT(Complex *a,int n,int f)
{
    for(int i=0;i<n;i++) {
      rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
    }
    for(int i=0;i<n;i++) {
      if(i<rev[i]) std::swap(a[i],a[rev[i]]);
    }
    for(int i=1;i<n;i<<=1)
    {
        Complex wn=(Complex){std::cos(PI/i),f*std::sin(PI/i)};
        for(int j=0;j<n;j+=(i<<1))
        {
            Complex w=(Complex){1,0};
            for(int k=0;k<i;k++,w=w*wn)
            {
                Complex x=a[j+k];
                Complex y=a[i+j+k]*w;
                a[j+k]=x+y;
                a[i+j+k]=x-y;
            }
        }
    }
    if(f==1) return;
    for(int i=0;i<n;i++) {
      a[i].real=a[i].real/(long double)n; //保护精度
    }
}
int n,m,p;
ll ans[maxn];
Complex a[maxn],b[maxn],c[maxn],d[maxn],e[maxn],f[maxn],g[maxn],h[maxn];
inline void MTT()
{
    n+=m;
    for(m=1;m<=n;m<<=1) l++;
    for(int i=0;i<n;i++)
    {
        a[i].real=F[i]/M,b[i].real=F[i]%M;
        c[i].real=G[i]/M,d[i].real=G[i]%M;
    }
    // 拆掉系数，分别做 fft
    FFT(a,m,1),FFT(b,m,1),FFT(c,m,1),FFT(d,m,1);
    //卷积写为 a * p = (a * m + b) * (c * m + d) = (a * c * m * m) + (a * m * d) + (b * c * m) + (b * d)
    // 先把他们乘起来，m最后乘进去就行
    for(int i=0;i<m;i++)
    {
        e[i]=a[i]*c[i]; f[i]=a[i]*d[i];
        g[i]=b[i]*c[i]; h[i]=b[i]*d[i];

    }
    FFT(e,m,-1),FFT(f,m,-1),FFT(g,m,-1),FFT(h,m,-1);
    for(int i=0;i<m;i++)
    {
        ans[i]=(ll)(round(e[i].real))%p*M%p*M%p;
        ans[i]+=(ll)(round(f[i].real))%p*M%p;
        ans[i]+=(ll)(round(g[i].real))%p*M%p;
        ans[i]+=(ll)(round(h[i].real))%p;
        ans[i]%=p;
    }
}
int main()
{
    std::cin >> n >> m >> p;
    for(int i=0;i<=n;i++) {
      std::cin >> F[i];
    }
    for(int i=0;i<=m;i++)  {
      std::cin >> G[i];
    }
    MTT(); // F 和 G 的卷积 ans
    for(int i = 0; i <= n; i++) {
      std::cout << ans[i] << ' ';
    }
    std::cout << '\n';
    return 0;
}
