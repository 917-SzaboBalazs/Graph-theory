#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum { UNDIRECTED, DIRECTED };

int main()
{
    int graphType; cin >> graphType;

    int n, m; cin >> n >> m;
    vector<int> adj[n + 1];

    for (int i = 0; i < m; i++)
    {
        int v1, v2; cin >> v1 >> v2;
        adj[v1].push_back(v2);

        if (graphType == UNDIRECTED)
        {
            adj[v2].push_back(v1);
        }
    }

    int start; cin >> start;

    queue<int> q;
    vector<bool> visited(n + 1, false);

    q.push(start);

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
