#include <iostream>
#include <vector>

using namespace std;

struct Edge
{
    int src;
    int dest;
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
        nodes[v].nodeRank = u;
    }
}

int main()
{
    int n, m; cin >> n >> m;
    vector<Edge> edges(m);

    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].src >> edges[i].dest;
    }

    vector<Node> nodes(n + 1);

    for (int i = 1; i <= n; i++)
    {
        nodes[i] = { i, 0 };
    }

    bool isCycle = false;

    for (int i = 0; i < m && !isCycle; i++)
    {
        int findU = Find(edges[i].src, nodes);
        int findV = Find(edges[i].dest, nodes);

        if (findU == findV)
        {
            isCycle = true;
        }
        else
        {
            Union(findU, findV, nodes);
        }
    }

    if (isCycle)
    {
        cout << "The graph contains cycle" << endl;
    }
    else
    {
        cout << "The graph doesn't contain cycle" << endl;
    }

    cout << "The represents: ";
    for (int i = 1; i <= n; i++)
    {
        cout << nodes[i].repr << " ";
    }
    cout << endl;

    return 0;
}
