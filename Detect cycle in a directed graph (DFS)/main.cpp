#include <iostream>
#include <vector>

using namespace std;

bool detectCycle(int currNode, bool *visited, bool *currPath, vector<int> *adj)
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

    bool visited[n + 1] = { false }, currPath[n + 1] = { false };

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            if (detectCycle(i, visited, currPath, adj))
            {
                cout << "The graph contains cycle" << endl;
                return 0;
            }
        }
    }

    cout << "The graph does not contain cycle" << endl;

    return 0;
}
