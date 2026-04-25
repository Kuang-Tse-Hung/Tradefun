// Alternate Prefix Sums - maximize beauty by rearranging arr.
//
// Coefficient analysis: arr[k] contributes S(k) = sum_{i=k..n-1} (-1)^i.
//   - If (n-k) is even, S(k) = 0.
//   - If (n-k) is odd,  S(k) = (-1)^k.
//
// n odd : coeff +1 at even indices (count = (n+1)/2), 0 at odd
//         -> put largest (n+1)/2 values at even indices.
// n even: coeff -1 at odd indices (count = n/2), 0 at even
//         -> put smallest n/2 values at odd indices.
//
// Time: O(n log n), Space: O(1) extra.

#include <vector>
#include <algorithm>
using namespace std;

long getMaxBeauty(vector<int> arr) {
    int n = (int)arr.size();
    sort(arr.begin(), arr.end());
    long long beauty = 0;
    if (n % 2 == 1) {
        int k = (n + 1) / 2;
        for (int i = n - k; i < n; ++i) beauty += arr[i];
    } else {
        int k = n / 2;
        for (int i = 0; i < k; ++i) beauty -= arr[i];
    }
    return (long)beauty;
}
