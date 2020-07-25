#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void topoSort(int curr, bool *visited, vector<int> *adj, vector<int> &topoOrder)
{
    visited[curr] = true;

    for (int &adjacent : adj[curr])
    {
        if (!visited[adjacent])
        {
            topoSort(adjacent, visited, adj, topoOrder);
        }
    }

    topoOrder.push_back(curr);
}

int main()
{
    int n, m; cin >> n >> m;
    vector<int> adj[n + 1];

    for (int i = 0; i < m; i++)
    {
        int v1, v2; cin >> v1 >> v2;
        adj[v1].push_back(v2);
    }

    bool visited[n + 1] = { false };
    vector<int> topoOrder;

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            topoSort(i, visited, adj, topoOrder);
        }
    }

    reverse(topoOrder.begin(), topoOrder.end());
    cout << "Topological order: ";
    for (int &item : topoOrder)
    {
        cout << item << " ";
    }
    cout << endl;

    return 0;
}
