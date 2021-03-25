#include<iostream>
#include<vector>
using namespace std;

int *visited;
int V=0;
vector<int> *x;

int ret_dfs(int u,int *visited,int parent)
{
    visited[u]=1;

   vector<int>::iterator i;
   for(i=x[u].begin();i!=x[u].end();i++)
   {

    if(!visited[*i])
        if(ret_dfs(*i,visited,u))
            return 1;

   else if(*i!=parent)
        return 1;
   }
   return 0;
}

int main()
{
    cout<<"Enter the number of nodes: ";
    cin>>V;
    int a=0,f=0;
    visited = new int[V];
     x = new vector<int>[V];
    cout<<"\nEnter the edges: \n";
    for(int i=0;i<V;i++)
    {
        for(int j=0;j<V;j++)
        {
            cout<<"\nEdge("<<i<<","<<j<<")? ";
            cin>>a;
            if(a)
                x[i].push_back(j);
        }
    }
    for(int i=0;i<V;i++)
        visited[i]=0;
    for(int i=0;i<V;i++)
    {
        if(!visited[i])
            if(ret_dfs(i,visited,-1))
                f=1;
    }

    if(f)
        cout<<"\ncycle exists";
    else cout<<"no cycle exists";

}
