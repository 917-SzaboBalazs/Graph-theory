#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum GraphType { UNDIRECTED, DIRECTED };

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

    queue<int> q;
    vector<bool> visited(n + 1, false);

    q.push(src);

    cout << "BFS order: ";
    while (!q.empty())
    {
        int currNode = q.front();
        q.pop();

        if (visited[currNode]) continue;
        visited[currNode] = true;

        cout << currNode << " ";

        for (int &adjNode : adj[currNode])
        {
            q.push(adjNode);
        }
    }

    cout << endl;

    return 0;
}
