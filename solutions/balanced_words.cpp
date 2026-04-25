// Balanced Words: count length-n words over a-z where every adjacent pair
// differs by at most d (alphabet positions). Answer mod 1e9+7.
//
// dp[i][c] = number of balanced words of length i ending in char c.
//   dp[1][c]   = 1
//   dp[i+1][c] = sum_{|c-k| <= d} dp[i][k]   (a sliding window)
// Use prefix sums so each step is O(26). Total O(26 * n).

#include <vector>
#include <algorithm>
using namespace std;

int countBalancedWords(int n, int d) {
    const long long MOD = 1000000007;
    vector<long long> dp(26, 1);
    for (int step = 1; step < n; ++step) {
        vector<long long> pref(27, 0);
        for (int i = 0; i < 26; ++i) pref[i + 1] = (pref[i] + dp[i]) % MOD;
        vector<long long> nxt(26);
        for (int c = 0; c < 26; ++c) {
            int lo = max(0, c - d);
            int hi = min(25, c + d);
            nxt[c] = (pref[hi + 1] - pref[lo] + MOD) % MOD;
        }
        dp.swap(nxt);
    }
    long long ans = 0;
    for (long long v : dp) ans = (ans + v) % MOD;
    return (int)ans;
}
