// LeetCode 458: Poor Pigs
// Each pig has (minutesToTest / minutesToDie + 1) distinguishable states
// (the round it died in, or survived). With p pigs we can identify
// states^p buckets. Return the smallest p with states^p >= buckets.
// Time: O(log_states(buckets)), Space: O(1)

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        int states = minutesToTest / minutesToDie + 1;
        int pigs = 0;
        long long total = 1;
        while (total < buckets) {
            total *= states;
            ++pigs;
        }
        return pigs;
    }
};
