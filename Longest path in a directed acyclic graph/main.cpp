#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Adjacent
{
    int id;
    int cost;
};

void createTopoOrder(int currNode, vector<bool> &visited, vector<Adjacent> *adj, vector<int> &topoOrder)
{
    visited[currNode] = true;

    for (Adjacent &adjNode : adj[currNode])
    {
        if (!visited[adjNode.id])
        {
            createTopoOrder(adjNode.id, visited, adj, topoOrder);
        }
    }

    topoOrder.push_back(currNode);
}

int main()
{
    int n, m; cin >> n >> m;
    vector<Adjacent> adj[n + 1];

    for (int i = 0; i < m; i++)
    {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({ v, w });
    }

    int src; cin >> src;

    vector<bool> visited(n + 1, false);
    vector<int> topoOrder;

    createTopoOrder(src, visited, adj, topoOrder);
    reverse(topoOrder.begin(), topoOrder.end());

    vector<int> maxDist(n + 1, INT_MIN), prev(n + 1, -1);
    maxDist[src] = 0;

    for (int &currNode : topoOrder)
    {
        for (Adjacent &adjNode : adj[currNode])
        {
            if (maxDist[adjNode.id] < maxDist[currNode] + adjNode.cost)
            {
                maxDist[adjNode.id] = maxDist[currNode] + adjNode.cost;
                prev[adjNode.id] = currNode;
            }
        }
    }

    cout << "Maximum distance from node " << src << ": " << endl;
    for (int i = 1; i <= n; i++)
    {
        if (maxDist[i] == INT_MIN)
        {
            cout << i << ": -" << endl;
        }
        else
        {
            cout << i << ": " << maxDist[i] << ", previous node: " << prev[i] << endl;
        }
    }

    return 0;
}
