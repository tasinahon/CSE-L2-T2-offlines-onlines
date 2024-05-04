#include<bits/stdc++.h>
using namespace std;
ofstream out("kruskal.txt");
class Graph{
public:
    int n,m;
    double sum;
    vector<pair<double,pair<int,int>>>adj;
    vector<int>parent_list;
    vector<int>rank_list;
    list<pair<int,int>>li;
    Graph(int n,int m){
        this->n=n;
        this->m=m;
       for(int i=0;i<n;i++){
        parent_list.push_back(i);
       }
       for(int i=0;i<n;i++){
        rank_list.push_back(0);
       }
       sum=0;


    }

    void sorting(){
        sort(adj.begin(),adj.end());
    }

    int main_parent(int v){
        if(parent_list[v]==v){
            return v;
        }
        parent_list[v]=main_parent(parent_list[v]);
        return parent_list[v];
    }
    void union_of_two(int u,int v){
        int a=main_parent(u);
        int b=main_parent(v);
        if(rank_list[a]<rank_list[b]){
            parent_list[a]=b;
        }
        else if(rank_list[a]>rank_list[b]){
            parent_list[b]=a;
        }
        else{
            parent_list[a]=b;
            rank_list[b]++;
        }


    }
    void mst(){
        for(auto it:adj){
            double w=it.first;
            int u=it.second.first;
            int v=it.second.second;
            if(main_parent(u)!=main_parent(v)){
                li.push_back({u,v});
                sum+=w;
                union_of_two(u,v);
            }
        }
    }
    void print(){
        out<<"Kruskal's Algorithm"<<endl;
        out<<"Total weight="<<" "<<sum<<endl;
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
        g.adj.push_back({w,{u,v}});
        c++;
    }
    g.sorting();
    g.mst();
    g.print();

}
