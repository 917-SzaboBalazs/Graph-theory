#include <iostream>
#include <vector>

using namespace std;

struct Edge
{
    int src;
    int dest;
};

int Find(int currNode, vector<int> &repr)
{
    while (currNode != repr[currNode])
    {
        currNode = repr[currNode];
    }

    return currNode;
}

int main()
{
    int n, m; cin >> n >> m;
    vector<Edge> edges(m);

    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].src >> edges[i].dest;
    }

    vector<int> repr(n + 1);

    for (int i = 1; i <= n; i++)
    {
        repr[i] = i;
    }

    bool isCycle = false;

    for (int i = 0; i < m && !isCycle; i++)
    {
        int findU = Find(edges[i].src, repr);
        int findV = Find(edges[i].dest, repr);

        if (findU == findV)
        {
            isCycle = true;
        }
        else
        {
            repr[findU] = findV;
        }
    }

    if (isCycle)
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
