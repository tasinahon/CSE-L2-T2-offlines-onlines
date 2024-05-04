#include<bits/stdc++.h>
using namespace std;
ofstream out("outs.txt");
class Graph
{
public:
    int n,m;
    vector<pair<int,int>>*adj;
    int *distance;
    stack<int>st;
    int f;
    int source,destination;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>container;
    vector<pair<int,pair<int,int>>>edges;
    int *path;
    int *path_bellman;
    Graph(int n,int m){
        this->n=n;
        this->m=m;
        adj=new vector<pair<int,int>>[n+1];
        distance=new int[n+1];
        for(int i=1;i<n;i++){
            distance[i]=INT_MAX;
        }
        path=new int [n+1];
        for(int i=0;i<n;i++){
            path[i]=i;
        }
        path_bellman=new int[n+1];
        for(int i=0;i<n;i++){
            path_bellman[i]=i;
        }

    }
    void set_source_destination(int s,int d){
        source=s;
        destination=d;
    }
    void shortest_distance_dijkstra()
    {
        for(int i=0;i<n;i++){
            distance[i]=INT_MAX;
        }
        distance[source]=0;
        container.push({0,source});
        while(!container.empty()){
            auto it=container.top();
            container.pop();
            int w=it.first;
            int node=it.second;
            for(auto ite:adj[node]){
                if(w+ite.second<distance[ite.first] ){
                    distance[ite.first]=w+ite.second;
                    container.push({distance[ite.first],ite.first});
                    path[ite.first]=node;
                }
            }
        }
        store_path(destination);
    }
    void shortest_distance_bellman(){

        distance[source]=0;
        for(int i=0;i<n-1;i++)
        {
            for(auto it:edges)
            {
                if(distance[it.second.first]!=INT_MAX && distance[it.second.first]+it.first<distance[it.second.second])
                {
                    distance[it.second.second]=distance[it.second.first]+it.first;
                    path_bellman[it.second.second]=it.second.first;
                }
            }

        }
        f=0;
        for(auto it:edges)
            {
                if(distance[it.second.first]+it.first<distance[it.second.second])
                {
                    out<<"Bellman Ford Algorithm:"<<endl;
                    out<<"Negative weight cycle present"<<endl;
                    f=1;
                }

            }
            if(!f){
                store_path_bellman(destination);
            }
    }
    void store_path_bellman(int dest)
    {
        st.push(dest);
        if(dest!=source){
            store_path_bellman(path_bellman[dest]);
        }
        /*for(int i=0;i<n;i++){
            cout<<path_bellman[i]<<" ";
        }*/
    }
     void print_bellman(){
        out<<"Bellman Ford Algorithm:"<<endl;
        out<<distance[destination]<<endl;
        while(!st.empty()){
            out<<st.top();
            if(st.top()!=destination){
                out<<"->";
            }

            st.pop();
        }

    }
    void store_path(int dest){

        st.push(dest);
        if(dest!=source){
            store_path(path[dest]);
        }
    }
    void print(){
        out<<endl;
        out<<endl;
        out<<"Dijkstra Algorithm:"<<endl;
        out<<distance[destination]<<endl;
        while(!st.empty()){
            out<<st.top();
            if(st.top()!=destination){
                out<<"->";
            }

            st.pop();
        }
    }

};
int main()
{

    ifstream in("in.txt");
    string str;
    int n,m,u,v,w,source,destination;
    getline(in,str);
    istringstream s(str);
    s>>n;
    s>>m;
    Graph g(n,m);
    for(int i=0;i<m;i++){
        getline(in,str);
        istringstream sa(str);
        sa>>u;
        sa>>v;
        sa>>w;
        g.adj[u].push_back({v,abs(w)});
        g.edges.push_back({w,{u,v}});
    }
    getline(in,str);
    istringstream so(str);
    so>>source;
    so>>destination;
    g.set_source_destination(source,destination);
    g.shortest_distance_bellman();
    if(g.f==0){
    g.print_bellman();
    }
    g.shortest_distance_dijkstra();
    g.print();


}
