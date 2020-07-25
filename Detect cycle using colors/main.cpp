#include <iostream>
#include <vector>

using namespace std;

enum Colors { WHITE, GRAY, BLACK };

bool detectCycle(int currNode, int *colors, vector<int> *adj)
{
    colors[currNode] = GRAY;

    for (int &adjNode : adj[currNode])
    {
        if (colors[adjNode] == WHITE)
        {
            if (detectCycle(adjNode, colors, adj))
            {
                return true;
            }
        }
        else if (colors[adjNode] == GRAY)
        {
            return true;
        }
    }

    colors[currNode] = BLACK;

    return false;
}

int main()
{
    int n, m; cin >> n >> m;
    vector<int> adj[n + 1];

    for (int i = 0; i < m; i++)
    {
        int v1, v2; cin >> v1 >> v2;
        adj[v1].push_back(v2);
    }

    int colors[n + 1] = { WHITE };

    for (int i = 1; i <= n; i++)
    {
        if (colors[i] == WHITE)
        {
            if (detectCycle(i, colors, adj))
            {
                cout << "The graph contains cycle" << endl;
                return 0;
            }
        }
    }

    cout << "The graph does not contain cycle" << endl;

    return 0;
}
