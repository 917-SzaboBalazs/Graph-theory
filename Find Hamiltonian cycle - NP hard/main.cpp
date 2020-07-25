#include <iostream>
#include <vector>

using namespace std;

enum GraphType { UNDIRECTED, DIRECTED };

void findHamiltonian(int currNode, vector<bool> &visited, vector<int> &currPath, vector<int> &hamil, vector<int> *adj, int n)
{
    visited[currNode] = true;
    currPath.push_back(currNode);

    if ((int)currPath.size() == n)
    {
        bool isBackEdge = false;
        for (int &adjNode : adj[currNode])
        {
            if (adjNode == 1)
            {
                isBackEdge = true;
                break;
            }
        }

        if (isBackEdge)
        {
            hamil = currPath;
            return;
        }
    }

    for (int &adjNode : adj[currNode])
    {
        if (!visited[adjNode])
        {
            findHamiltonian(adjNode, visited, currPath, hamil, adj, n);
            if ((int)hamil.size() == n)
            {
                return;
            }
        }
    }

    visited[currNode] = false;
    currPath.pop_back();
}

int main()
{
    int graphType; cin >> graphType;

    int n, m; cin >> n >> m;
    vector<int> adj[n + 1];

    for (int i = 0; i < m; i++)
    {
        int u, v; cin >> u >> v;

        adj[u].push_back(v);
        if (graphType == GraphType::UNDIRECTED)
        {
            adj[v].push_back(u);
        }
    }

    vector<bool> visited(n + 1, false);
    vector<int> hamil, currPath;

    findHamiltonian(1, visited, currPath, hamil, adj, n);

    if (hamil.size() == 0 && n > 1)
    {
        cout << "The graph has no Hamiltonian cycle" << endl;
    }
    else
    {
        hamil.push_back(1);

        cout << "Hamiltonian cycle: ";
        for (int &item : hamil) cout << item << " ";
        cout << endl;
    }

    return 0;
}
