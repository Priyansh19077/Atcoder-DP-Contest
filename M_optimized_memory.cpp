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


ll dp[100001];
ll prefix[100001];
ll temp[100001];

void solve() {

	// dp[n][k] = number of ways to distribute k candies among n people
	// dp[n][k] = dp[n-1][k] + dp[n-1][k-1] + dp[n-1][k-2]..... + dp[n-1][k-a[n]];
	// then to find dp[n+1][k] we can find prefix sum from dp[n][0] to dp[n][k-a[n+1]];
	// in the end we just find dp[n][k]

	// base cases dp[0][0] = 1
	// dp[0][i] = 0 for i > 0

	int n, k;
	cin >> n >> k;
	ll arr[n];
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	dp[0] = 1;
	for (int i = 1; i <= k; i++)
		dp[i] = 0;
	for (int i = 0; i <= k; i++) {
		prefix[i] = (dp[i] + ((i > 0) ? prefix[i - 1] : 0)) % MOD;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= k; j++) {
			int right = j;
			int left = max(j - arr[i - 1], (ll)0);
			dp[j] = (prefix[right] - ((left > 0) ? prefix[left - 1] : 0)) % MOD;
		}
		for (int j = 0; j <= k; j++) {
			prefix[j] = (dp[j] + ((j > 0) ? prefix[j - 1] : 0)) % MOD;
		}
	}
	cout << mod_add(dp[k], 0, MOD) << nline;

	//memory can be optimized as we only require the previous stage.
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