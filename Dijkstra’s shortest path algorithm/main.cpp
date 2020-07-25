#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum { UNDIRECTED, DIRECTED };

struct Adjacent
{
    int id;
    int cost;

    bool operator>(const Adjacent &rhs) const
    {
        return cost > rhs.cost;
    }
};

int main()
{
    int graphType; cin >> graphType;
    int n, m; cin >> n >> m;

    vector<Adjacent> adj[n + 1];
    for (int i = 0; i < m; i++)
    {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({ v, w });
        if (graphType == UNDIRECTED)
        {
            adj[v].push_back({ u, w });
        }
    }

    int src; cin >> src;

    vector<bool> visited(n + 1, false);
    vector<int> minDist(n + 1, INT_MAX);
    vector<int> prev(n + 1, -1);

    priority_queue<Adjacent, vector<Adjacent>, greater<Adjacent>> pq;

    minDist[src] = 0;
    pq.push({ src, 0 });

    while (!pq.empty())
    {
        int currNode = pq.top().id;
        pq.pop();

        if (visited[currNode]) continue;
        visited[currNode] = true;

        for (Adjacent &adjNode : adj[currNode])
        {
            if (minDist[adjNode.id] > minDist[currNode] + adjNode.cost)
            {
                minDist[adjNode.id] = minDist[currNode] + adjNode.cost;
                prev[adjNode.id] = currNode;

                pq.push({ adjNode.id, minDist[adjNode.id] });
            }
        }
    }

    cout << "Minimum distance from node " << src << ": " << endl;
    for (int i = 1; i <= n; i++)
    {
        if (minDist[i] == INT_MAX)
        {
            cout << i << ": -" << endl;
        }
        else
        {
            cout << i << ": " << minDist[i] << ", previous node: " << prev[i] << endl;
        }
    }

    return 0;
}
