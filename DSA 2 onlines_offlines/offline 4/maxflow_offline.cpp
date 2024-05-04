#include <bits/stdc++.h>
using namespace std;

void make_pair(int x, vector<pair<int, int>> adj[], vector<int>& w, vector<int>& r,
               const vector<string>& names, int n, unordered_map<string, int>& ks_vi, vector<vector<int>>& store)
{
    map<pair<string, string>, int> make_pair1;
    int k = 2;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (i == x || j == x) continue;
            make_pair1[ {names[i], names[j]}] = n + k;
            k++;
            adj[n].push_back({make_pair1[{names[i], names[j]}], store[i][j]});
            adj[make_pair1[ {names[i], names[j]}]].push_back({ks_vi[names[i]], INT_MAX});
            adj[make_pair1[ {names[i], names[j]}]].push_back({ks_vi[names[j]], INT_MAX});
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (i == x) continue;
        adj[ks_vi[names[i]]].push_back({n + 1, max(w[x] + r[x] - w[i], 0)});
    }
}

bool bfs(vector<pair<int, int>> adj[], int n, int source, int destination, vector<pair<int, int>>& parent, vector<int>& vis,int total)
{
    vis.assign(total, 0);
    queue<int> q;
    parent[source].first = source;
    parent[source].second = INT_MAX;
    q.push(source);
    vis[source] = 1;
    int f = 0;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        for (auto it : adj[node])
        {
            int nextNode = it.first;
            int flow = it.second;
            if (!vis[nextNode] && flow > 0)
            {
                vis[nextNode] = 1;
                parent[nextNode].first = node;
                parent[nextNode].second = min(parent[node].second, flow);
                if (nextNode == destination)
                {
                    f = 1;
                    break;
                }
                q.push(nextNode);
            }
        }
        if (f)
        {
            break;
        }
    }
    return f;
}
vector<int> bonus_bfs(vector<pair<int, int>> adj[], int n, int source,  vector<int>& vis,int total,unordered_map<string, int> &ks_vi,vector<string> &names)
{
    vis.assign(total, 0);
    vector<int>st;
    queue<int> q;
    q.push(source);
    vis[source] = 1;
    while(!q.empty())
    {
        int node=q.front();
        q.pop();
        for(auto it:adj[node])
        {
            int nextNode = it.first;
            int flow = it.second;
            if(!vis[nextNode] && flow>0)
            {
                vis[nextNode]=1;
                for(int i=0; i<names.size(); i++)
                {
                    if(nextNode==ks_vi[names[i]])
                    {
                        st.push_back(nextNode);
                    }
                }
                q.push(it.first);


            }
        }
    }
    return st;


}

void storing_parent(vector<pair<int, int>>& parent, int i, vector<int>& store, vector<int>& store_node, vector<int>& store_vertex, int source,int total)
{

    while (i != source)
    {
        store.push_back(parent[i].second);
        store_node.push_back(i);
        store_vertex.push_back(parent[i].first);
        i = parent[i].first;
    }
}

void edmonds_karp(vector<pair<int, int>> adj[], int n, int s, int d, int& flow,int total)
{
    vector<pair<int, int>> parent(total, {-1, -1});
    vector<int> vis(total, 0);
    while (bfs(adj, n, s, d, parent,vis,total))
    {
        vector<int> store;
        vector<int> store_node;
        vector<int> store_vertex;
        storing_parent(parent, d, store, store_node, store_vertex, s,total);
        int minimum = *min_element(store.begin(),store.end());
        flow += minimum;
        for (int i = 0; i < store.size(); i++)
        {
            int u = store_vertex[i];
            int v = store_node[i];
            for (auto &edge : adj[u])
            {
                if (edge.first == v)
                {
                    edge.second -= minimum;
                    break;
                }
            }

            bool reverse_edge_found = false;
            for (auto &rev_edge : adj[v])
            {
                if (rev_edge.first == u)
                {
                    rev_edge.second += minimum;
                    reverse_edge_found = true;
                    break;
                }
            }

            if (!reverse_edge_found)
            {
                adj[v].emplace_back(u, minimum);
            }
        }
        parent.assign(total, {-1, -1});
    }
}
int main()
{
    int n;
    cin >> n;

    unordered_map<string, int> ks_vi;
    vector<vector<int>> store;
    vector<string> names;
    vector<int> w(n);
    vector<int> l(n);
    vector<int> r(n);
    int win, loss, left;
    int a;

    cin.ignore();

    for (int i = 0; i < n; i++)
    {
        string str;
        getline(cin, str);

        istringstream s(str);
        string name;
        s >> name;
        names.push_back(name);
        ks_vi[name] = i;

        s >> win;
        w[i] = win;
        s >> loss;
        l[i] = loss;
        s >> left;
        r[i] = left;

        vector<int> stats;
        while (s >> a)
        {
            stats.push_back(a);
        }
        store.push_back(stats);
    }

    int flow = 0;
    int total=2+(n*(n-1))/2+n;
    vector<pair<int, int>> adj[total];
    for (int i = 0; i < n; i++)
    {

        for (int i = 0; i < total; i++) adj[i].clear();
        int flag=0;
        for(int j=0; j<n; j++)
        {
            if(w[j]>w[i]+r[i])
            {
                cout<<endl<<endl;
                cout<<names[i]<<" is eleminated"<<endl;
                cout<<"They can win at most "<<w[i]<<"+"<<r[i]<<"="<<w[i]+r[i]<<" games"<<endl;
                cout<<names[j]<<" has won a total of "<<w[j]<<" games"<<endl;
                cout<<"They play each other "<<0<<" times"<<endl;
                cout<<"So on average, each of the teams in this group wins "<<w[j]<<"/1"<<"="<<w[j]<<" games"<<endl;
                flag=1;
                break;
            }
        }
        if(!flag)
        {
            make_pair(i, adj, w, r, names, n, ks_vi, store);

            flow = 0;
            int f=0;
            edmonds_karp(adj, n + 2, n, n + 1, flow,total);
            for(auto it:adj[n])
            {
                if(it.second>0)
                {
                    f=1;
                    break;
                }
            }
            if(f)
            {
                cout<<endl<<endl;
                cout<<names[i]<<" is eleminated"<<endl;
                cout<<"They can win at most "<<w[i]<<"+"<<r[i]<<"="<<w[i]+r[i]<<" games"<<endl;
                vector<int> vis(total, 0);
                vector<int>st=bonus_bfs(adj,n,n,vis,total,ks_vi,names);
                int sum=0;
                int count=0;
                for(int i=0; i<st.size(); i++)
                {
                    sum+=w[st[i]];
                }
                for(int i=0; i<st.size(); i++)
                {
                    for(int j=i+1; j<st.size(); j++)
                    {
                        count+=store[st[i]][st[j]];
                    }
                }

                for(int m=0; m<st.size(); m++)
                {
                    if(m==st.size()-1)
                    {
                        cout<<names[st[m]]<<" have won a total of "<<sum<<" games"<<endl;
                        cout<<"They play each other "<<count<<" times"<<endl;
                        cout<<"So on average, each of the teams in this group wins "<<sum+count<<"/"<<st.size()<<"="<<((sum+count)*1.0/st.size())<<" games"<<endl;
                    }
                    else
                    {
                        cout<<names[st[m]]<<",";
                    }


                    if(m==st.size()-2)
                    {
                        cout<<" and ";
                    }

                }

            }

        }

    }

    return 0;
}

