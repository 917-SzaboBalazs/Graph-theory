#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Edge
{
    int src;
    int dest;
};

void findBCCs(int currNode, int prevNode, vector<int> &disc, vector<int> &low, stack<Edge> &st, vector<vector<Edge>> &BCC, vector<int> *adj, int rootNode)
{
    static int time = 0;
    int children = 0;

    disc[currNode] = low[currNode] = ++time;

    for (int &adjNode : adj[currNode])
    {
        if (disc[adjNode] == 0)
        {
            children++;
            st.push({ currNode, adjNode });

            findBCCs(adjNode, currNode, disc, low, st, BCC, adj, rootNode);

            low[currNode] = min(low[currNode], low[adjNode]);

            bool isAP = false;
            if (currNode == rootNode && children > 1)
            {
                isAP = true;
            }
            else if (currNode != rootNode && disc[currNode] <= low[adjNode])
            {
                isAP = true;
            }

            if (isAP)
            {
                vector<Edge> currComponent;

                while (st.top().src != currNode || st.top().dest != adjNode)
                {
                    currComponent.push_back(st.top());
                    st.pop();
                }
                currComponent.push_back(st.top());
                st.pop();

                BCC.push_back(currComponent);
            }
        }
        else if (adjNode != prevNode)
        {
            low[currNode] = min(low[currNode], disc[adjNode]);

            if (disc[currNode] > disc[adjNode])
            {
                st.push({ currNode, adjNode });
            }
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
    stack<Edge> st;
    vector<vector<Edge>> BCC;

    for (int i = 1; i <= n; i++)
    {
        if (disc[i] == 0)
        {
            findBCCs(i, -1, disc, low, st, BCC, adj, i);

            vector<Edge> currComponent;
            while (!st.empty())
            {
                currComponent.push_back({ st.top() });
                st.pop();
            }

            if (currComponent.size() != 0)
            {
                BCC.push_back(currComponent);
            }
        }
    }

    cout << "Number of biconnected components: " << BCC.size() << endl;
    for (size_t i = 0; i < BCC.size(); i++)
    {
        cout << i + 1 << ": ";
        for (Edge &e : BCC[i])
        {
            cout << e.src << " - " << e.dest << " ";
        }
        cout << endl;
    }

    return 0;
}
