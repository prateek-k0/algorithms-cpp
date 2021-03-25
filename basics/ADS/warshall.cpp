#include<iostream>
using namespace std;

int V;
void printsol(int dist[4][4])
{
    cout<<endl;
    for(int i=0;i<V;i++)
    {
        for(int j=0;j<V;j++)
        {
            if(dist[i][j]==100)
                cout<<"INF\t";
            else cout<<dist[i][j]<<"\t";

        }
        cout<<endl;
    }
}

void warshall(int adj[4][4])
{
    int dist[4][4];
    for(int i=0;i<V;i++)
        for(int j=0;j<V;j++)
            dist[i][j]=adj[i][j];

    for(int k=0;k<V;k++)
    {
        for(int i=0;i<V;i++)
        {
            for(int j=0;j<V;j++)
            {
                if(dist[i][k]+dist[k][j]<dist[i][j])
                    dist[i][j]=dist[i][k]+dist[k][j];
            }
        }
    }

    printsol(dist);
}

int main()
{   V=4;
    int adj[4][4]={{0,5,100,10},{100,0,3,100},{100,100,0,1},{100,100,100,0}};
    warshall(adj);
    return 0;
}
