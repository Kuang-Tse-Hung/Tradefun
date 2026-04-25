#include <iostream>
#include <numeric>
#include <random>
#include <climits>
#include "../solutions/alternate_prefix_sums.cpp"

// Brute force: try every permutation of arr (only for very small n) and compute the
// max beauty, then compare against getMaxBeauty.
static long long beautyOf(const vector<int>& a) {
    int n = a.size();
    long long psum = 0, beauty = 0;
    for (int i = 0; i < n; ++i) {
        psum += a[i];
        beauty += (i % 2 == 0 ? 1 : -1) * psum;
    }
    return beauty;
}

static long long bruteMax(vector<int> a) {
    sort(a.begin(), a.end());
    long long best = LLONG_MIN;
    do {
        best = max(best, beautyOf(a));
    } while (next_permutation(a.begin(), a.end()));
    return best;
}

int main() {
    int pass = 0, total = 0;

    auto check = [&](vector<int> a, long expected, const string& name) {
        ++total;
        long got = getMaxBeauty(a);
        cout << name << ": got " << got << " expected " << expected;
        if (got == expected) { ++pass; cout << "  PASS\n"; }
        else cout << "  FAIL\n";
    };

    // Provided example
    check({3, 4, 5, 1, 1}, 12, "Example arr=[3,4,5,1,1]");

    // Hand-derived
    check({1, 2, 3, 4}, -3, "n=4 [1,2,3,4]");        // -(1+2)
    check({5},          5,  "n=1 single");           // top 1
    check({1, 2},       -1, "n=2 [1,2]");            // -min = -1
    check({1, 2, 3},    5,  "n=3 [1,2,3]");          // top 2 = 2+3
    check({10, 1, 1, 1, 10}, 21, "n=5 mixed");       // top 3: 1,10,10 = 21

    // Random brute-force comparison for small n.
    mt19937 rng(42);
    for (int trial = 0; trial < 50; ++trial) {
        int n = uniform_int_distribution<int>(1, 7)(rng);
        vector<int> a(n);
        for (int& x : a) x = uniform_int_distribution<int>(1, 20)(rng);
        long long expected = bruteMax(a);
        long got = getMaxBeauty(a);
        ++total;
        if ((long long)got == expected) ++pass;
        else {
            cout << "FAIL random trial " << trial << " n=" << n << " arr=[";
            for (int x : a) cout << x << ",";
            cout << "] got " << got << " expected " << expected << "\n";
        }
    }

    // Large stress test for overflow / perf (no brute, just consistency).
    {
        ++total;
        int n = 100000;
        vector<int> a(n, 1000000000);  // all max value
        long got = getMaxBeauty(a);
        // n even -> -(sum of smallest n/2) = -(50000 * 1e9) = -5e13
        long long expected = -50000LL * 1000000000LL;
        cout << "Stress n=1e5 max vals: got " << got << " expected " << expected;
        if ((long long)got == expected) { ++pass; cout << "  PASS\n"; }
        else cout << "  FAIL\n";
    }
    {
        ++total;
        int n = 99999;
        vector<int> a(n, 1000000000);
        long got = getMaxBeauty(a);
        // n odd -> sum of top (n+1)/2 = 50000 * 1e9 = 5e13
        long long expected = 50000LL * 1000000000LL;
        cout << "Stress n=99999 max vals: got " << got << " expected " << expected;
        if ((long long)got == expected) { ++pass; cout << "  PASS\n"; }
        else cout << "  FAIL\n";
    }

    cout << "\n" << pass << "/" << total << " passed\n";
    return pass == total ? 0 : 1;
}
