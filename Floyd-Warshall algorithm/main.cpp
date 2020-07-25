#include <iostream>
#include <vector>

using namespace std;

enum { UNDIRECTED, DIRECTED };

int main()
{
    int graphType; cin >> graphType;

    int n, m; cin >> n >> m;
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, INT_MAX));
    vector<vector<int>> minDist(n + 1, vector<int>(n + 1, INT_MAX));
    vector<vector<int>> next(n + 1, vector<int>(n + 1, -1));

    for (int i = 0; i < m; i++)
    {
        int u, v, w; cin >> u >> v >> w;
        graph[u][v] = minDist[u][v] = w;
        next[u][v] = v;
        if (graphType == UNDIRECTED)
        {
            graph[v][u] = minDist[v][u] = w;
            next[v][u] = u;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        graph[i][i] = minDist[i][i] = 0;
    }

    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (minDist[i][k] != INT_MAX && minDist[k][j] != INT_MAX && minDist[i][j] > minDist[i][k] + minDist[k][j])
                {
                    minDist[i][j] = minDist[i][k] + minDist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    cout << "Minimum distance: " << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << i << ": ";
        for (int j = 1; j <= n; j++)
        {
            if (minDist[i][j] == INT_MAX)
            {
                cout << "- ";
            }
            else
            {
                cout << minDist[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;

    cout << "Next node matrix: " << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (next[i][j] == -1)
            {
                cout << "- ";
            }
            else
            {
                cout << next[i][j] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
