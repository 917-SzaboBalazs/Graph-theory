#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    int u;
    int v;
    int w;

    friend istream &operator>>(istream &in, Edge &obj)
    {
        in >> obj.u >> obj.v >> obj.w;
        return in;
    }

    bool operator<(const Edge &rhs) const
    {
        return w < rhs.w;
    }
};

struct Subset
{
    int parent;
    int rank;
};

int find(int i, Subset *subsets)
{
    if (subsets[i].parent != i)
    {
        subsets[i].parent = find(subsets[i].parent, subsets);
    }
    return subsets[i].parent;
}

void Union(int u, int v, Subset *subsets)
{
    if (subsets[u].rank < subsets[v].rank)
    {
        subsets[u].parent = v;
    }
    else if (subsets[u].rank > subsets[v].rank)
    {
        subsets[v].parent = u;
    }
    else
    {
        subsets[u].parent = v;
        subsets[v].rank++;
    }
}

int main()
{
    int n, m; cin >> n >> m;
    Edge edges[m];

    for (int i = 0; i < m; i++)
    {
        cin >> edges[i];
    }

    sort(edges, edges + m);
    Subset subsets[n + 1]; for (int i = 1; i <= n; i++) subsets[i] = { i, 0 };


    vector<Edge> MST;
    int MSTCost = 0;

    for (int i = 0; i < m && (int)MST.size() != n - 1; i++)
    {
        int findU = find(edges[i].u, subsets);
        int findV = find(edges[i].v, subsets);

        if (findU != findV)
        {
            MST.push_back(edges[i]);
            MSTCost += edges[i].w;

            Union(findU, findV, subsets);
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
            cout << e.u << " - " << e.v << endl;
        }
    }

    return 0;
}
