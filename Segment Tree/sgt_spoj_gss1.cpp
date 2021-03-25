#include<bits/stdc++.h>
#define int long long
#define uint unsigned long long
#define N (int)2e5
#define endl "\n"
#define print(a,s,e) for(uint i=s;i<e;i++) cout<<a[i]<<"  "
#define io_unsync ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define inf (int)1e9
/// reference : https://www.geeksforgeeks.org/maximum-subarray-sum-given-range/
using namespace std;

struct node
{
    int mps, mss, ts, msas;
    node(int val)
    {
        mps = mss = ts = msas = val;
    }
    node()
    {
        mps = mss = ts = msas = -inf;
    }
}tree[N << 1];

uint ceilp2(uint n)
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

class sgt
{
    uint length;
    static node combiner(node l, node r)
    {
        node par;
        par.mps = max(l.mps, l.ts+r.mps);
        par.mss = max(r.mss, r.ts+l.mss);
        par.ts = l.ts + r.ts;
        par.msas = max({l.msas, r.msas, l.mss+r.mps});
        return par;
    }
    inline void build()
    {
        for(uint i = this->length - 1; i > 0; i--)
            tree[i] = sgt::combiner(tree[i<<1], tree[i<<1|1]);
    }
public:
    sgt(uint n) : length(n) { this->build(); }
    node query(uint l, uint r)
    {
        assert(l >= 0 && r <= this->length);
        node resl, resr;
        for(l += this->length, r+= this->length; r >= l; l >>= 1, r >>= 1)
        {
            if(l&1) { resl = sgt::combiner(resl, tree[l++]); }
            if(!(r&1)) { resr = sgt::combiner(tree[r--], resr); }
        }
        return sgt::combiner(resl, resr);
    }
};
int32_t main()
{
    //io_unsync
    uint oglen, len, m, l, r;
    int a;
    cin>>oglen;
    len = ceilp2(oglen);
    for(uint i = 0; i < len; i++)
    {
        if(i >= oglen) { tree[i+len] = node();}
        else
        {
            cin>>a;
            tree[i+len] = node(a);
        }
    }
    sgt obj(len);
    cin>>m;
    while(m--)
    {
        cin>>l>>r;
        node p = obj.query(l-1, r-1);
        cout<<p.msas<<endl;
    }

    return 0;
}
