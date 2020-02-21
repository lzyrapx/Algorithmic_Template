#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
 * O(N^(2/3))
 * declare in global or heap
 */
struct Melssel_Lehmer
{
    static const int N = 6e6 + 2;
    bool notprime[N];
    int prime[N], pi[N];
    static const int M = 7;
    static const int PM = 2 * 3 * 5 * 7 * 11 * 13 * 17;
    int phi[PM + 1][M + 1], sz[M + 1];
    Melssel_Lehmer()
    {
        int cnt = 0;
        notprime[0] = notprime[1] = true;
        pi[0] = pi[1] = 0;
        for (int i = 2; i < N; ++i)
        {
            if (!notprime[i])
                prime[++cnt] = i;
            pi[i] = cnt;
            for (int j = 1; j <= cnt && i * prime[j] < N; ++j)
            {
                notprime[i * prime[j]] = true;
                if (i % prime[j] == 0)
                    break;
            }
        }
        sz[0] = 1;
        for (int i = 0; i <= PM; ++i)
            phi[i][0] = i;
        for (int i = 1; i <= M; ++i)
        {
            sz[i] = prime[i] * sz[i - 1];
            for (int j = 1; j <= PM; ++j)
                phi[j][i] = phi[j][i - 1] - phi[j / prime[i]][i - 1];
        }
    }
    int sqrt2(ll x)
    {
        ll r = (ll)sqrt(x - 0.1);
        while (r * r <= x)
            ++r;
        return r - 1;
    }
    int sqrt3(ll x)
    {
        ll r = (ll)cbrt(x - 0.1);
        while (r * r * r <= x)
            ++r;
        return r - 1;
    }
    ll getphi(ll x, ll s)
    {
        if (s == 0)
            return x;
        if (s <= M)
            return phi[x % sz[s]][s] + (x / sz[s]) * phi[sz[s]][s];
        if (x <= prime[s] * prime[s])
            return pi[x] - s + 1;
        if (x <= prime[s] * prime[s] * prime[s] && x < N)
        {
            int s2x = pi[sqrt2(x)];
            ll ans = pi[x] - (s2x + s - 2) * (s2x - s + 1) / 2;
            for (int i = s + 1; i <= s2x; ++i)
                ans += pi[x / prime[i]];
            return ans;
        }
        return getphi(x, s - 1) - getphi(x / prime[s], s - 1);
    }
    // https://oeis.org/A006880
    ll getpi(ll x) // return number of primes < 10^n. (1 <= n <= 13) faster
    {
        if (x < N)
            return pi[x];
        ll ans = getphi(x, pi[sqrt3(x)]) + pi[sqrt3(x)] - 1;
        for (int i = pi[sqrt3(x)] + 1, ed = pi[sqrt2(x)]; i <= ed; ++i)
            ans -= getpi(x / prime[i]) - i + 1;
        return ans;
    }
    // https://oeis.org/A006880
    ll solve(ll x) // return number of primes < 10^n. (1 <= n <= 13) slower
    {
        if (x < N)
            return pi[x];
        int a = (int)solve(sqrt2(sqrt2(x)));
        int b = (int)solve(sqrt2(x));
        int c = (int)solve(sqrt3(x));
        ll sum = getphi(x, a) + (ll)(b + a - 2) * (b - a + 1) / 2;
        for (int i = a + 1; i <= b; i++)
        {
            ll w = x / prime[i];
            sum -= solve(w);
            if (i > c)
                continue;
            ll lim = solve(sqrt2(w));
            for (int j = i; j <= lim; j++)
            {
                sum -= solve(w / prime[j]) - (j - 1);
            }
        }
        return sum;
    }
};
Melssel_Lehmer solver;

int main(int argc, char *argv[])
{
    cout << solver.getpi(10) << endl;
    cout << solver.getpi(100) << endl;
    cout << solver.getpi(1000) << endl;
    cout << solver.getpi(10000) << endl;
    clock_t start, end;
    start = clock();
    cout << solver.getpi(1e13) << endl;
    end = clock();
    printf("spent time=%f\n", (float)(end - start) * 1000 / CLOCKS_PER_SEC);
    start = clock();
    cout << solver.solve(1e13) << endl;
    end = clock();
    printf("spent time=%f\n", (float)(end - start) * 1000 / CLOCKS_PER_SEC);
    return 0;
}