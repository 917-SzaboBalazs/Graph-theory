#include <iostream>
#include <vector>

using namespace std;

enum GraphType { UNDIRECTED, DIRECTED };

void dfs(int currNode, bool *visited, vector<int> *adj)
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
        int v1, v2; cin >> v1 >> v2;
        adj[v1].push_back(v2);

        if (graphType == GraphType::UNDIRECTED)
        {
            adj[v2].push_back(v1);
        }
    }

    int src; cin >> src;

    bool visited[n + 1] = { false };

    cout << "DFS order: ";
    dfs(src, visited, adj);
    cout << endl;

    return 0;
}
