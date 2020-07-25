#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge
{
    int src;
    int dest;
    int cost;
};

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
    int n, m; cin >> n >> m;
    vector<Edge> edges(m + n);

    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].src >> edges[i].dest >> edges[i].cost;
    }

    vector<int> h(n + 1, INT_MAX);
    h[0] = 0;

    for (int i = m; i < m + n; i++)
    {
        edges[i] = { 0, i - m + 1, 0 };
    }

    /// Bellman-Ford
    for (int i = 0; i < n - 1; i++)
    {
        for (Edge &e : edges)
        {
            if (h[e.src] != INT_MAX && h[e.dest] > h[e.src] + e.cost)
            {
                h[e.dest] = h[e.src] + e.cost;
            }
        }
    }

    bool negativeWeightCycle = false;

    for (Edge &e : edges)
    {
        if (h[e.src] != INT_MAX && h[e.dest] > h[e.src] + e.cost)
        {
            negativeWeightCycle = true;
            break;
        }
    }

    if (negativeWeightCycle)
    {
        cout << "Negative weight cycle detected" << endl;
    }
    else
    {
        /// Dijkstra
        vector<Adjacent> adj[n + 1];

        for (int i = 0; i < m; i++)
        {
            adj[edges[i].src].push_back({ edges[i].dest, edges[i].cost + h[edges[i].src] - h[edges[i].dest] });
        }

        priority_queue<Adjacent, vector<Adjacent>, greater<Adjacent>> pq;

        for (int i = 1; i <= n; i++)
        {
            vector<int> minDist(n + 1, INT_MAX), prev(n + 1, -1);
            vector<bool> visited(n + 1, false);

            pq.push({ i, 0 });
            minDist[i] = 0;

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

            for (int j = 1; j <= n; j++)
            {
                if (minDist[j] != INT_MAX)
                {
                    minDist[j] += h[j] - h[i];
                }
            }

            cout << "Minimum distance from node " << i << ": " << endl;
            for (int j = 1; j <= n; j++)
            {
                if (minDist[j] == INT_MAX)
                {
                    cout << j << ": -" << endl;
                }
                else
                {
                    cout << j << ": " << minDist[j] << ", previous node: " << prev[j] << endl;
                }
            }
            cout << endl;
        }
    }

    return 0;
}
