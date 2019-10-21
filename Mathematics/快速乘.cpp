/*
 * @Author: zhaoyang.liang
 * @Github: https://github.com/LzyRapx
 * @Date: 2019-10-21 22:52:09
 */
#include <iostream>
using namespace std;

typedef long long ll;
ll mul(ll A,ll B,ll mod)
{
    return (A*B-(ll)((long double)A*B/mod)*mod+mod)%mod;
}

int main(int argc, char const *argv[])
{
    cout << mul(100000, 123, 10005) << endl;
    return 0;
}
