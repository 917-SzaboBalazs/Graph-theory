#include <iostream>
#include <vector>

using namespace std;

void findBridges(int currNode, int prevNode, vector<int> &disc, vector<int> &low, vector<pair<int, int>> &bridges, vector<int> *adj)
{
    static int time = 0;

    disc[currNode] = low[currNode] = ++time;

    for (int &adjNode : adj[currNode])
    {
        if (disc[adjNode] == 0)
        {
            findBridges(adjNode, currNode, disc, low, bridges, adj);

            low[currNode] = min(low[currNode], low[adjNode]);

            if (disc[currNode] < low[adjNode])
            {
                bridges.push_back(make_pair(currNode, adjNode));
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
    vector<pair<int, int>> bridges;

    for (int i = 1; i <= n; i++)
    {
        if (disc[i] == 0)
        {
            findBridges(i, -1, disc, low, bridges, adj);
        }
    }

    cout << "Number of bridges: " << bridges.size() << endl;

    if (bridges.size() > 0)
    {
        cout << "Bridges:" << endl;

        for (pair<int, int> &bridge : bridges)
        {
            cout << bridge.first << " - " << bridge.second << endl;
        }
    }

    return 0;
}
