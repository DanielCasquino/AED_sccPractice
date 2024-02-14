#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Solution
{

    void firstDFS(int i, vector<vector<int>> &graph, vector<bool> &visited, stack<int> &finished)
    {
        // DFS stuff
        stack<int> traversalStack;
        traversalStack.push(i);
        visited[i] = true;

        // We have to make sure to traverse one path only, and only come back if we reach a dead end (no neighbours left)
        while (!traversalStack.empty())
        {
            int current = traversalStack.top(); // Get the current vertex, but no popping yet as it still might have unvisited neighbours
            bool visitedAllNeighbours = true;   // We assume it has no unvisited neighbours

            for (int neighbour : graph[current])
            {
                if (!visited[neighbour]) // If we find a neighbour that hasn't been visited yet
                {
                    visited[neighbour] = true;      // We say hi to homie
                    traversalStack.push(neighbour); // Add homie to DFS stack
                    visitedAllNeighbours = false;   // Turns out we still haven't visited all homies
                    break;                          // IMPORTANT, THIS ALLOWS US TO GO ALONG ONE WAY ONLY. ELSE IT WILL REPEAT THE PROCESS FOR EACH NEIGHBOUR, BRANCHING OUT.
                }
            }

            if (visitedAllNeighbours) // If current vertex has no neighbours left
            {
                finished.push(current); // Finished processing
                traversalStack.pop();   // Remove it from DFS stack
            }
        }
    } // Hahahahahahahahahahaha

    void secondDFS(int i, vector<vector<int>> &transposedGraph, vector<bool> &visited, vector<int> &scc)
    {
        // DFS YEAAAAA
        stack<int> traversalStack;
        traversalStack.push(i);
        visited[i] = true;

        while (!traversalStack.empty())
        {
            int current = traversalStack.top();
            traversalStack.pop();
            scc.push_back(current);

            for (int neighbour : transposedGraph[current])
            {
                if (!visited[neighbour])
                {
                    visited[neighbour] = true;
                    traversalStack.push(neighbour);
                }
            }
        }
    }

    vector<vector<int>> getSCC(vector<char> &vals, vector<vector<int>> &edges)
    {
        // PRE-IMPLEMENTATION LOGIC:
        // Start at the first node. Go forward. If current node has neighbours, keep going for that neighbour only. if it doesnt, it finished. add it to stack.
        // DFS through transposed too using the finished stack. Add elements to scc stack.
        // Profit...???
        // Understood like 70%

        int v = vals.size();
        vector<bool> visited(v, false);
        stack<int> finishedStack;

        // Builds graph
        vector<vector<int>> graph(v);
        for (auto pair : edges)
        {
            graph[pair[0]].push_back(pair[1]);
        }

        // Builds transposed graph
        vector<vector<int>> transposedGraph(v);
        for (int i = 0; i < graph.size(); ++i)
        {
            for (int j : graph[i])
            {
                transposedGraph[j].push_back(i); // Pushes edges the other way around
            }
        }

        // First DFS to get finished vertices
        for (int i = 0; i < v; ++i)
        {
            if (!visited[i])
                firstDFS(i, graph, visited, finishedStack);
        }

        // Restart visited vectors
        std::fill(visited.begin(), visited.end(), false);
        vector<vector<int>> sccs; // Vector to store SCCs

        while (!finishedStack.empty())
        {
            int current = finishedStack.top();
            finishedStack.pop();
            if (!visited[current])
            {
                vector<int> currentScc; // Vector to store current SCC
                secondDFS(current, transposedGraph, visited, currentScc);
                sccs.push_back(currentScc);
            }
        }
        return sccs;
    }
};

int main()
{
    vector<char> values = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    vector<vector<int>> edges = {{0, 1}, {1, 4}, {4, 0}, {2, 1}, {2, 3}, {3, 2}, {3, 7}, {7, 7}, {5, 4}, {5, 6}, {6, 5}, {6, 7}};
    vector<vector<int>> res = Solution().getSCC(values, edges);
    int i = 0;
    for (auto scc : res)
    {
        cout << "SCC " << i << endl;
        cout << "[ ";
        for (auto e : scc)
        {
            cout << values[e] << " ";
        }
        cout << ']';
        cout << endl;
        ++i;
    }
    return 0;
}
