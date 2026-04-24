// Local test harness for solutions/reconstruct_flight_path.cpp
#include <iostream>
#include "../solutions/reconstruct_flight_path.cpp"

static void printVec(const vector<string>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << "\"" << v[i] << "\"";
        if (i + 1 < v.size()) cout << ",";
    }
    cout << "]\n";
}

static bool eq(const vector<string>& a, const vector<string>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) if (a[i] != b[i]) return false;
    return true;
}

int main() {
    Solution s;
    int pass = 0, total = 0;

    {
        ++total;
        vector<vector<string>> t = {{"BUF","HOU"},{"HOU","SEA"},{"JFK","BUF"}};
        vector<string> expected = {"JFK","BUF","HOU","SEA"};
        auto got = s.findItinerary(t);
        cout << "Test 1: "; printVec(got);
        if (eq(got, expected)) { ++pass; cout << "  PASS\n"; } else cout << "  FAIL expected JFK,BUF,HOU,SEA\n";
    }
    {
        ++total;
        vector<vector<string>> t = {{"HOU","JFK"},{"SEA","JFK"},{"JFK","SEA"},{"JFK","HOU"}};
        vector<string> expected = {"JFK","HOU","JFK","SEA","JFK"};
        auto got = s.findItinerary(t);
        cout << "Test 2: "; printVec(got);
        if (eq(got, expected)) { ++pass; cout << "  PASS\n"; } else cout << "  FAIL expected JFK,HOU,JFK,SEA,JFK\n";
    }
    {
        // Classic LC example: greedy-lex DFS would fail here without Hierholzer.
        ++total;
        vector<vector<string>> t = {{"MUC","LHR"},{"JFK","MUC"},{"SFO","SJC"},{"LHR","SFO"}};
        vector<string> expected = {"JFK","MUC","LHR","SFO","SJC"};
        auto got = s.findItinerary(t);
        cout << "Test 3: "; printVec(got);
        if (eq(got, expected)) { ++pass; cout << "  PASS\n"; } else cout << "  FAIL\n";
    }
    {
        // Another classic trap case.
        ++total;
        vector<vector<string>> t = {{"JFK","KUL"},{"JFK","NRT"},{"NRT","JFK"}};
        vector<string> expected = {"JFK","NRT","JFK","KUL"};
        auto got = s.findItinerary(t);
        cout << "Test 4: "; printVec(got);
        if (eq(got, expected)) { ++pass; cout << "  PASS\n"; } else cout << "  FAIL\n";
    }
    {
        ++total;
        vector<vector<string>> t = {{"JFK","ATL"},{"ATL","JFK"}};
        vector<string> expected = {"JFK","ATL","JFK"};
        auto got = s.findItinerary(t);
        cout << "Test 5: "; printVec(got);
        if (eq(got, expected)) { ++pass; cout << "  PASS\n"; } else cout << "  FAIL\n";
    }

    cout << "\n" << pass << "/" << total << " passed\n";
    return pass == total ? 0 : 1;
}
