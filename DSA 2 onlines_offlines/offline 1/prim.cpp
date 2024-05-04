#include<bits/stdc++.h>
using namespace std;
ofstream out("prim.txt");

class Graph{
public:
    int *vis;
    int n,m;
    double sum;
    list<pair<int,int>>li;
    vector<pair<int,double>>*adj;
    priority_queue<pair<double,pair<int,int>>,vector<pair<double,pair<int,int>>>,greater<pair<double,pair<int,int>>>>container;
    Graph(int n,int m){
        this->n=n;
        this->m=m;
        vis=new int[n+1];
        for(int i=0;i<n;i++){
            vis[i]=0;
        }
        vis[0]=1;
        adj=new vector<pair<int,double>>[n+1];
        sum=0;
    }
    void mst(){
        container.push({0,{0,-1}});
        while(!container.empty()){
            auto it=container.top();
            container.pop();
            double w=it.first;
            int node=it.second.first;
            int parent=it.second.second;
            if(vis[node]!=1 && parent!=-1){
                    li.push_back({node,parent});
                    vis[node]=1;
                    sum+=w;

            }

            for(auto it:adj[node]){
                if(!vis[it.first]){
                    container.push({it.second,{it.first,node}});
                }
            }
        }


    }
    void print(){
        out<<"Total weight="<<" "<<sum<<endl;
        out<<"Root node="<<" "<<"0"<<endl;
        for(auto it:li){
            out<<it.first<<" "<<it.second<<endl;
        }



    }



};
int main(){
    ifstream in("in.txt");
    string str;
    int c=0;
    int u,v;
    double w;
    getline(in,str);
    istringstream s(str);
    int n,m;
    s>>n;
    s>>m;
    Graph g(n,m);
    while(c!=m)
    {
        getline(in,str);
        istringstream sa(str);
        sa>>u;
        sa>>v;
        sa>>w;
        g.adj[u].push_back({v,w});
        g.adj[v].push_back({u,w});
        c++;
    }

    g.mst();
    g.print();

}
