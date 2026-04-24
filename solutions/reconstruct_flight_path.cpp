// LeetCode 332 / NeetCode 150: Reconstruct Flight Path
// Hierholzer's algorithm for Eulerian path.
// Time: O(E log E), Space: O(E)

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, priority_queue<string, vector<string>, greater<string>>> graph;
        for (auto& t : tickets) {
            graph[t[0]].push(t[1]);
        }

        vector<string> route;
        stack<string> stk;
        stk.push("JFK");

        while (!stk.empty()) {
            string curr = stk.top();
            if (!graph[curr].empty()) {
                string next = graph[curr].top();
                graph[curr].pop();
                stk.push(next);
            } else {
                route.push_back(curr);
                stk.pop();
            }
        }

        reverse(route.begin(), route.end());
        return route;
    }
};
