#include<iostream>
#include<list>
#include<vector>
#include<stack>
using namespace std;

int V;

void topoutil(int v, bool visited[], stack<int> &s,vector<list<int> > adj)
{
    visited[v]=true;
    for(list<int>::iterator i = adj[v].begin();i!=adj[v].end();i++)
    {
        if(!visited[*i])
            topoutil(*i,visited,s,adj);
    }

    s.push(v);
}

void toposort(vector<list<int> > v)
{
    stack<int> s;
    bool *visited=new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    for(int i=0;i<V;i++)
        if(!visited[i])
            topoutil(i,visited,s,v);

    while (!s.empty())
    {
        cout <<s.top()+1<< " ";
        s.pop();
    }
}

int main()
{
    cout<<"Enter the number of edges: ";
    cin>>V;
    vector<list<int> > adj(V);
    int a[10][10];
    cout<<"\nEnter edge weights: \n";
    for(int i=0;i<V;i++)
    {
        for(int j=0;j<V;j++)
        {   cin>>a[i][j];
            if(a[i][j])
                adj[i].push_back(j);
        }
    }
    cout<<endl<<endl;
    toposort(adj);

}
