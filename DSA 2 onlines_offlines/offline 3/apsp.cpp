#include<bits/stdc++.h>
using namespace std;
ofstream out("output.txt");
class Graph
{
public:
    int n,m;
    int **distance;

    Graph(int n,int m)
    {
        this->n=n;
        this->m=m;
        distance=new int*[n+1];
        for(int i=1; i<=n; i++)
        {
            distance[i]=new int[n+1];
        }

        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(i==j)
                {
                    distance[i][j]=0;
                }
                else
                {
                    distance[i][j]=INT_MAX;

                }

            }
        }
    }
    int** matrix_multiplication(int **L1, int **L2)
    {
        int** newm = new int*[n + 1];
        for (int i = 1; i <= n; ++i)
        {
            newm[i] = new int[n + 1];
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                newm[i][j] = INT_MAX;
                for (int k = 1; k <= n; k++)
                {
                    if (L1[i][k] != INT_MAX && L2[k][j] != INT_MAX)
                    {
                        newm[i][j] = min(newm[i][j], L1[i][k] + L2[k][j]);
                    }
                }
            }
        }
        return newm;
    }

    void call_matrix_multiplication()
    {
        int** L = new int*[n + 1];
        for (int i = 1; i <= n; i++)
        {
            L[i] = new int[n + 1];
            for (int j = 1; j <= n; j++)
            {
                L[i][j] = distance[i][j];
            }
        }

        int mo = 1;
        while (mo < n - 1)
        {
            L = matrix_multiplication(L, L);
            mo *= 2;
        }
        print_matrix(L);


    }
    void Floyd_warshell()
    {
        for(int vertex=1; vertex<=n; vertex++)
        {
            for(int i=1; i<=n; i++)
            {
                for(int j=1; j<=n; j++)
                {
                    if(distance[i][vertex]!=INT_MAX && distance[vertex][j]!=INT_MAX)
                    {
                        distance[i][j]=min(distance[i][j],(distance[i][vertex]+distance[vertex][j]));
                    }
                    else
                    {
                        distance[i][j]=distance[i][j];
                    }

                }
            }
        }
    }
    void print_warshell()
    {
        out<<"Shortest distance matrix"<<endl;
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(distance[i][j]==INT_MAX)
                {
                    out<<"INF"<<" ";
                }
                else
                {
                    out<<distance[i][j]<<" ";
                }

            }
            out<<endl;
        }
    }
    void print_matrix(int **L)
    {
        out<<"Shortest distance matrix"<<endl;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (L[i][j] == INT_MAX)
                {
                    out << "INF" << " ";
                }
                else
                {
                    out << L[i][j] << " ";
                }
            }
            out << endl;
        }
        out<<endl<<endl;
    }
};
int main()
{

    ifstream in("input.txt");
    int n,m;
    string str;
    getline(in,str);
    istringstream s(str);
    s>>n;
    s>>m;
    Graph g(n,m);
    int u,v,w;
    for(int i=0;i<m;i++)
    {
        getline(in,str);
        istringstream s1(str);
        s1>>u;
        s1>>v;
        s1>>w;
        g.distance[u][v]=w;

    }
    g.Floyd_warshell();
    g.print_warshell();
    //g.call_matrix_multiplication();


}
