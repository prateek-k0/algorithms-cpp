#include<bits/stdc++.h>
#define uint unsigned long long
#define int long long
#define N (uint)3e5
#define endl "\n"
#define print(a,s,e) for(uint i=s;i<e;i++) cout<<a[i]<<" "; cout<<endl;
#define io_unsync ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pii pair<int, int>
using namespace std;
vector<int> graph[N], graph2[N];
vector<pii> st; //prefix_pop_n_day_sum_stack
int p[N], b[N], a[N], ans[N], ord[N], parent[N], present[N];

uint find_parent(int x)
{
    return parent[x] == x? x : parent[x]=find_parent(parent[x]);
}

void node_union(int u, int v)
{
    v = find_parent(v);
    parent[v] = u;
    graph2[u].push_back(v);
}

void dfs(int node)
{
    st.push_back(pii(st.back().first + a[node], ord[node]+1));
    int end_day = lower_bound(st.begin(), st.end(), pii(b[node],0)) - st.begin();
    if(end_day < st.size())
        ans[node] = st[end_day].second;

    for(auto nei:graph2[node])
        dfs(nei);
    st.pop_back();
}

int32_t main()
{   //io_unsync
    int t, n, u, v, pab;
    for(cin>>t; t--;)
    {
        cin>>n;
        fill_n(ans, n+1, -1);
        fill_n(present, n+1, 0);
        iota(parent, parent+n+1, 0);
        st.clear();
        for(int i = 0; i<n; i++)
        {
            graph[i].clear(), graph2[i].clear();
        }
        for(int i=0; i<n-1; i++)
        {
            cin>>u>>v;
            graph[u-1].push_back(v-1), graph[v-1].push_back(u-1);
        }
        for(int i=0; i<n; i++)
        {
            cin>>pab;
            p[i] = pab-1, ord[p[i]] = i;
        }
        for(int i=0; i<n; i++)
        {
            cin>>pab;
            a[i] = pab;
        }
        for(int i=0; i<n; i++)
        {
            cin>>pab;
            b[i] = pab;
        }
        for(int i=n-1; i>=0; i--)
        {
            present[p[i]] = 1;
            for(auto nei:graph[p[i]])
            {
                if(present[nei])
                    node_union(p[i], nei);
            }
        }
        st.push_back(pii(0,0));
        dfs(p[0]);
        print(ans,0,n);
    }
    return 0;
}
