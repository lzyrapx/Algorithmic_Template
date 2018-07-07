#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100 + 10;
char s[N];
ll fact[N];
void init()//阶乘表，这里仅打表到20
{
    fact[0] = 1;
    for(int i = 1; i <= 20; i++) fact[i] = i * fact[i-1];
}
ll Cantor_expansion(char *s)
{
    ll res = 0;
    int len = strlen(s);
    for(int i = 0; s[i]; i++)
    {
        int rnk = 0;
        for(int j = i+1; s[j]; j++)
            if(s[i] > s[j]) rnk++;
        res += rnk * fact[len-i-1];
    }
    return res;
}
void Cantor_inverse_expansion(ll n, int m)
{//n是在全排列中的名次，注意是从0开始计数的，若从1开始计数则要减去1。m是元素个数
    vector<int> num;
    int arr[N], k = 0;
    for(int i = 1; i <= m; i++) num.push_back(i);
    for(int i = m; i >= 1; i--)
    {
        ll r = n % fact[i-1];
        ll t = n / fact[i-1];
        n = r;
        sort(num.begin(), num.end());
        arr[k++] = num[t];
        num.erase(num.begin() + t);
    }
    for(int i = 0; i < k; i++) printf("%d", arr[i]);
    printf("\n");
}
int main()
{
    init();
    while(~ scanf("%s", s))
    {
        int len = strlen(s);
        ll res = Cantor_expansion(s);//求出此排列的名次
        printf("%lld\n", res);
        Cantor_inverse_expansion(res, len);//根据排列的名次复原此排列
    }
    return 0;
}