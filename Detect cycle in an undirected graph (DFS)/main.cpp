#include <iostream>
#include <vector>

using namespace std;

bool detectCycle(int currNode, int parentNode, bool *visited, vector<int> *adj)
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
        else if (adjNode != parentNode)
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
        int v1, v2; cin >> v1 >> v2;
        adj[v1].push_back(v2);
        adj[v2].push_back(v1);
    }

    bool visited[n + 1] = { false };

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            if (detectCycle(i, -1, visited, adj))
            {
                cout << "Graph contains cycle" << endl;
                return 0;
            }
        }
    }

    cout << "Graph does not contain cycle" << endl;

    return 0;
}
