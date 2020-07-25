#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Adjacent
{
    int id;
    int cost;
};

struct Edge
{
    int src;
    int dest;
    int cost;

    bool operator>(const Edge &rhs) const
    {
        return cost > rhs.cost;
    }
};

int main()
{
    int n, m; cin >> n >> m;
    vector<Adjacent> adj[n + 1];

    for (int i = 0; i < m; i++)
    {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({ v, w });
        adj[v].push_back({ u, w });
    }

    vector<bool> visited(n + 1, false);
    vector<Edge> MST;
    int MSTCost = 0;

    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    visited[1] = true;
    for (Adjacent &adjNode : adj[1])
    {
        pq.push({ 1, adjNode.id, adjNode.cost });
    }

    while (!pq.empty() && (int)MST.size() != n - 1)
    {
        Edge currEdge = pq.top();
        int currNode = currEdge.dest;

        pq.pop();

        if (visited[currNode]) continue;
        visited[currNode] = true;

        MST.push_back(currEdge);
        MSTCost += currEdge.cost;

        for (Adjacent &adjNode : adj[currNode])
        {
            pq.push({ currNode, adjNode.id, adjNode.cost });
        }
    }

    if ((int)MST.size() != n - 1)
    {
        cout << "The graph does not have MST" << endl;
    }
    else
    {
        cout << "MST cost: " << MSTCost << endl;
        for (Edge &e : MST)
        {
            cout << e.src << " - " << e.dest << endl;
        }
    }

    return 0;
}
