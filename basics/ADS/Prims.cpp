#include<iostream>
using namespace std;

int V=4;

int mine(int key[],bool mst[])
{
    int m=100,min_index;
    for(int i=0;i<V;i++)
    {
        if(mst[i]==false && key[i]<m)
            m=key[i],min_index=i;
    }
    return min_index;
}

void print_mst(int parent[4], int n, int adj[][4])
{
    cout<<"Edge\tWeight\n";
    for(int i=1;i<V;i++)
        cout<<parent[i]<<" - "<<i<<"\t"<<adj[i][parent[i]]<<endl;
}

void prim(int adj[4][4])
{
    int parent[V],key[V],u;
    bool mst[V];

    for(int i=0;i<V;i++)
        key[i]=100,mst[i]=false;

    key[0]=0;   //source
    parent[0]=-1;

    for(int j=0;j<V-1;j++)
    {
        u=mine(key,mst);
        mst[u]=true;

        for(int v=0;v<V;v++)
        {
            if(adj[u][v] && mst[v]==false && adj[u][v]<key[v])
                parent[v]=u,key[v]=adj[u][v];
        }
    }

    print_mst(parent,V,adj);
}

int main()
{   int adj[4][4],i,j;
     cout<<"\nEnter the cost adjacency matrix: ";
    for(i=0;i<4;i++)
    {   for(j=0;j<4;j++)
        {
            cin>>adj[i][j];
            if(!adj[i][j])
                adj[i][j]=100;
        }
    }
    prim(adj);
}
