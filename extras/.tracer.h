//--------------------debug only---------------------//
using namespace std;
//--------------------debug only---------------------//
#undef endl
#define io_fast 
#define trace(vars...) ;errtraceall(__LINE__, #vars,vars);
#define traceN(_n,expr);{ cerr<<__LINE__<<":"<<" | "<<#expr<<" = [";\
for(int j=0;j<_n;j++){ cerr << ((j==0) ? "" : ", "); errprint(expr);}cerr<<']'<<endl;}

#define delim ; cerr <<"---------------- "<<j+1<<" ---------------- "<<j+1<<" ----------------"<< endl;
#define endd ; cerr << "---------------- R -------------------------------- R ----------------" << endl; 
#define local if (true)
template<typename... T> void err(const T&... vars) {(...,(cerr << vars << ' '));}
template<typename... T> void errln(const T&... vars) {err(vars...);cout << endl;}

// Dynamic strings `char s[n]` must be traced like trace(&s[0])
// because char[n] cannot be passed as a template parameter. 

template<typename T>
concept stringLike = is_convertible_v<T,string_view>;

template<typename T>
concept arrayLike = (is_bounded_array_v<T> ||
    ( ranges::range<T> && 
    requires (T v, typename T::size_type i){
        { v[i] } -> same_as<typename T::reference>;
    })) && !stringLike<T>;

template<typename T>
concept Streamable = !arrayLike<T> && !stringLike<T> && !is_same_v<T,bool> && 
        requires(ostream& os, T value) {
        { os << value } -> same_as<ostream&>;
};

template<typename T>
concept setLike = 
    ranges::range<T> && 
    requires {
    typename T::key_type;
    typename T::value_type;
};

template<typename T>
concept iterOpaque = 
    (!(setLike<T> || arrayLike<T> || stringLike<T>)) &&
    ranges::range<T>;

template <stringLike S>
void errprint(const S& var);
void errprint(const bool& var);
template <Streamable T>
void errprint(const T& var);
template<typename ...T>
void errprint (const tuple<T...>& t);
template<typename... Ts>
void errprint(const variant<Ts...>& v);
template<typename T>
void errprint(const std::optional<T>& opt);
template<typename T1, typename T2>
void errprint(const pair<T1,T2>& p);
template <setLike S>
void errprint(const S& var);
template<arrayLike V>
void errprint(const V& var);
template<iterOpaque O>
void errprint(const O& var);

template <ranges::range R>
void _printrange(const R& r){
    bool start = true;
    for (auto& v : r){
        if (!start) cerr << ", ";
        start = false;
        errprint(v);
    }
}

template<typename T,size_t... I>
void _print_tup(const T& t, index_sequence<I...>){
    (...,(cerr<<(I == 0? "" : ", "),errprint(get<I>(t))));
}

template<typename ...T>
void errprint (const tuple<T...>& t){
    cerr << '(';
    _print_tup(t,make_index_sequence<sizeof...(T)>());
    cerr << ')';
}

template<typename T>
void errprint(const optional<T>& v) {
    if (v) {cerr << '?' ;errprint(*v);}
    else cerr << "?-";
}

template<typename... Ts>
void errprint(const variant<Ts...>& v) {
    size_t index = v.index();
    cerr  << '!' << index << '~';
    std::visit([](auto& val){ errprint(val); }, v);
}

template<typename T1, typename T2>
void errprint(const pair<T1,T2>& p){
    cerr <<'(';
    errprint(p.first);
    cerr <<": ";
    errprint(p.second);
    cerr <<')';
}

template <stringLike S>
void errprint(const S& var){
    cerr << "\"" << var << "\"";
}

void errprint(const bool& var){
    cerr << (var? 'T' : 'F'); 
}

template <Streamable T>
void errprint(const T& var){
    cerr << var;
}

template<setLike S>
void errprint(const S& s){
    cerr << '{';
    _printrange(s);
    cerr << '}';
}

template<arrayLike V>
void errprint(const V& s){
    cerr << '[';
    _printrange(s);
    cerr << ']';
}

template<iterOpaque O>
void errprint(const O& s){
    cerr << '`';
    _printrange(s);
    cerr << '`';
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

template <typename... T>
void errtraceall(int lno,const char* s, const T&... vars){
    cerr <<lno<<":";
    auto names = StrSplit(s);
    (...,(cerr<<" | "<<names.next()<<" = ",errprint(vars)));
    cerr << endl;
}
