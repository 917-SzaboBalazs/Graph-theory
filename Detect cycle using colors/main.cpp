#include <iostream>
#include <vector>

using namespace std;

enum Colors { BLACK, GRAY, WHITE };

bool detectCycle(int currNode, vector<int> &colors, vector<int> *adj)
{
    colors[currNode] = GRAY;

    for (int &adjNode : adj[currNode])
    {
        if (colors[adjNode] == BLACK)
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

    colors[currNode] = WHITE;

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

    vector<int> colors(n + 1, BLACK);

    bool isCycle = false;

    for (int i = 1; i <= n && !isCycle; i++)
    {
        if (colors[i] == BLACK && detectCycle(i, colors, adj))
        {
            isCycle = true;
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

    return 0;
}
