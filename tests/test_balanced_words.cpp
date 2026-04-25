#include <iostream>
#include <vector>
#include <string>
#include "../solutions/balanced_words.cpp"

// Brute force: enumerate all 26^n words for small n.
static long long bruteCount(int n, int d) {
    long long total = 0;
    vector<int> w(n, 0);
    while (true) {
        bool ok = true;
        for (int i = 1; i < n; ++i) {
            if (abs(w[i] - w[i - 1]) > d) { ok = false; break; }
        }
        if (ok) ++total;
        // increment
        int i = n - 1;
        while (i >= 0 && w[i] == 25) { w[i] = 0; --i; }
        if (i < 0) break;
        ++w[i];
    }
    return total;
}

int main() {
    int pass = 0, total = 0;

    auto check = [&](int n, int d, long long expected, const string& name) {
        ++total;
        long long got = countBalancedWords(n, d);
        cout << name << ": got " << got << " expected " << expected;
        if (got == expected) { ++pass; cout << "  PASS\n"; }
        else cout << "  FAIL\n";
    };

    // Provided samples
    check(2, 2, 124, "Sample 0 (n=2,d=2)");
    check(3, 1, 224, "Sample 1 (n=3,d=1)");
    check(2, 3, 170, "Stated example (n=2,d=3)");

    // d >= 25 -> all 26^n words are valid
    check(2, 25, 26 * 26, "d=25 covers all (n=2)");
    check(3, 25, 26 * 26 * 26, "d=25 covers all (n=3)");

    // Brute force cross-check for small n,d
    for (int n = 2; n <= 5; ++n) {
        for (int d = 1; d <= 5; ++d) {
            ++total;
            long long expected = bruteCount(n, d);
            long long got = countBalancedWords(n, d);
            if (got == expected) ++pass;
            else cout << "FAIL n=" << n << " d=" << d << " got " << got << " expected " << expected << "\n";
        }
    }

    // Stress test: large n
    {
        ++total;
        long long got = countBalancedWords(100000, 25);  // every word valid
        // 26^100000 mod (1e9+7) -- compute fast pow to verify
        const long long MOD = 1000000007;
        long long base = 26 % MOD, exp = 100000, result = 1;
        while (exp > 0) {
            if (exp & 1) result = result * base % MOD;
            base = base * base % MOD;
            exp >>= 1;
        }
        cout << "Stress n=1e5 d=25: got " << got << " expected " << result;
        if (got == result) { ++pass; cout << "  PASS\n"; }
        else cout << "  FAIL\n";
    }

    // Stress test: large n with d=1 (just shouldn't crash / time out)
    {
        ++total;
        long long got = countBalancedWords(100000, 1);
        cout << "Stress n=1e5 d=1: got " << got << " (sanity: in [0, 1e9+7))";
        if (got >= 0 && got < 1000000007) { ++pass; cout << "  PASS\n"; }
        else cout << "  FAIL\n";
    }

    cout << "\n" << pass << "/" << total << " passed\n";
    return pass == total ? 0 : 1;
}
