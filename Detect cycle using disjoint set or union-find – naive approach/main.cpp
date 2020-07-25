#include <iostream>

using namespace std;

struct Edge
{
    int u;
    int v;
};

int findRepr(int currNode, int *repr)
{
    while (repr[currNode] != currNode)
    {
        currNode = repr[currNode];
    }

    return currNode;
}

int main()
{
    int n, m; cin >> n >> m;
    Edge edges[m];

    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].u >> edges[i].v;
    }

    int repr[n + 1]; for (int i = 1; i <= n; i++) repr[i] = i;
    bool wasCycle = false;

    for (int i = 0; i < m; i++)
    {
        int findU = findRepr(edges[i].u, repr);
        int findV = findRepr(edges[i].v, repr);

        if (findU == findV)
        {
            wasCycle = true;
        }
        else
        {
            repr[findU] = findV;
        }
    }

    if (wasCycle)
    {
        cout << "The graph contains cycle" << endl;
    }
    else
    {
        cout << "The graph does not contain cycle" << endl;
    }

    cout << "The representations: ";
    for (int i = 1; i <= n; i++)
    {
        cout << repr[i] << " ";
    }
    cout << endl;

    return 0;
}
