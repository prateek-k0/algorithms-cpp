#include<iostream>
#include<stdlib.h>
using namespace std;
int i,j,mincost=0,a,b,u,v,n,m,ne=1;
int parent[10];
int findv(int i)
{
    if(parent[i])
        i=parent[i];
    return i;
}

int uni(int i,int j)
{
    if(i!=j)
    {
        parent[j]=i;
        return 1;
    }
    return 0;
}

int main()
{
    int adj[10][10];
    cout<<"Enter the number of vertices";
    cin>>n;
    cout<<"\nEnter the cost adjacency matrix: ";
    for(i=1;i<=n;i++)
    {   for(j=1;j<=n;j++)
        {
            cin>>adj[i][j];
            if(!adj[i][j])
                adj[i][j]=100;
        }
    }
    cout<<"\n\n";

    while(ne<n)
    {
        for(i=1,m=100;i<=n;i++)
        {
            for(j=1;j<=n;j++)
            {
                if(adj[i][j]<m)
                {
                    m=adj[i][j];
                    a=u=i;
                    b=v=j;
                }
            }
        }
        u=findv(u);
        v=findv(v);
        if(uni(u,v));
        {
            cout<<"edge ("<<a<<" , "<<b<<") : "<<m<<endl;
            ne++;
            mincost+=m;
        }
        adj[a][b]=adj[b][a]=100;

    }
    cout<<endl<<"mincost: "<<mincost;
return 0;
}
