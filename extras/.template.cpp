#include "bits/stdc++.h"
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
#define end ;
#endif


template<typename T> inline void read(T &var){ cin >> var;}
template<typename T, typename... R> inline void read(T &var, R &...rest){ cin >> var; read(rest...);}
#define input(vars...) vars; read(vars)
#define repeatN(_n, oper...); for(int j=0;j<_n;j++) {oper;}  
#define COM ,

template<typename T> inline void print(const T var){ cout<<var<<' ';}
template<typename T,typename... R> inline void print(const T var, const R ...rest){cout<<var<<' '; print(rest...);}
template<typename T> inline void println(const T var){ cout<<var<<endl;}
template<typename T,typename... R> inline void println(const T var, const R ...rest){cout<<var<<' '; println(rest...);}
#define printN(_n,expr...) for(int j=0;j<_n;j++){print(expr);}cout <<endl;

int test(){
    return 0;
}

int main(){
    io_fast;
    int input(t);
    repeatN(t,delim;println(test()));
    end
} 
