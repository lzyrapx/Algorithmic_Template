#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double eps = 1e-7;
const int maxn = 1e5 + 5;
vector<double> ps[maxn];
int fail[maxn];
double x[maxn], delta[maxn];
int n;
int pn;
/* 
前提：必须符合线性递推，如：
fib: 1 1 2 3 5 8 13 21 34 55 89
*/
int main()
{
    while (~scanf("%d", &n)) // n 项
    {
        pn = 0;
        for (int i = 1; i <= n; i++) {
          scanf("%lf", &x[i]); //前 n项
        }
        for (int i = 1; i <= n; i++)
        {
            double dt = -x[i];
            for (int j = 0; j < (int)ps[pn].size(); j++)
            {
              dt += x[i - j - 1] * ps[pn][j];
            }
            delta[i] = dt;
            if (fabs(dt) <= eps) continue;
            fail[pn] = i;
            if(!pn)
            {
              ps[++pn].resize(1);
              continue;
            }
            vector<double>&ls = ps[pn - 1];
            double k = -dt / delta[fail[pn - 1]];
            vector<double> cur;
            cur.resize(i - fail[pn - 1] - 1);
            cur.push_back(-k);
            for(int j = 0; j < (int)ls.size();j++)
            {
              cur.push_back(ls[j] * k);
            }
            if((int)cur.size() < (int)ps[pn].size())
            {
              cur.resize(ps[pn].size());
            }
            for(int j = 0; j < (int)ps[pn].size(); j++)
            {
              cur[j] += ps[pn][j];
            }
            ps[++pn] = cur;
        }
        int len = (int)ps[pn].size();
        std::cout << "f[i]=" ;
        for (int i = 0; i < len; i++){
            if(ps[pn][i] > 0 && i > 0)std::cout << "+";
            if(ps[pn][i]==0)continue;
            printf("%g*f[i-%d]", ps[pn][i], i+1);
        }
    }
    return 0;
}
