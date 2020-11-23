/* Priyansh Agarwal*/

#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<algorithm>
#include<string.h>
#include<unordered_map>
#include<vector>
#include<unordered_set>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<map>
#include<chrono>

using namespace std;
using namespace __gnu_pbds;
using namespace chrono;

#define debug(x) cout << #x << " " << x <<endl;
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define nline "\n"
#define pb push_back
#define ppb pop_back;
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcount
#define sz(x) (int)(x.size())

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key

/*---------------------------------------------------------------------------------------------------------------------------*/
ll gcd(ll a, ll b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
ll expo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
void extendgcd(ll a, ll b, ll*v) {if (b == 0) {v[0] = 1; v[1] = 0; v[2] = a; return ;} extendgcd(b, a % b, v); ll x = v[1]; v[1] = v[0] - v[1] * (a / b); v[0] = x; return;} //pass an arry of size1 3
ll mminv(ll a, ll b) {ll arr[3]; extendgcd(a, b, arr); return arr[0];} //for non prime b
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}
bool revsort(ll a, ll b) {return a > b;}
void swap(int &x, int &y) {int temp = x; x = y; y = temp;}
ll combination(ll n, ll r, ll m, ll *fact, ll *ifact) {ll val1 = fact[n]; ll val2 = ifact[n - r]; ll val3 = ifact[r]; return (((val1 * val2) % m) * val3) % m;}
void google(int t) {cout << "Case #" << t << ": ";}
vector<int> sieve(int n) {int*arr = new int[n + 1](); vector<int> vect; for (int i = 2; i <= n; i++)if (arr[i] == 0) {vect.push_back(i); for (int j = 2 * i; j <= n; j += i)arr[j] = 1;} return vect;}
ll mod_add(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
ll mod_mul(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll mod_sub(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}
ll mod_div(ll a, ll b, ll m) {a = a % m; b = b % m; return (mod_mul(a, mminvprime(b, m), m) + m) % m;}  //only for prime m
ll phin(ll n) {ll number = n; if (n % 2 == 0) {number /= 2; while (n % 2 == 0)n /= 2;} for (ll i = 3; i <= sqrt(n); i += 2) {if (n % i == 0) {while (n % i == 0)n /= i; number = (number / i * (i - 1));}} if (n > 1)number = (number / n * (n - 1)) ; return number;} //O(sqrt(N))
/*--------------------------------------------------------------------------------------------------------------------------*/

lld dp[301][301][301];
void solve() {
	int n;
	cin >> n;
	int a1 = 0, a2 = 0, a3 = 0;
	for (int i = 0; i < n; i++) {
		int ai;
		cin >> ai;
		if (ai == 1)
			a1++;
		else if (ai == 2)
			a2++;
		else
			a3++;
	}
	// dp[a][b][c] = p_a * (1 + dp[a-1][b][c]) + p_b * (1 + dp[a+1][b-1][c]) + p_c * (1 + dp[a][b+1][c-1]) + p_d * (1 + dp[a][b][c]);

	// 1 * p_a + 1 * p_b + 1 * p_c + 1 * p_d = 1

	// dp[a][b][c] - p_d * (dp[a][b][c]) = 1 + p_a * (dp[a-1][b][c]) + p_b * (dp[a+1][b-1][c]) +p_c * (dp[a][b+1][c-1]);

	// dp[a][b][c] = (1 - p_d) * [1 + p*a (dp[a-1][b][c]) + p_b * (dp[a+1][b-1][c]) + p_c * (dp[a][b+1][c-1])]

	dp[0][0][0] = 0;
	for (int threes = 0; threes <= n; threes++) {
		for (int twos = 0; twos <= n; twos++) {
			for (int ones = 0; ones <= n; ones++) {
				if (threes + twos + ones > n)
					continue;
				if (threes + ones + twos == 0)
					continue;
				lld p_a = ((lld)ones) / n;
				lld p_b = ((lld)twos) / n;
				lld p_c = ((lld)threes) / n;
				lld p_d = ((lld)(n - ones - twos - threes)) / n;
				lld value = 1;
				if (ones - 1 >= 0)
					value += p_a * dp[threes][twos][ones - 1];
				if (twos - 1 >= 0)
					value += p_b * dp[threes][twos - 1][ones + 1];
				if (threes - 1 >= 0)
					value += p_c * dp[threes - 1][twos + 1][ones];
				value = value / (1 - p_d);
				dp[threes][twos][ones] = value;
			}
		}
	}
	cout << setprecision(15);
	cout << fixed;
	cout << dp[a3][a2][a1] << nline;
}
int main() {
	fastio();
#ifndef ONLINE_JUDGE
	freopen("Input.txt", "r", stdin);
	freopen("Output.txt", "w", stdout);
	freopen("Error.txt", "w", stderr);
#endif
	auto start1 = high_resolution_clock::now();
	solve();
	auto stop1 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop1 - start1);
#ifndef ONLINE_JUDGE
	cerr << "Time: " << duration.count() / 1000 << endl;
#endif
	return 0;
}