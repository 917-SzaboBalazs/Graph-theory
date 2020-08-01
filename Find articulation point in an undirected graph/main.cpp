#include <iostream>
#include <vector>

using namespace std;

void findAP(int currNode, int prevNode, vector<int> &disc, vector<int> &low, vector<bool> &isAP, vector<int> *adj, int rootNode)
{
    static int time = 0;

    disc[currNode] = low[currNode] = ++time;
    int children = 0;

    for (int &adjNode : adj[currNode])
    {
        if (disc[adjNode] == 0)
        {
            children++;

            findAP(adjNode, currNode, disc, low, isAP, adj, rootNode);

            low[currNode] = min(low[currNode], low[adjNode]);

            if (currNode == rootNode && children > 1)
            {
                isAP[currNode] = true;
            }
            else if (currNode != rootNode && disc[currNode] <= low[adjNode])
            {
                isAP[currNode] = true;
            }
        }
        else if (adjNode != prevNode)
        {
            low[currNode] = min(low[currNode], disc[adjNode]);
        }
    }
}

int main()
{
    int n, m; cin >> n >> m;
    vector<int> adj[n + 1];

    for (int i = 0; i < m; i++)
    {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> disc(n + 1, 0), low(n + 1, 0);
    vector<bool> isAP(n + 1, false);

    vector<int> AP;

    for (int i = 1; i <= n; i++)
    {
        if (disc[i] == 0)
        {
            findAP(i, -1, disc, low, isAP, adj, i);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (isAP[i])
        {
            AP.push_back(i);
        }
    }

    cout << "Number of articulation points: " << AP.size() << endl;

    if (AP.size() > 0)
    {
        cout << "Articulation points: ";

        for (int &item : AP)
        {
            cout << item << " ";
        }
        cout << endl;
    }

    return 0;
}
