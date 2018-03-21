#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const double PI = acos(-1);
void rader(vector<complex<double> >& y) {
    int len = y.size();
    int i, j, k;
    for (i = 1, j = len / 2; i < len - 1; i++) {
        if (i < j) swap(y[i], y[j]);
        k = len / 2;
        while (j >= k) {
            j -= k;
            k /= 2;
        }
        if (j < k) j += k;
    }
}
void fft(vector<complex<double> >& y, int on) {
    int len = y.size();
    rader(y);
    for (int h = 2; h <= len; h <<= 1) {
        complex<double> wn(cos(-on * 2 * PI / h), sin(-on * 2 * PI / h));
        for (int j = 0; j < len; j += h) {
            complex<double> w(1, 0);
            for (int k = j; k < j + h / 2; k++) {
                complex<double> u = y[k];
                complex<double> t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
                w = w * wn;
            }
        }
    }
    if (on == -1) for (auto& i : y) i.real(i.real() / len);
}
class BigInt {
 private:
     string num;
     string sign;

 public:
     const string to_string() const {
         if (this->sign == "-") return this->sign + this->num;
         else return this->num;
     }
     const LL toll() { return stoll(this->to_string()); }
     const int toi() { return stoi(this->to_string()); }
     BigInt() : num("0"), sign("+") {}
     BigInt(const int t) {
         if (t < 0) {
             this->num = std::to_string(-t);
             this->sign = "-";
         } else {
             this->num = std::to_string(t);
             this->sign = "+";
         }
     }
     BigInt(const LL t) {
         if (t < 0) {
             this->num = std::to_string(-t);
             this->sign = "-";
         } else {
             this->num = std::to_string(t);
             this->sign = "+";
         }
     }
     BigInt(const string& t) {
         if (t[0] == '-') {
             this->num = t.substr(1);
             this->sign = "-";
         } else {
             this->num = t;
             this->sign = "+";
         }
         int flag = 0;
         while (flag < (int)this->num.length() - 1 && this->num[flag] == '0') flag++;
         this->num = this->num.substr(flag);
     }
     BigInt(char* const t) : BigInt(string(t)) {}
     friend bool operator< (const BigInt& t, const BigInt& s) {
         if (t.sign != s.sign) {
             if (t.sign == "-") return true;
             else return false;
         } else {
             if (t.sign == "-") {
                 if (t.num.length() == s.num.length()) {
                     return t.num > s.num;
                 } else {
                     return t.num.length() > s.num.length();
                 }
             } else {
                 if (t.num.length() == s.num.length()) {
                     return t.num < s.num;
                 } else {
                     return t.num.length() < s.num.length();
                 }
             }
         }
     }
     friend bool operator> (const BigInt& t, const BigInt& s) {
         return s < t;
     }
     friend bool operator== (const BigInt& t, const BigInt& s) {
         return t.num == s.num && t.sign == s.sign;
     }
     friend bool operator!= (const BigInt& t, const BigInt& s) {
         return !(t == s);
     }
     friend bool operator<= (const BigInt& t, const BigInt& s) {
         return t == s || t < s;
     }
     friend bool operator>= (const BigInt& t, const BigInt& s) {
         return t == s || t > s;
     }
     friend const BigInt abs(const BigInt& t) {
         BigInt ans = t;
         if (ans.sign == "-") ans.sign = "+";
         return ans;
     }
     friend const BigInt operator- (const BigInt& t) {
         BigInt ans = t;
         if (ans.sign == "-") ans.sign = "+";
         else ans.sign = "-";
         return ans;
     }
     friend istream& operator>> (istream& in, BigInt& t) {
         string s;
         in >> s;
         t = s;
         return in;
     }
     friend ostream& operator<< (ostream& out, const BigInt& t) {
         out << t.to_string();
         return out;
     }
     friend const BigInt operator+ (const BigInt& t, const BigInt& s) {
         BigInt ans, sub;
         if (t.num.length() < s.num.length()) {
             ans = s;
             sub = t;
         } else if (t.num.length() == s.num.length()) {
             if (t.num < s.num) {
                 ans = s;
                 sub = t;
             } else {
                 ans = t;
                 sub = s;
             }
         } else {
             ans = t;
             sub = s;
         }
         int sub_l = sub.num.length();
         int ans_l = ans.num.length();
         if (t.sign == s.sign) {
             for (int i = 1; i <= sub_l; i++) {
                 ans.num[ans_l - i] += sub.num[sub_l - i] - '0';
             }
             int flag = 0;
             for (int i = 1; i <= ans_l; i++) {
                 if (ans.num[ans_l - i] > '9') {
                     ans.num[ans_l - i] -= 10;
                     if (i == ans_l) {
                         flag = 1;
                     } else {
                         ans.num[ans_l - i - 1] += 1;
                     }
                 } else if (i >= sub_l) {
                     break;
                 }
             }
             if (flag) ans.num = "1" + ans.num;
         } else {
             for (int i = 1; i <= sub_l; i++) {
                 ans.num[ans_l - i] -= sub.num[sub_l - i] - '0';
             }
             for (int i = 1; i <= ans_l; i++) {
                 if (ans.num[ans_l - i] < '0') {
                     ans.num[ans_l - i] += 10;
                     ans.num[ans_l - i - 1] -= 1;
                 } else if (i >= sub_l) {
                     break;
                 }
             }
             int flag = 0;
             while (flag < ans_l - 1 && ans.num[flag] == '0') flag++;
             ans.num = ans.num.substr(flag);
             if (ans.num == "0") ans.sign = "+";
         }
         return ans;
     }
     friend const BigInt operator- (const BigInt& t, const BigInt& s) {
         BigInt sub = s;
         if (sub.sign == "+") sub.sign = "-";
         else sub.sign = "+";
         return t + sub;
     }
     friend const BigInt operator* (const BigInt& t, const BigInt& s) {
         BigInt res;
         if (s.sign == t.sign) res.sign = "+";
         else res.sign = "-";
         vector<complex<double> > x1, x2;
         vector<int> sum;
         string str1 = t.num, str2 = s.num;
         int len1 = str1.length();
         int len2 = str2.length();
         int len = 1;
         while (len < len1 * 2 || len < len2 * 2) len <<= 1;
         for (int i = 0; i < len1; i++) {
             x1.push_back(complex<double>(str1[len1 - 1 - i] - '0', 0));
         }
         for (int i = len1; i < len; i++) {
             x1.push_back(complex<double>(0, 0));
         }
         for (int i = 0; i < len2; i++) {
             x2.push_back(complex<double>(str2[len2 - 1 -i] - '0', 0));
         }
         for (int i = len2; i < len; i++) {
             x2.push_back(complex<double>(0, 0));
         }
         fft(x1, 1);
         fft(x2, 1);
         for (int i = 0; i < len; i++) x1[i] = x1[i] * x2[i];
         fft(x1, -1);
         for (auto& i : x1) sum.push_back((int)(i.real() + 0.5));
         for (int i = 0; i < len; i++) {
             sum[i + 1] += sum[i] / 10;
             sum[i] %= 10;
         }
         len = len1 + len2 - 1;
         while (sum[len] <= 0 && len > 0) len--;
         res.num = "";
         for (int i = len; i >= 0; i--) res.num += sum[i] + '0';
         if (res.num == "0") res.sign = "+";
         return res;
     }
     friend const BigInt operator/ (const BigInt& t, const BigInt& s) {
         if (s == 0) throw;
         BigInt res;
         if (s.sign == t.sign) res.sign = "+";
         else res.sign = "-";
         BigInt sub = abs(t), ans = abs(s);
         int w = sub.num.length() - ans.num.length();
         for (int i = 0; i < w; i++) ans.num += "0";
         while (w >= 0) {
             int d = 0;
             while (ans <= sub) {
                 sub -= ans;
                 d++;
             }
             res.num += d + '0';
             ans.num = ans.num.substr(0, ans.num.length() - 1);
             w--;
         }
         int flag = 0;
         while (flag < (int)res.num.length() - 1 && res.num[flag] == '0') flag++;
         res.num = res.num.substr(flag);
         if (res.num == "0") res.sign = "+";
         return res;
     }
     friend const BigInt operator% (const BigInt& t, const BigInt& s) {
         if (s == 0) throw;
         BigInt sub = abs(t), ans = abs(s);
         int w = sub.num.length() - ans.num.length();
         for (int i = 0; i < w; i++) ans.num += "0";
         while (w >= 0) {
             int d = 0;
             while (ans <= sub) {
                 sub -= ans;
                 d++;
             }
             w--;
             ans.num = ans.num.substr(0, ans.num.length() - 1);
         }
         sub.sign = t.sign;
         if (sub.num == "0") sub.sign = "+";
         return sub;
     }
     friend BigInt& operator+= (BigInt& t, const BigInt& s) {
         return t = t + s;
     }
     friend BigInt& operator-= (BigInt& t, const BigInt& s) {
         return t = t - s;
     }
     friend BigInt& operator*= (BigInt& t, const BigInt& s) {
         return t = t * s;
     }
     friend BigInt& operator/= (BigInt& t, const BigInt& s) {
         return t = t / s;
     }
     friend BigInt& operator%= (BigInt& t, const BigInt& s) {
         return t = t % s;
     }
     const BigInt subnum(int r, int l) {
         BigInt ans = this->num.substr(this->num.length() - l, l - r);
         ans.sign = this->sign;
         return ans;
     }
     const BigInt subnum(int l) {
         return this->subnum(0, l);
     }
};
BigInt dp[110][110];
int main(int argc, char const *argv[]) {
     BigInt a,b;// = 123235346576879789345325136217838;
    // std::cin >> a >> b;
    a = "12323534657687970056576575634534645";
    b = "123237596348601894012384039504950";
    std::cout << a * b << '\n';
    BigInt c;
    BigInt d;
    //std::cin >> c >> d;
    c = "1232353465768797893453251362178300000000";
    d = "21324354658768";
  std::cout << c / d << '\n';

    for(int i=0;i<=110;i++) {
        dp[i][0] = 1;
        dp[i][100] = 1;
    }
    for(int i=1;i<=100;i++) {
        for(int j=1;j<=100;j++) {
            dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
        }
    }
    std::cout << dp[4][2] << '\n';
    return 0;
}
