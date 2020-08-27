#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Adjacent
{
    int id;
    size_t revPos;
};

int findStartNode(vector<int> &deg, int n)
{
    int startNode = 0;
    int noOdd = 0;

    for (int i = 1; i <= n; i++)
    {
        if (deg[i] % 2 == 1)
        {
            startNode = i;
            noOdd++;
            if (noOdd > 2)
            {
                return 0;
            }
        }
        else if (deg[i] > 0 && startNode == 0)
        {
            startNode = i;
        }
    }

    return startNode == 0 ? 1 : startNode;
}

void findEulerian(int currNode, vector<int> &deg, vector<int> &euler, vector<Adjacent> *adj)
{
    while (deg[currNode] > 0)
    {
        if (adj[currNode][--deg[currNode]].id == 0) continue;

        int adjNode = adj[currNode][deg[currNode]].id;
        size_t revPos = adj[currNode][deg[currNode]].revPos;

        adj[adjNode][revPos].id = 0;

        findEulerian(adjNode, deg, euler, adj);
    }

    euler.push_back(currNode);
}

int main()
{
    int n, m; cin >> n >> m;
    vector<Adjacent> adj[n + 1];

    for (int i = 0; i < m; i++)
    {
        int u, v; cin >> u >> v;
        adj[u].push_back({ v, adj[v].size() });
        adj[v].push_back({ u, adj[u].size() - 1 });
    }

    vector<int> deg(n + 1);
    for (int i = 1; i <= n; i++)
    {
        deg[i] = adj[i].size();
    }

    int startNode = findStartNode(deg, n);

    if (startNode == 0)
    {
        cout << "No Eulerian path or cycle exited!" << endl;
    }
    else
    {
        vector<int> euler;

        findEulerian(startNode, deg, euler, adj);

        if ((int)euler.size() != m + 1)
        {
            cout << "No Eulerian path or cycle exited!" << endl;
        }
        else
        {
            reverse(euler.begin(), euler.end());

            cout << "Eulerian path or cycle: ";
            for (int &currNode : euler)
            {
                cout << currNode << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
