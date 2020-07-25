#include <iostream>

using namespace std;

struct Edge
{
    int u;
    int v;
};

struct Node
{
    int repr;
    int nodeRank;
};

int findRepr(int currNode, Node *nodes)
{
    if (nodes[currNode].repr != currNode)
    {
        nodes[currNode].repr = findRepr(nodes[currNode].repr, nodes);
    }

    return nodes[currNode].repr;
}

void doUnion(int reprU, int reprV, Node *nodes)
{
    if (nodes[reprU].nodeRank == nodes[reprV].nodeRank)
    {
        nodes[reprU].repr = reprV;
        nodes[reprV].nodeRank++;
    }
    else if (nodes[reprU].nodeRank > nodes[reprV].nodeRank)
    {
        nodes[reprV].repr = reprU;
    }
    else
    {
        nodes[reprU].repr = reprV;
    }
}

int main()
{
    int n, m; cin >> n >> m;
    Edge edges[m];

    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].u >> edges[i].v;
    }

    Node nodes[n + 1];

    for (int i = 1; i <= n; i++)
    {
        nodes[i].repr = i;
        nodes[i].nodeRank = 0;
    }

    bool wasCycle = false;

    for (int i = 0; i < m; i++)
    {
        int findU = findRepr(edges[i].u, nodes);
        int findV = findRepr(edges[i].v, nodes);

        if (findU == findV)
        {
            wasCycle = true;
        }
        else
        {
            doUnion(findU, findV, nodes);
        }
    }

    if (wasCycle)
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
