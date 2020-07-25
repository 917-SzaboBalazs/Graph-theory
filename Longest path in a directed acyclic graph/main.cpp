#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    int dest;
    int cost;
};

void createTopoOrder(int curr, bool *visited, vector<Edge> *adj, vector<int> &topoOrder)
{
    visited[curr] = true;

    for (Edge &e : adj[curr])
    {
        if (!visited[e.dest])
        {
            createTopoOrder(e.dest, visited, adj, topoOrder);
        }
    }

    topoOrder.push_back(curr);
}

int main()
{
    int n, m; cin >> n >> m;
    vector<Edge> adj[n + 1];

    for (int i = 0; i < m; i++)
    {
        int v1, v2, w; cin >> v1 >> v2 >> w;
        adj[v1].push_back({ v2, w });
    }
    int start; cin >> start;

    vector<int> topoOrder;
    bool visited[n + 1] = { false };

    createTopoOrder(start, visited, adj, topoOrder);
    reverse(topoOrder.begin(), topoOrder.end());

    int maxDist[n + 1]; fill(maxDist + 1, maxDist + n + 1, INT_MIN);
    maxDist[start] = 0;

    for (size_t i = 0; i < topoOrder.size(); i++)
    {
        if (maxDist[topoOrder[i]] == INT_MIN) continue;

        for (Edge &e : adj[topoOrder[i]])
        {
            if (maxDist[e.dest] < maxDist[topoOrder[i]] + e.cost)
            {
                maxDist[e.dest] = maxDist[topoOrder[i]] + e.cost;
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << (maxDist[i] == INT_MIN ? "-" : to_string(maxDist[i])) << " ";
    }
    cout << endl;

    return 0;
}
