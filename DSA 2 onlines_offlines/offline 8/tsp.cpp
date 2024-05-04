#include<bits/stdc++.h>
using namespace std;

class Graph
{
public:
    vector<pair<int,pair<int,int>>>edge;
    vector<int>parent_list;
    vector<int>rank_list;
    list<pair<int,pair<int,int>>>li;
    list<pair<int,pair<int,int>>>doublemst;

    vector<vector<int>> Create_Random_Graph(int v)
    {


        vector<vector<int>> adj(v, vector<int>(v, INT_MAX));

        for (int i = 0; i < v; i++)
        {
            adj[i][i] = 0;
        }
        for(int i=0; i<v; i++)
        {
            for(int j=i+1; j<v; j++)
            {
                int w=edgeweight(50,200);
                adj[i][j]=w;
                adj[j][i]=w;
            }
        }
        for (int i = 0; i < v; i++)
        {
            for (int j = 0; j < v; j++)
            {
                for (int k = 0; k < v; k++)
                {
                    if (i != j && i != k && j != k)
                    {
                        if (adj[i][j] > adj[i][k] + adj[k][j])
                        {

                            adj[i][j] = adj[i][k] + adj[k][j];
                        }
                    }
                }
            }
        }

        return adj;


    }

    vector<int> Exact_TSP(vector<vector<int>> adj, int source)
    {
        int n = adj.size();
        vector<vector<int>> path_track(1 << n, vector<int>(n, -1));
        vector<vector<int>> shortest_d_container(1 << n, vector<int>(n, INT_MAX));
        shortest_d_container[1 << source][source] = 0;
        int subset_generator = 1;
        int minimum_cost = INT_MAX;
        while (subset_generator < (1 << n))
        {
            vector<int> subset_city;
            for (int ending_city = 0; ending_city < n; ending_city++)
            {
                if ((subset_generator & (1 << ending_city)) != 0)
                {
                    subset_city.push_back(ending_city);
                }
            }
            for (int end_city = 0; end_city < subset_city.size(); end_city++)
            {
                for (int city_from_subset = 0; city_from_subset < subset_city.size(); city_from_subset++)
                {
                    if (subset_city[end_city] != subset_city[city_from_subset])
                    {
                        if (shortest_d_container[subset_generator - (1 << subset_city[end_city])][subset_city[city_from_subset]] != INT_MAX)
                        {
                            int newCost = shortest_d_container[subset_generator - (1 << subset_city[end_city])][subset_city[city_from_subset]] + adj[subset_city[city_from_subset]][subset_city[end_city]];
                            if (newCost < shortest_d_container[subset_generator][subset_city[end_city]])
                            {
                                shortest_d_container[subset_generator][subset_city[end_city]] = newCost;
                                path_track[subset_generator][subset_city[end_city]] = subset_city[city_from_subset];
                            }
                        }
                    }
                }
            }
            subset_generator++;
        }
        int end_city = -1;
        for (int i = 0; i < n; i++)
        {
            if (i != source)
            {
                if (shortest_d_container[(1 << n) - 1][i] + adj[i][source] < minimum_cost)
                {
                    minimum_cost = shortest_d_container[(1 << n) - 1][i] + adj[i][source];
                    end_city = i;
                }
            }
        }

        int generator = (1 << n) - 1;
        vector<int> optimum_tour;
        int cities = end_city;
        int temp;
        optimum_tour.push_back(source);
        while (generator != 0)
        {
            if (cities != -1)
            {
                optimum_tour.push_back(cities);
                temp = path_track[generator][cities];
                generator ^= (1 << cities);
                cities = temp;
            }
        }




        return optimum_tour;
    }
    vector<int> Metric_Approximation_TSP(vector<vector<int>>&adj)
    {
        int v=adj.size();
        for(int i=0; i<v; i++)
        {
            parent_list.push_back(i);
        }
        for(int i=0; i<v; i++)
        {
            rank_list.push_back(0);
        }
        for(int i=0; i<v; i++)
        {
            for(int j=i+1; j<v; j++)
            {
                int w=adj[i][j];
                edge.push_back({w,{i,j}});
            }
        }
        mst();
        doubling_the_mst();
        vector<int>eulerian_tour_unique=find_eulerian_path();
        return eulerian_tour_unique;
    }





    int edgeweight(int low,int high)
    {
        int weight=low+(rand()%(high-low+1));
        return weight;
    }
    void sorting()
    {
        sort(edge.begin(),edge.end());
    }

    int main_parent(int v)
    {
        if(parent_list[v]==v)
        {
            return v;
        }
        parent_list[v]=main_parent(parent_list[v]);
        return parent_list[v];
    }
    void union_of_two(int u,int v)
    {
        int a=main_parent(u);
        int b=main_parent(v);
        if(rank_list[a]<rank_list[b])
        {
            parent_list[a]=b;
        }
        else if(rank_list[a]>rank_list[b])
        {
            parent_list[b]=a;
        }
        else
        {
            parent_list[a]=b;
            rank_list[b]++;
        }


    }
    void mst()
    {
        for(auto it:edge)
        {
            double w=it.first;
            int u=it.second.first;
            int v=it.second.second;
            if(main_parent(u)!=main_parent(v))
            {
                li.push_back({w,{u,v}});
                union_of_two(u,v);
            }
        }

    }
    void doubling_the_mst()
    {
        for(auto it:li)
        {
            int w=it.first;
            int u=it.second.first;
            int v=it.second.second;
            doublemst.push_back({w,{u,v}});
            doublemst.push_back({w,{v,u}});
        }

    }
    vector<int> find_eulerian_path()
    {
        int l=doublemst.size();
        vector<int>eulerian_tour;
        vector<int>mst_graph[l];
        for(auto it:doublemst)
        {
            mst_graph[it.second.first].push_back(it.second.second);
        }
        stack<int>st;
        st.push(0);
        while(!st.empty())
        {
            int vertex=st.top();
            if(mst_graph[vertex].size()!=0)
            {
                st.push(mst_graph[vertex].back());
                mst_graph[vertex].pop_back();

            }
            else
            {
                eulerian_tour.push_back(vertex);
                st.pop();
            }

        }
        unordered_set<int>a;
        vector<int>eulerian_tour_unique;
        for (int element : eulerian_tour)
        {
            if (a.insert(element).second)
            {

                eulerian_tour_unique.push_back(element);
            }
        }

        return eulerian_tour_unique;
    }
    int Calculate_Tour_Length(vector<int>tour,vector<vector<int>>adj)
    {
        int tour_length=0;
        for(int i=0; i<tour.size()-1; i++)
        {
            tour_length+=adj[tour[i]][tour[i+1]];
        }
        return tour_length+adj[tour[tour.size()-1]][0];

    }

};
int main()
{
    int x;
    cout<<"Enter number of test cases:"<<endl;
    cin>>x;
    for(int i=1; i<=x; i++)
    {
        Graph g;
        vector<vector<int>>adj=g.Create_Random_Graph(20);
        vector<int>optimum_tour=g.Exact_TSP(adj,0);
        vector<int>eulerian_tour_unique=g.Metric_Approximation_TSP(adj);
        int Approximate_Tour_Length=g.Calculate_Tour_Length(eulerian_tour_unique,adj);
        int Optimum_Tour_Length=g.Calculate_Tour_Length(optimum_tour,adj);
        cout<<"Test case: "<<i<<", "<<"Ratio : "<<(Approximate_Tour_Length*1.0/Optimum_Tour_Length)<<endl;
    }

}
