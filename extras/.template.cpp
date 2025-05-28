#include "bits/stdc++.h"
using namespace std;

using ll=long long;
// #define endl '\n'; cout.flush()
#define endl '\n'
#ifdef LOCAL
#include "./extras/tracer.h"
#else
#define io_fast ios_base::sync_with_stdio(false);cin.tie(nullptr)
#define trace(...) ;
#define traceN(...) ;
#define delim ;
#define endd ;
#endif

template<typename... T> void read(T&... vars){ (...,(cin >> vars));}
#define input(vars...) vars; read(vars)
#define repeatN(_n, oper...); for(int j=0;j<_n;j++) {oper;}  
#define COM ,

template<typename... T> void print(const T&... vars){(...,(cout << vars << ' '));}
template<typename... T> void println(const T&... vars){(print(vars...));cout << endl;}
#define printN(_n,expr...) for(int j=0;j<_n;j++){print(expr);}cout <<endl;


int test(){
    return 0;
}

int main(){
    io_fast;
    int input(t);
    repeatN(t,delim;println(test()));
    endd;
} 
