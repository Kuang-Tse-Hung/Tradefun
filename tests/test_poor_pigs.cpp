#include <iostream>
#include "../solutions/poor_pigs.cpp"

int main() {
    Solution s;
    int pass = 0, total = 0;

    auto check = [&](int buckets, int td, int tt, int expected, const string& name) {
        ++total;
        int got = s.poorPigs(buckets, td, tt);
        cout << name << ": got " << got << " expected " << expected;
        if (got == expected) { ++pass; cout << "  PASS\n"; }
        else cout << "  FAIL\n";
    };

    check(4, 15, 15, 2, "Example 1");        // states=2, 2^2=4 >= 4
    check(4, 15, 30, 2, "Example 2");        // states=3, 3^2=9 >= 4
    check(1, 1, 1, 0, "Single bucket");      // no pig needed
    check(2, 15, 15, 1, "Two buckets");      // states=2, 2^1=2 >= 2
    check(1000, 15, 60, 5, "1000/states=5"); // states=5, 5^4=625<1000, 5^5=3125>=1000
    check(125, 1, 4, 3, "125 buckets");      // states=5, 5^3=125
    check(8, 5, 15, 2, "8/states=4");        // states=4, 4^2=16 >= 8
    check(1000, 1, 1, 10, "states=2 max");   // states=2, 2^10=1024 >= 1000
    check(1, 100, 100, 0, "1 bucket again"); // edge

    cout << "\n" << pass << "/" << total << " passed\n";
    return pass == total ? 0 : 1;
}
