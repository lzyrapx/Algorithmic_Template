/*
 * @Author: zhaoyang.liang
 * @Github: https://github.com/LzyRapx
 * @Date: 2020-02-21 21:25:47
 */
// E(n) be the nth positive eleven-free integer. 
// find E(1e18)
// Aho-Corasick automaton
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
typedef long long ll;

const int maxn = 1e4;
int trie[maxn][10];
int cntword[maxn]; // 记录该单词出现次数
int fail[maxn];
int cnt = 0;
long long dp[20][maxn];

void insertWords(string s){
    int root = 0;
    for(int i = 0;i < s.size();i++){
        int next = s[i] - '0';
        if(!trie[root][next]) {
          memset(trie[cnt],0,sizeof(trie[cnt]));
          trie[root][next] = ++cnt;
        }
        root = trie[root][next];
    }
    cntword[root]++;
}
void getFail(){
    queue<int>q;
    for(int i = 0;i <= 9; i++){
        if(trie[0][i]){
            fail[trie[0][i]] = 0;
            q.push(trie[0][i]);
        }
    }
    while(!q.empty()){
        int now = q.front();
        q.pop();
        for(int i = 0;i <= 9; i++) {
            if(trie[now][i]) {
                fail[trie[now][i]] = trie[fail[now]][i];
                if(cntword[fail[trie[now][i]]]) {
                  ++cntword[trie[now][i]];
                }
                q.push(trie[now][i]);
            }
            else {
                trie[now][i] = trie[fail[now]][i];
            }   
        }
    }
}
int query(string s) {
    int now = 0,ans = 0;
    for(int i = 0; i < s.size(); i++){    
        now = trie[now][s[i] - '0']; 
        for(int j = now; j > 0 && cntword[j] != -1; j = fail[j]){
            ans += cntword[j];
            cntword[j] = -1;
        }
    }
    return ans;
}
int digit[maxn];
ll dfs(int dep,int state, bool ending)
{
    if(dep <= -1) return cntword[state] == 0;
    if(ending == 0 && dp[dep][state] != -1) return dp[dep][state];
    int End = ending ? digit[dep] : 9;
    ll ans = 0;
    for(int i = 0; i <= End; i++)
    {
        if(cntword[trie[state][i]]) continue;
        ans += dfs(dep-1, trie[state][i],ending && i == End);
    }
    if(ending == 0) dp[dep][state] = ans;
    return ans;
}
ll calc(ll x) {
    if(x == 0) return 0;
    int len = 0;
    while(x > 0)
    {
        digit[len++]= x % 10;
        x /= 10;
    }
    return dfs(len - 1, 0, 1) - 1;
}
int main() {
    ll N;
    cin >> N;
    memset(dp, -1, sizeof(dp));
    memset(trie, 0, sizeof(trie));
    memset(fail, -1, sizeof(fail));
    memset(cntword, 0, sizeof(cntword));
    ll ans = 1;
    // string s = "";
    while(ans <= N / 11)
    {
        ans *= 11;
        int cnt = 0;
        string s = "";
        ll tmp = ans;
        while(tmp > 0)
        {
            s = s + to_string(tmp % 10);
            cnt++;
            tmp /= 10;
        }
        for(int i = 0; i < cnt / 2; i++) {
            swap(s[i], s[cnt - 1 - i]);
        }
        // cout << "cnt = " << cnt << endl;
        // cout << "s = " << s << endl;
        insertWords(s);
    }
    getFail();
    calc(N * 9);
    
    ll l = N, r = 8 * N;
    while(l < r) {
        ll mid = (l + r) / 2;
        ll ans = calc(mid);
        if(ans < N) {
            l = mid + 1;
        }
        else {
            r = mid;
        }
    }
    cout << l << endl;
    // ans = 1295552661530920149
    return 0;
}