#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    int src;
    int dest;
    int cost;

    bool operator<(const Edge &rhs) const
    {
        return cost < rhs.cost;
    }
};

struct Node
{
    int repr;
    int nodeRank;
};

int Find(int currNode, vector<Node> &nodes)
{
    if (currNode != nodes[currNode].repr)
    {
        nodes[currNode].repr = Find(nodes[currNode].repr, nodes);
    }

    return nodes[currNode].repr;
}

void Union(int u, int v, vector<Node> &nodes)
{
    if (nodes[u].nodeRank < nodes[v].nodeRank)
    {
        nodes[u].repr = v;
    }
    else if (nodes[u].nodeRank > nodes[v].nodeRank)
    {
        nodes[v].repr = u;
    }
    else
    {
        nodes[u].repr = v;
        nodes[v].nodeRank++;
    }
}

int main()
{
    int n, m; cin >> n >> m;
    vector<Edge> edges(m);

    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].src >> edges[i].dest >> edges[i].cost;
    }

    sort(edges.begin(), edges.end());

    vector<Edge> MST;
    int MSTCost = 0;

    vector<Node> nodes(n + 1);

    for (int i = 1; i <= n; i++)
    {
        nodes[i] = { i, 0 };
    }

    for (int i = 0; i < m && (int)MST.size() != n - 1; i++)
    {
        int findU = Find(edges[i].src, nodes);
        int findV = Find(edges[i].dest, nodes);

        if (findU != findV)
        {
            Union(findU, findV, nodes);

            MST.push_back(edges[i]);
            MSTCost += edges[i].cost;
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
