#include<bits/stdc++.h>
#define int long long
#define uint unsigned long long
#define log2(X) ((unsigned) (8*sizeof (ull) - __builtin_clzll((X)) - 1))
#define N (int)1e6+5
#define endl "\n"
#define print(a,s,e) for(int i=s;i<e;i++) cout<<a[i]<<"  "; cout<<endl;
#define io_unsync ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;
int tree[N << 1];
bool lazy[N << 1];
pair<int, int> range[N << 1];
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
class sgt_coin_flipper
{
    int fid;
    uint length;
    static inline int combiner(int x, int y) { return x + y; }
    void build()
    {
        for(int i = this->length-1; i>0; i--)
        {
            tree[i] = sgt_coin_flipper::combiner(tree[i<<1], tree[i<<1|1]);
            lazy[i] = false;
            range[i].first = range[i << 1].first, range[i].second = range[i << 1 | 1].second;
        }
    }

    inline bool is_leaf(int index) { return (index >= this->length) && (index < this->length<<1); }

    void push_down(int index)      /// O(1)
    {   assert(lazy[index]);
        //left child
        tree[index<<1] = (range[index<<1].second - range[index<<1].first + 1) - tree[index<<1];
        if(!is_leaf(index<<1))
            lazy[index<<1] = true;
        //right child
        tree[index<<1|1] = (range[index<<1|1].second - range[index<<1|1].first + 1) - tree[index<<1|1];
        if(!is_leaf(index<<1|1))
            lazy[index<<1|1] = true;
        lazy[index] = false;
    }

public:
    sgt_coin_flipper(uint n, int fid) : length(n), fid(fid) { build(); }
    void update(uint node, uint l, uint r)
    {   if(!this->is_leaf(node) && lazy[node])
            this->push_down(node);
        if(range[node].first > r || range[node].second < l)
            return;
        if(range[node].first >= l && range[node].second <= r)
        {
            if(!is_leaf(node)) lazy[node] = true;
            tree[node] = range[node].second - range[node].first + 1 - tree[node];
            return;
        }
        update(node<<1, l, r);
        update(node<<1|1, l, r);
        tree[node] = sgt_coin_flipper::combiner(tree[node<<1], tree[node<<1|1]);
    }
    int query(uint node, uint l, uint r)
    {
        if(range[node].first > r || range[node].second < l)
            return this->fid;
        if(!this->is_leaf(node) && lazy[node])
            this->push_down(node);
        if((range[node].first >= l && range[node].second <= r))
            return tree[node];
        return sgt_coin_flipper::combiner(query(node<<1, l, r), query(node<<1|1, l, r));
    }
};

int32_t main()
{
    //io_unsync
    uint oglen, q, l, r;
    int fid = 0, type;
    cin>>oglen>>q;
    uint len = ceilp2(oglen);
    for(uint i=0;i<len;i++)
    {
        tree[len+i] = 0;
        range[len+i].first = i, range[len+i].second = i;
    }
    sgt_coin_flipper desparado(len, fid);
    while(q--)
    {
        cin>>type>>l>>r;
        if(type == 0)
            desparado.update(1, l, r);
        else
            cout<<desparado.query(1, l, r)<<endl;
        //print(tree, 1, len<<1);
    }
}
