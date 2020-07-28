#include <iostream>
#include <vector>

using namespace std;

enum GraphType { UNDIRECTED, DIRECTED };

void dfs(int currNode, vector<bool> &visited, vector<int> *adj)
{
    visited[currNode] = true;
    cout << currNode << " ";

    for (int &adjNode : adj[currNode])
    {
        if (!visited[adjNode])
        {
            dfs(adjNode, visited, adj);
        }
    }
}

int main()
{
    int graphType; cin >> graphType;

    int n, m; cin >> n >> m;
    vector<int> adj[n + 1];

    for (int i = 0; i < m; i++)
    {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);

        if (graphType == GraphType::UNDIRECTED)
        {
            adj[v].push_back(u);
        }
    }

    int src; cin >> src;

    vector<bool> visited(n + 1, false);

    cout << "DFS order: ";
    dfs(src, visited, adj);
    cout << endl;

    return 0;
}
