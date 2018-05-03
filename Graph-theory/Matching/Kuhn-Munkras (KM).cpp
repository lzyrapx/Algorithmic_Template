#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;  // NOLINT
const int INF = 0x3f3f3f3f;

// O(n^3)

// return largest macthing.(A interger)
template<typename T>
T KM(vector<vector<T>>& mp)
{
    int n = mp.size();  // left num
    int m = mp[0].size();  // right num
    static vector<int> rlink; //, llink;  // right link to left, left link to right
    //llink.resize(n), fill(llink.begin(), llink.end(), -1);
    rlink.resize(m);
    fill(rlink.begin(), rlink.end(), -1);
    vector<T> fl, fr;  // flag num
    fl.resize(n);
    fill(fl.begin(), fl.end(), -INF);
    fr.resize(m);
    fill(fr.begin(), fr.end(), 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fl[i] = max(fl[i], mp[i][j]);
        }
    }
    static vector<T> slack;
    slack.resize(m);
    static vector<int> lused, rused;  // record used point in a dfs
    lused.resize(n), rused.resize(m);
    static function<bool(int)> dfs = [&](int k) {  // find a method that can make k link to right
        lused[k] = 1;
        for (int i = 0; i < m; i++) {
            if (mp[k][i] == -INF || rused[i]) continue;
            T tmp = fl[k] + fr[i] - mp[k][i];
            if (!tmp) {
                rused[i] = 1;
                if (rlink[i] == -1 || dfs(rlink[i])) {
                    rlink[i] = k;  // make or change link
                    // llink[k] = i;
                    return true;
                }
            } else slack[i] = min(slack[i], tmp);
        }
        return false;
    };
    for (int d = 0; d < n; d++) {
        fill(slack.begin(), slack.end(), INF);
        while (1) {
            fill(lused.begin(), lused.end(), 0);
            fill(rused.begin(), rused.end(), 0);
            if (dfs(d)) break;
            T e = INF;
            for (int i = 0; i < m; i++) {  // min slack
                if (!rused[i]) e = min(e, slack[i]);
            }
            if (e == INF) return -1;
            for (int i = 0; i < n; i++) {
                if (lused[i]) fl[i] -= e;
            }
            for (int i = 0; i < m; i++) {
                if (rused[i]) fr[i] += e;
                else if (mp[d][i] != -INF) slack[i] -= e;
            }
        }
    }
    T res = 0;
    for (int i = 0; i < n; i++) {
        res += mp[rlink[i]][i];
    }
    return res;
}
int n;
int main(int argc, char const *argv[]) {

  std::cin >> n;
  std::vector<std::vector<int>> mp(n+1,std::vector<int>(n+1,0));
  for(int i=0;i<6;i++) {
      int u,v;
      std::cin >> u >> v;
      u--;v--;
      mp[u][v] = 1;
    }

  std::cout << KM(mp) << '\n';
  return 0;
}
/*
8
1 5
2 7
3 8
3 6
3 5
4 6

answer:
4
*/
