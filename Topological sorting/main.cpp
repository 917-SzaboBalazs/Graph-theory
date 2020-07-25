#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void createTopoOrder(int currNode, vector<bool> &visited, vector<int> *adj, vector<int> &topoOrder)
{
    visited[currNode] = true;

    for (int &adjNode : adj[currNode])
    {
        if (!visited[adjNode])
        {
            createTopoOrder(adjNode, visited, adj, topoOrder);
        }
    }

    topoOrder.push_back(currNode);
}

int main()
{
    int n, m; cin >> n >> m;
    vector<int> adj[n + 1];

    for (int i = 0; i < m; i++)
    {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }

    vector<bool> visited(n + 1, false);
    vector<int> topoOrder;

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            createTopoOrder(i, visited, adj, topoOrder);
        }
    }

    reverse(topoOrder.begin(), topoOrder.end());

    cout << "Topological order: ";
    for (int &item : topoOrder) cout << item << " ";
    cout << endl;

    return 0;
}
