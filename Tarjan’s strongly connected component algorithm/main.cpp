#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void findSCCs(int currNode, vector<int> &disc, vector<int> &low, vector<bool> &onStack, stack<int> &st, vector<vector<int>> &SCC, vector<int> *adj)
{
    static int time = 0;

    disc[currNode] = low[currNode] = ++time;
    onStack[currNode] = true;
    st.push(currNode);

    for (int &adjNode : adj[currNode])
    {
        if (disc[adjNode] == 0)
        {
            findSCCs(adjNode, disc, low, onStack, st, SCC, adj);

            low[currNode] = min(low[currNode], low[adjNode]);
        }
        else if (onStack[adjNode])
        {
            low[currNode] = min(low[currNode], disc[adjNode]);
        }
    }

    if (disc[currNode] == low[currNode])
    {
        vector<int> currComponent;

        while (st.top() != currNode)
        {
            onStack[st.top()] = false;
            currComponent.push_back(st.top());
            st.pop();
        }
        onStack[st.top()] = false;
        currComponent.push_back(st.top());
        st.pop();

        SCC.push_back(currComponent);
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
    }

    vector<int> disc(n + 1, 0), low(n + 1, 0);
    vector<bool> onStack(n + 1, false);
    stack<int> st;
    vector<vector<int>> SCC;

    for (int i = 1; i <= n; i++)
    {
        if (disc[i] == 0)
        {
            findSCCs(i, disc, low, onStack, st, SCC, adj);
        }
    }

    cout << "Number of strongly connected components: " << SCC.size() << endl;

    for (size_t i = 0; i < SCC.size(); i++)
    {
        cout << i + 1 << ": ";
        for (int &item : SCC[i])
        {
            cout << item << " ";
        }
        cout << endl;
    }

    return 0;
}
