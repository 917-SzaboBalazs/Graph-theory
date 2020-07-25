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
        hamil = currPath;
        return;
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

    for (int i = 1; i <= n && hamil.size() == 0; i++)
    {
        findHamiltonian(i, visited, currPath, hamil, adj, n);
    }

    if (hamil.size() == 0)
    {
        cout << "The graph has no Hamiltonian path" << endl;
    }
    else
    {
        cout << "Hamiltonian path: ";
        for (int &item : hamil) cout << item << " ";
        cout << endl;
    }

    return 0;
}
