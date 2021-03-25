#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define ll long long
#define int ll
#define log2(X) ((unsigned) (8*sizeof (ull) - __builtin_clzll((X)) - 1))
#define N (int)1e6+5
#define endl "\n"
#define print(a,s,e) for(int i=s;i<e;i++) cout<<a[i]<<"  "; cout<<endl;
#define io_unsync ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
int tree[N << 1], nentry[N], nexit[N];
vector<int>euler;
pair<bool, int> lazy[N];
pair<int, int> range[N << 1];
vector<int> adj[N];
int ceilp2(int n)
{
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32;
    return ++n;
}
class SegmentTree2
{
    int fid, height;
    ull length;
    static inline int combiner(int x, int y) { return x + y; }        ///modify as per requirement
    void build(void)
    {
        for(int i = this->length-1; i>0; i--)
        {
            tree[i] = SegmentTree2::combiner(tree[i << 1], tree[i << 1 | 1]);
            lazy[i].first = false, lazy[i].second = 0;
            range[i].first = range[i << 1].first, range[i].second = range[i << 1 | 1].second;
        }
    }
    /// aux functions
    inline bool is_leaf(int index) { return (index >= this->length) && (index < this->length<<1); }

    void push_down(int index)      /// O(1)
    {   assert(lazy[index].first);
        int ss = range[index << 1].second - range[index << 1].first + 1, val = lazy[index].second;
        if(!this->is_leaf(index << 1))
        {
            lazy[index << 1].first = true, lazy[index << 1].second = val;
            lazy[index << 1 | 1].first = true, lazy[index << 1 | 1].second = val;
        }
        tree[index << 1] = val*ss, tree[index << 1 | 1] = val*ss;
        lazy[index].first = false, lazy[index].second = 0;
    }

    void push_up(int index, int val)             /// O(logn)
    {
        int ss = range[index].second - range[index].first + 1;
        for(int h = (int)log2(index); h >=0; h--)       ///clear path from top to bottom
        {
             if(!this->is_leaf(index >> h) && lazy[index >> h].first) { this->push_down(index >> h); }
        }
        if(!is_leaf(index)) lazy[index].first = true, lazy[index].second = val;
        for(tree[index] = val * ss, index >>= 1; index > 0; index >>= 1)        ///propagate up
            tree[index] = SegmentTree2::combiner(tree[index << 1], tree[index << 1 | 1]);
    }

public:

    SegmentTree2(ull n, int fid) : length(n), fid(fid), height((int)log2(n)) { build(); }

    void assignment_update(int l, int r, int val)  /// assignment update, O((logn)^2)
    {
        assert(l >= 0 && r <= this->length);int c = 0;
        for(l += this->length, r += this->length; r >= l; l >>= 1, r >>= 1)
        {
            if (l&1) { this->push_up(l++, val); }
            if (!(r&1)) { this->push_up(r--, val); }
        }
    }
    void update(int node, int l, int r, int val)
    {
        if(range[node].first > r || range[node].second < l)
            return;
        if(lazy[node].first)
            this->push_down(node);
        if(range[node].first >= l && range[node].second <= r)
        {
            if(!is_leaf(node)) lazy[node].first = true, lazy[node].second = val;
            tree[node] = (range[node].second - range[node].first + 1)*val;
            return;
        }
        update(node << 1, l, r, val);
        update(node << 1 | 1, l, r, val);
        tree[node] = SegmentTree2::combiner(tree[node << 1], tree[node << 1 | 1]);
    }

    int query(int node, int l, int r)
    {
        if(range[node].first > r || range[node].second < l)
            return this->fid;
        if(this->is_leaf(node) || (range[node].first >= l && range[node].second <= r))
            return tree[node];
        if(lazy[node].first)
            this->push_down(node);
        return SegmentTree2::combiner(query(node << 1, l, r), query(node << 1 | 1, l, r));
    }
};

int timer = 0;
void dfs(int node, int par)
{
    nentry[node] = timer++;
    //euler.push_back(1);
    for(auto i:adj[node])
    {
        if(i!=par)
            dfs(i, node);
    }
    nexit[node] = timer - 1;
}

int32_t main()
{   //io_unsync
    ull oglen;
    int fid = 0;       /// change fid
    cin>>oglen;
    ull len = ceilp2(oglen);
    /*
    for(ull i=0;i<len;i++)
    {
        if(i>=oglen) tree[len+i] = fid;
        else cin>>tree[len+i];
        range[len+i].first = i, range[len+i].second = i;
    }
    SegmentTree2 obj(len, fid);
    print(tree,0,len<<1);
    cout<<obj.query(1, 3, 4);
    */
    int par, root;
    for(int i=1; i <= oglen; i++)
    {
        cin>>par;
        if(par == 0) root = i-1;
        else
        {
            adj[i-1].push_back(par-1);
            adj[par-1].push_back(i-1);
        }
    }
    dfs(root, -1);
    for(int i = 0; i < len; i++)
    {
        if(i >= oglen) tree[len+i] = fid;
        else
        {
            tree[len+i] = 1
        }
        range[len+i].first = i, range[len+i].second = i;
    }
    SegmentTree2 obj(len, fid);
    //print(tree,0,len<<1);

    int q,type,sol;
    cin>>q;
    while(q--)
    {
        cin>>type>>sol;
        if(type==1)
        {
            if(nentry[sol-1] != nexit[sol-1])
            {
                obj.update(1,nentry[sol-1]+1,nexit[sol-1],1);
                //print(tree,0,len<<1);
            }
        }
        else if(type==2)
        {
            if(nentry[sol-1] != nexit[sol-1])
            {
                obj.update(1,nentry[sol-1]+1,nexit[sol-1],0);
                //print(tree,0,len<<1);
            }
        }
        else{
            if(nentry[sol-1] != nexit[sol-1])
            {
                cout<<obj.query(1,nentry[sol-1]+1, nexit[sol-1])<<endl;
            }
            else cout<<0<<endl;
        }
    }

    return 0;
}
