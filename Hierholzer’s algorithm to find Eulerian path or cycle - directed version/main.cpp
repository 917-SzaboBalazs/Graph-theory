#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int findStartNode(vector<int> &inDeg, vector<int> &outDeg, int n)
{
    int startNode = 0;

    for (int i = 1; i <= n; i++)
    {
        if (abs(inDeg[i] - outDeg[i]) > 1)
        {
            return 0;
        }
        else if (outDeg[i] - inDeg[i] == 1)
        {
            if (startNode == 0)
            {
                startNode = i;
            }
            else
            {
                return 0;
            }
        }
        else if (inDeg[i] == outDeg[i] && startNode == 0 && inDeg[i] > 0)
        {
            startNode = i;
        }
    }

    return startNode == 0 ? 1 : startNode;
}

void findEulerian(int currNode, vector<int> &outDeg, vector<int> &euler, vector<int> *adj)
{
    while (outDeg[currNode] > 0)
    {
        findEulerian(adj[currNode][--outDeg[currNode]], outDeg, euler, adj);
    }

    euler.push_back(currNode);
}

int main()
{
    int n, m; cin >> n >> m;
    vector<int> adj[n + 1];
    vector<int> inDeg(n + 1, 0), outDeg(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        inDeg[v]++;
        outDeg[u]++;
    }

    int startNode = findStartNode(inDeg, outDeg, n);

    if (startNode == 0)
    {
        cout << "No Eulerian path or cycle existed!" << endl;
    }
    else
    {
        vector<int> euler;

        findEulerian(startNode, outDeg, euler, adj);

        if ((int)euler.size() != m + 1)
        {
            cout << "No Eulerian path or cycle existed!" << endl;
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
