#include<bits/stdc++.h>
#define uint unsigned long long
#define int long long
#define N (uint)1e6+5
#define endl "\n"
#define print(a,s,e) for(uint i=s;i<e;i++) cout<<a[i]<<"  "
#define io_unsync ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;
int tree[N << 1];
class SegmentTree
{
    int fid; uint length;
    static inline int combiner(int x, int y) {return x<y?x:y;}    ///change as per the requirement
    inline void build(void){
        for(uint i = this->length-1; i > 0; i--)
            tree[i] = SegmentTree::combiner(tree[i << 1], tree[i << 1 | 1]);    /// root is at index 1, left children are even indexed.
    }

public:

    SegmentTree(uint n, int fid) : length(n), fid(fid) { build(); }

    inline void point_update(uint index, int value)        ///  O(logn), propagate_up
    {
        assert(index >= 0 && index < this->length);
        for(tree[index += this->length] = value, index >>= 1; index > 0; index >>= 1)        /// declaration; condition; update
            tree[index] = SegmentTree::combiner(tree[index << 1], tree[index << 1 | 1]);    /// 2*index, 2*index + 1, merge operation
    }

    int query(uint l, uint r)               /// query on range [l, r], O(logn)
    {
        assert(l >= 0 && r <= this->length);
        int resl = this->fid, resr = this->fid;    /// for non-coummutative combiner functions
        for(l += this->length, r += this->length; r >= l; l >>= 1, r >>= 1)
        {
            if(l&1) { resl = SegmentTree::combiner(resl, tree[l++]); }         /// l is odd indexed
            if(!(r&1)) { resr = SegmentTree::combiner(tree[r--], resr); }      /// r is even indexed
        }
        return SegmentTree::combiner(resl,resr);
    }
};
int32_t main()
{   //io_unsync
    uint n,q;
    cin>>n>>q;
    for(uint i = 0;i<n;i++) cin>>tree[n+i];
    SegmentTree obj(n,(int)1e6);
    while(q--)
    {   char a;
        uint l,vr;
        cin>>a>>l>>vr;
        if(a=='q') cout<<obj.query(l-1,vr-1)<<endl;
        else obj.point_update(l-1, vr);
    }
    return 0;
}
