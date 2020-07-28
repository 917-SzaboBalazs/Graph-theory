#include <iostream>
#include <vector>

using namespace std;

bool detectCycle(int currNode, int prevNode, vector<bool> &visited, vector<int> *adj)
{
    visited[currNode] = true;

    for (int &adjNode : adj[currNode])
    {
        if (!visited[adjNode])
        {
            if (detectCycle(adjNode, currNode, visited, adj))
            {
                return true;
            }
        }
        else if (adjNode != prevNode)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    int n, m; cin >> n >> m;
    vector<int> adj[n + 1];

    for (int i = 0; i < m; i++)
    {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> visited(n + 1, false);

    bool isCycle = false;

    for (int i = 1; i <= n && !isCycle; i++)
    {
        if (!visited[i] && detectCycle(i, -1, visited, adj))
        {
            isCycle = true;
        }
    }

    if (isCycle)
    {
        cout << "Graph contains cycle" << endl;
    }
    else
    {
        cout << "Graph does not contain cycle" << endl;
    }

    return 0;
}
