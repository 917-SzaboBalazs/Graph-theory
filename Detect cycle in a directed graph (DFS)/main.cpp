#include <iostream>
#include <vector>

using namespace std;

bool detectCycle(int currNode, vector<bool> &visited, vector<bool> &currPath, vector<int> *adj)
{
    visited[currNode] = currPath[currNode] = true;

    for (int &adjNode : adj[currNode])
    {
        if (!visited[adjNode])
        {
            if (detectCycle(adjNode, visited, currPath, adj))
            {
                return true;
            }
        }
        else if (currPath[adjNode])
        {
            return true;
        }
    }

    currPath[currNode] = false;

    return false;
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

    vector<bool> visited(n + 1, false), currPath(n + 1, false);

    bool isCycle = false;

    for (int i = 1; i <= n && !isCycle; i++)
    {
        if (!visited[i] && detectCycle(i, visited, currPath, adj))
        {
            isCycle = true;
        }
    }

    if (isCycle)
    {
        cout << "The graph contains cycle" << endl;
    }
    else
    {
        cout << "The graph does not contain cycle" << endl;
    }

    return 0;
}
