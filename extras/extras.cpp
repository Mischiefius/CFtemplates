#include <bits/stdc++.h>
using namespace std;


//-----------------------DSU-----------------------// 20
struct DSU{
    vector<int> lnk;
    DSU(int n){
        lnk = vector<int>(n,-1);
    }
    int find(int x){
        if (lnk[x] < 0) return x;
        return lnk[x] = find(lnk[x]);
    }
    int unite(int x, int y){
        x = find(x); y = find(y);
        if (x==y) return 0;

        if (lnk[x] == lnk[y]) {lnk[x]--;lnk[y] = x;}
        else if (lnk[x] < lnk[y]) lnk[y] = x;
        else lnk[x] = y;
        return 1;
    }
};

//----------------------hash----------------------// 19
template<typename T>
struct Rhash{
    static size_t size_t_random(){
        static random_device rd;
        return (((size_t) rd())<<32) | ((size_t) rd());
    }
    
    size_t operator()(const T key) const {
        static const auto hsh = hash<T>();
        static const size_t fr = size_t_random();
        size_t x = hsh(key);
        x ^= fr;
        x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
        x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
        x = x ^ (x >> 31);
        return x;
    }
};

//----------------------trie----------------------// 20
struct trie{
    const int data;
    trie* nexts[10];
    trie(int d) : data(d) {
        for (int i=0;i<10;i++) nexts[i]= nullptr;
    }
    void insert(const int* arr,int m){
        auto curr = this;
        for (int i=0;i<m;i++){
            if (curr->nexts[arr[i]] == nullptr){
                curr->nexts[arr[i]] = new trie(arr[i]);
            }
            curr = curr->nexts[arr[i]];
        }
    }
    ~trie() {
        for (int i=0;i<10;i++) if(nexts[i]) delete nexts[i];
    }
};


//----------------------segTree----------------------// 46
template <typename T, void cmb(T&, const T&, const T&),
          decltype(cmb) upd=cmb, decltype(cmb) cmbq=cmb>
struct segTree{
    unique_ptr<T[]> tree;
    T ans;
    int b,n;
    template<class Iterator>
    segTree(Iterator first, int size){
        n = size;
        b = 1;
        while (b<n) b *=2; 
        tree = unique_ptr<T[]>(new T[2*n-1]-1);
        for(int i=0;i<n;i++) tree[n+(i+b)%n] = *(first++);
        for(int i=n-1;i>0;i--) 
            cmb(tree[i],tree[2*i],tree[2*i+1]);
    }
    T& get(int i){
        return tree[n + (i+b)%n];
    }
    void update(int x){
        x = n + (x+b)%n;
        while (x>1) {
            x /= 2;
            upd(tree[x],tree[2*x],tree[2*x+1]);
        }    
    }
    void query(int l, int r){
        l = n + (l+b)%n;
        r = n + (r+b)%n;
        T ql=ans,qr=ans;
        if (l > r){
            if (l%2==1) cmbq(ql,ql,tree[l++]);
            l /= 2;
        }
        while (l <= r){
            if (l%2==1) cmbq(ql,ql,tree[l++]);
            if (r%2==0) cmbq(qr,tree[r--],qr);
            l /= 2;
            r /= 2;
        }
        cmbq(ans,ql,qr);
    }
    ~segTree(){if (T* w=tree.release()) delete[] (w+1);}
    segTree(segTree&& o)noexcept =default;
    segTree& operator=(segTree&& o)noexcept =default;
};
// root node not checked & l and r global vars; x=1,bs=b/2 (init)
// void _query(int x, int lx,int rx,int bs){
//     if (x<n) {
//         int m = min(lx+bs-1,rx-bs/2);
//         trace(lx,m,rx,bs);
//         if (l<=m && thing) _query(2*x,lx,m,bs/2); 
//         if (r>m && thing) _query(2*x+1,m+1,rx,bs/2);
//         upd(tree[x],tree[2*x],tree[2*x+1]);
//     }
//     else{
//         stuff;
//     }
// }
