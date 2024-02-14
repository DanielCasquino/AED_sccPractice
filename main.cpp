#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Solution
{
    vector<vector<int>> getSCC(vector<char> &vals, vector<vector<int>> &edges)
    {
        // PRE-IMPLEMENTATION LOGIC:
        // Start at the first node. Go forward. If current node has neighbours, keep going. if it doesnt, close it. add it to stack.

        stack<int> finishedStack;
        stack<int> traversalStack;
        vector<bool> visited(vals.size(), false);

        vector<vector<int>> graph(vals.size());
        for (auto pair : graph)
        {
            graph[pair[0]].push_back(pair[1]);
        } // Adds directional edges
        }
};

int main()
{
    vector<char> values = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {3, 7}, {7, 7}, {7, 6}, {6, 5}, {5, 6}, {5, 4}, {1, 4}};
    auto res = Solution().getSCC(values, edges);
    std::cout << "Hello, from AED_sscPractice!\n";
    return 0;
}
