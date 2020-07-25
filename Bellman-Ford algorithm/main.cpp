#include <iostream>
#include <vector>

using namespace std;

struct Edge
{
    int src;
    int dest;
    int cost;
};

int main()
{
    int n, m; cin >> n >> m;
    vector<Edge> edges(m);

    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].src >> edges[i].dest >> edges[i].cost;
    }

    int src; cin >> src;

    vector<int> minDist(n + 1, INT_MAX);
    vector<int> prev(n + 1, -1);
    minDist[src] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (Edge &e : edges)
        {
            if (minDist[e.src] != INT_MAX && minDist[e.dest] > minDist[e.src] + e.cost)
            {
                minDist[e.dest] = minDist[e.src] + e.cost;
                prev[e.dest] = e.src;
            }
        }
    }

    bool negativeWeightCycle = false;

    for (Edge &e : edges)
    {
        if (minDist[e.src] != INT_MAX && minDist[e.dest] > minDist[e.src] + e.cost)
        {
            negativeWeightCycle = true;
            break;
        }
    }

    if (negativeWeightCycle)
    {
        cout << "Negative weight cycle existed" << endl;
    }
    else
    {
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
    }

    return 0;
}
