#include<iostream>
using namespace std;

int V;
int mind(int dist[],bool spt[])
{
    int m = 999,min_index;
    for(int i=0;i<V;i++)
    {
        if(!spt[i] && dist[i]<=m)
            m=dist[i],min_index=i;
    }

    return min_index;
}

int printsol(int dist[],int n)
{
    cout<<endl;
    for(int i=0;i<V;i++)
        cout<<i<<"\t\t"<<dist[i]<<endl;
}

void djkstra(int adj[9][9],int src)
{
    int dist[V];
    bool spt[V];

    for(int i=0;i<V;i++)
    {
        dist[i]=999;
        spt[i]=false;
    }

    dist[src]=0;
    for(int c=0;c<V-1;c++)
    {
        int u=mind(dist,spt);
        spt[u]=true;
        for(int v=0;v<V;v++)
        {
            if(!spt[v] && adj[u][v] && dist[u]!=999 && dist[u]+adj[u][v]<dist[v])
                dist[v]=dist[u]+adj[u][v];
        }
    }

    printsol(dist,V);
}

int main()
{   V=9;
    int adj[9][9]={{0,4,0,0,0,0,0,8,0},{4,0,8,0,0,0,0,11,0},{0,8,0,7,0,4,0,0,2},{0,0,7,0,9,14,0,0,0},{0,0,0,9,0,10,0,0,0},{0,0,4,14,10,0,2,0,0},{0,0,0,0,0,2,0,1,6},{8,11,0,0,0,0,1,0,7},{0,0,2,0,0,0,6,7,0}};
    djkstra(adj,0);

}
