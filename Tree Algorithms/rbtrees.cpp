///https://www.codechef.com/problems/RBTREES
#include<bits/stdc++.h>
#define uint unsigned long long
#define int long long
#define N (uint)2e5
#define endl "\n"
#define print(a,s,e) for(uint i=s;i<e;i++) cout<<a[i]<<"  "
#define io_unsync ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;
int color_balance[N], ans, org_color[N];
vector<int> graph[N];
void dfs(int node, int parent, int true_color)
{
    if(true_color != org_color[node])
        color_balance[node] += org_color[node];
    for(auto nei:graph[node])
    {
        if(nei!=parent)
        {
            dfs(nei, node, true_color*(-1));
            color_balance[node] += color_balance[nei];
            ans += abs(color_balance[nei]);
        }
    }
}
int solve(int beg_col)
{
    fill_n(color_balance, N, 0);
    ans = 0;
    dfs(0, -1, beg_col);
    if(color_balance[0]!=0)
        return (int)1e7;
    return ans;
}
int32_t main()
{
    int t, col, n, u, v;
    string color_combo;
    for(cin>>t; t--; )
    {
        cin>>n;
        for(int i = 0; i<n-1; i++)
        {
            cin>>u>>v;
            graph[u-1].push_back(v-1);
            graph[v-1].push_back(u-1);
        }
        cin>>color_combo;
        for(int i=0; i<n; i++)
        {
            if(color_combo[i]=='1')
                org_color[i] = 1;
            else org_color[i] = -1;
        }
        u = solve(1), v = solve(-1);
        int a = min(u, v);
        if(a == (int)1e7)
            cout<<-1;
        else cout<<ans;
        ans=0, fill_n(org_color,n,0);
        for(int i = 0; i<n; i++) graph[i].clear();
    }
    return 0;
}
