#ifdef LOCAL
#include "./extras/.stdc++.h"
#include "./extras/.tracer.h"
#else
#include <bits/stdc++.h>
#define io_fast ios_base::sync_with_stdio(false);cin.tie(nullptr)
#define trace(...) 
#define traceN(...) 
#define err(...) 
#define errln(...) 
#define local if (false)
#define delim 
#define endd 
#define endl '\n'
#endif
using ll=long long;
using namespace std;

template<typename... T> void read(T&... vars) {(cin >>...>> vars);}
#define input(vars...) vars; read(vars)
#define rep(v,_n) for (int v=0;v<_n;v++)   
#define COM ,
 
template<typename... T> void print(const T&... vars) {(...,(cout << vars << ' '));}
template<typename... T> void println(const T&... vars) {print(vars...);cout << endl;}

int test(){
    return 0;
}

int main(){
    io_fast;
    int input(_t);
    rep(j,_t) {delim;println(test());};
    endd;
} 
