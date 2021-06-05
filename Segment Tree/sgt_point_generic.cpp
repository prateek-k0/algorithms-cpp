#include<bits/stdc++.h>
#define uint unsigned long long
#define int long long
#define N (uint)1e6+5
#define endl "\n"
#define print(a,s,e) for(uint i=s;i<e;i++) cout<<a[i]<<"  "
#define io_unsync ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int tree[N << 1];

/// Segment Tree definition
template <typename T>    /// T = datatype of the elements to be stored inside the array
class SegmentTree
{
    uint length;
    T fid, *tree_arr;    /// fid = function-identity;
    std::function<T(T, T)> combiner;     /// pass combiner function;

    inline void build(){            ///tree init
        for(uint i = this->length-1; i > 0; i--)
            this->tree_arr[i] = this->combiner(this->tree_arr[i << 1], this->tree_arr[i << 1 | 1]);   /// root is at index 1, left children are even indexed.
    }

public:

    SegmentTree(T* arr, uint len, std::function<T(T, T)> func, T fid) : tree_arr(arr), length(len), combiner(func), fid(fid) { build(); }

    inline void point_update(uint index, T value)       /// update function, O(logn), propagate_up
    {
        assert(index >= 0 && index < this->length);
        for(this->tree_arr[index += this->length] = value, index >>= 1; index > 0; index >>= 1)       /// declaration; condition; update
            this->tree_arr[index] = this->combiner(this->tree_arr[index << 1], this->tree_arr[index << 1 | 1]);    /// 2*index, 2*index + 1, merge operation
    }

    T query(uint l, uint r)         ///query function - query on range [l, r], O(logn)
    {
        assert(l >= 0 && r <= this->length);
        T resl = this->fid, resr = this->fid;       /// for non-coummutative combiner functions
        for(l += this->length, r += this->length; r >= l; l >>= 1, r >>= 1)
        {
            if(l&1) { resl = this->combiner(resl, this->tree_arr[l++]); }       /// l is odd indexed
            if(!(r&1)) { resr = this->combiner(this->tree_arr[r--], resr); }    /// r is even indexed
        }
        return this->combiner(resl, resr);
    }
};

int32_t main()
{
    int n, q, l, vr;
    char qt;
    cin>>n>>q;
    for(uint i = 0; i < n; i++)  cin>>tree[n+i];
    SegmentTree<int> obj(tree, n, [](int x, int y) -> int {return x<y?x:y;}, (int)1e9);
    while(q--)
    {
        cin>>qt>>l>>vr;
        if(qt=='q') cout<<obj.query(l-1, vr-1)<<endl;
        else obj.point_update(l-1, vr);
    }
}






