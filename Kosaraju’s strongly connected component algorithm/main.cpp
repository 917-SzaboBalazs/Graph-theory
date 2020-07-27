#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfs(int currNode, vector<bool> &visited, stack<int> &order, vector<int> *adj)
{
    visited[currNode] = true;

    for (int &adjNode : adj[currNode])
    {
        if (!visited[adjNode])
        {
            dfs(adjNode, visited, order, adj);
        }
    }

    order.push(currNode);
}

void dfs(int currNode, vector<bool> &visited, vector<int> &currComponent, vector<int> *adj)
{
    visited[currNode] = true;
    currComponent.push_back(currNode);

    for (int &adjNode : adj[currNode])
    {
        if (!visited[adjNode])
        {
            dfs(adjNode, visited, currComponent, adj);
        }
    }
}

int main()
{
    int n, m; cin >> n >> m;
    vector<int> adj[n + 1], revAdj[n + 1];

    for (int i = 0; i < m; i++)
    {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        revAdj[v].push_back(u);
    }

    vector<bool> visited(n + 1, false);
    stack<int> order;

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            dfs(i, visited, order, adj);
        }
    }

    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> SCC;

    while (!order.empty())
    {
        int currNode = order.top();
        order.pop();

        if (visited[currNode]) continue;

        vector<int> currComponent;
        dfs(currNode, visited, currComponent, revAdj);

        SCC.push_back(currComponent);
    }

    cout << "Number of strongly connected components: " << SCC.size() << endl;
    for (size_t i = 0; i < SCC.size(); i++)
    {
        cout << i + 1 << ": ";
        for (int &currNode : SCC[i])
        {
            cout << currNode << " ";
        }
        cout << endl;
    }

    return 0;
}
