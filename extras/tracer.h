//--------------------debug only---------------------//
// #include <bits/stdc++.h>
// using namespace std;
//--------------------debug only---------------------//
#undef endl
#define io_fast ;
#define trace(vars...) ;errprintall(__LINE__, #vars,vars);
#define traceN(_n,expr);{ cerr<<":"<<__LINE__<<" | "<<#expr<<" = [";\
int j=0;for(;j<(_n)-1;j++){cerr<<expr<<", ";cerr.flush();}if ((_n)!=0)cerr<<expr;cerr<<']'<<endl;}

#define delim ;cerr <<"---------------- "<<j+1<<" ---------------- "<<j+1<<" ----------------"<<endl;
#define end ; cerr << "---------------- R -------------------------------- R ----------------" << endl; 
template<typename T>
ostream& operator << (ostream& in,const vector<T>& v){
    in << '[';
    for (int i=0; i+1 < v.size();i++) {
        in << v[i] << ", ";
        in.flush();
    }
    if (v.size()) in << v.back();
    in << ']';
    in.flush();
    return in;
}

template<typename T>
ostream& operator << (ostream& in,const set<T>& s){
    in << '{';
    for(auto it = s.begin();it!=s.end();){
        in << *(it++);
        if (it!=s.end()) in << ", ";
    }
    in << '}';
    return in;
}
template<typename T>
ostream& operator << (ostream& in,const multiset<T>& s){
    in << '{';
    for(auto it = s.begin();it!=s.end();){
        in << *(it++);
        if (it!=s.end()) in << ", ";
    }
    in << '}';
    return in;
}
template<typename T, typename H>
ostream& operator << (ostream& in,const unordered_set<T,H>& s){
    in << '{';
    for(auto it = s.begin();it!=s.end();){
        in << *(it++);
        if (it!=s.end()) in << ", ";
    }
    in << '}';
    return in;
}
template<typename T, typename H>
ostream& operator << (ostream& in,const unordered_multiset<T,H>& s){
    in << '{';
    for(auto it = s.begin();it!=s.end();){
        in << *(it++);
        if (it!=s.end()) in << ", ";
    }
    in << '}';
    return in;
}
template<typename K,typename V>
ostream& operator << (ostream& in,const map<K,V>& s){
    in << '{';
    auto it = s.begin();
    for(;next(it)!=s.end(); it++){
        in << it->first << ':' << it->second << ", ";
    }
    in << it->first << ':' << it->second << '}';
    return in;
}

template<typename K,typename V,typename H>
ostream& operator << (ostream& in,const unordered_map<K,V,H>& s){
    in << '{';
    auto it = s.begin();
    for(;next(it)!=s.end(); it++){
        in << it->first << ':' << it->second << ", ";
    }
    in << it->first << ':' << it->second << '}';
    return in;
}

template<typename T,typename R>
ostream& operator << (ostream& in,const pair<T,R>& s){
    in << '(' << s.first <<',' << s.second << ')'; 
    return in;
}
template<typename T,size_t... I>
void __print_tup(const T& t,std::index_sequence<I...>){
    (..., (cerr << (I == 0? "" : ", ") << get<I>(t)));
}
template<typename ...T>
ostream& operator << (ostream& in,const tuple<T...>& t){
    in << '(';
    __print_tup(t,make_index_sequence<sizeof...(T)>());
    return in << ')';
}

struct StrSplit{
    const char* s;
    StrSplit(const char* const f) {s = f;}
    const string next(){
        const char* start = s;
        int n = 0;
        while (*s && *(s++) != ','){n++;}
        return string(start,n);
    }
};
template <typename T>
void errprint(const string&& name, T& var ){
    cerr << " | " <<name << " = " << var;
    cerr.flush();
}
template <typename... T>
void errprintall(int lno,const char* s, const T&... vars){
    cerr <<":"<<lno;
    auto names = StrSplit(s);
    (...,errprint(move(names.next()),vars));
    cerr << endl;
}
// int main(){
//     int a,b,c;
//     int x[5] = {0};
//     set<int> f = {5,10};
//     traceI(f,e);
//     traceN(5,x);
//     trace(a,b,c);
// }
