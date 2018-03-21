#include <bits/stdc++.h>
using namespace std;

using T = long long;
class Frac {
 private:
     void simply() {
         T g = __gcd(num, den);
         num /= g;
         den /= g;
         if (den < T(0)) {
             den = -den;
             num = -num;
         }
     }

 public:
     T num, den;
     Frac(const T& t = 0, const T& s = 1) : num(t), den(s) { simply(); }
     double to_double() const { return (double)num / den; }
     long double to_ldouble() const { return (long double)num / den; }
     friend const Frac operator- (const Frac& t) {
         auto ans = t;
         ans.num = -ans.num;
         return ans;
     }
     friend const Frac abs(const Frac& t) {
         auto ans = t;
         if (ans.num < T(0)) ans.num = -ans.num;
         return ans;
     }
     friend ostream& operator<< (ostream& out, const Frac& t) {
         out << t.num << "/" << t.den;
         return out;
     }
     friend const Frac operator+ (const Frac& t, const Frac& s) {
         auto ans = t;
         ans.num = ans.num * s.den + s.num * ans.den;
         ans.den *= s.den;
         ans.simply();
         return ans;
     }
     friend const Frac operator- (const Frac& t, const Frac& s) {
         return t + (-s);
     }
     friend const Frac operator* (const Frac& t, const Frac& s) {
         auto ans = t;
         ans.num *= s.num;
         ans.den *= s.den;
         ans.simply();
         return ans;
     }
     friend const Frac operator/ (const Frac& t, const Frac& s) {
         if (s == T(0)) throw;
         auto ans = s;
         swap(ans.num, ans.den);
         return t * ans;
     }
     friend Frac& operator+= (Frac& t, const Frac& s) {
         return t = t + s;
     }
     friend Frac& operator-= (Frac& t, const Frac& s) {
         return t = t - s;
     }
     friend Frac& operator*= (Frac& t, const Frac& s) {
         return t = t * s;
     }
     friend Frac& operator/= (Frac& t, const Frac& s) {
         return t = t / s;
     }
     friend bool operator< (const Frac& t, const Frac& s) {
         return t.num * s.den < s.num * t.den;
     }
     friend bool operator> (const Frac& t, const Frac& s) {
         return s < t;
     }
     friend bool operator== (const Frac& t, const Frac& s) {
         return t.num == s.num && t.den == s.den;
     }
     friend bool operator!= (const Frac& t, const Frac& s) {
         return !(t == s);
     }
     friend bool operator<= (const Frac& t, const Frac& s) {
         return t < s || t == s;
     }
     friend bool operator>= (const Frac& t, const Frac& s) {
         return t > s || t == s;
     }
};

int main(int argc, char const *argv[]) {

 	// int a,b;
	// std::cin >> a >> b;
	Frac ans = Frac(1,3) + Frac(1,3);
	Frac res = Frac(2,3) + Frac(1,3);
	std::cout << ans << '\n';
	std::cout << res << '\n';
	std::cout  << Frac(1,3) << endl;
	return 0;
}
