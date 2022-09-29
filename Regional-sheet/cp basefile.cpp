#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template <typename T>
std::ostream & operator << (std::ostream & os, const std::vector<T> & vec);
template <typename T>
std::ostream & operator << (std::ostream & os, const std::set<T> & vec);
template <typename T>
std::ostream & operator << (std::ostream & os, const std::unordered_set<T> & vec);
template <typename T>
std::ostream & operator << (std::ostream & os, const std::multiset<T> & vec);
template <typename T>
std::ostream & operator << (std::ostream & os, const std::unordered_multiset<T> & vec);
template<typename T1, typename T2>
std::ostream & operator << (std::ostream & os, const std::pair<T1,T2> & p);
template<typename T1, typename T2>
std::ostream & operator << (std::ostream & os, const std::map<T1,T2> & p);
template<typename T1, typename T2>
std::ostream & operator << (std::ostream & os, const std::unordered_map<T1,T2> & p);
template <typename T>
std::ostream & operator << (std::ostream & os, const std::vector<T> & vec){
    os<<"{";
    for(auto elem : vec)
        os<<elem<<",";
    os<<"}";
    return os;
}
template <typename T>
std::ostream & operator << (std::ostream & os, const std::set<T> & vec){
    os<<"{";
    for(auto elem : vec)
        os<<elem<<",";
    os<<"}";
    return os;
}
template <typename T>
std::ostream & operator << (std::ostream & os, const std::unordered_set<T> & vec){
    os<<"{";
    for(auto elem : vec)
        os<<elem<<",";
    os<<"}";
    return os;
}
template <typename T>
std::ostream & operator << (std::ostream & os, const std::multiset<T> & vec){
    os<<"{";
    for(auto elem : vec)
        os<<elem<<",";
    os<<"}";
    return os;
}
template <typename T>
std::ostream & operator << (std::ostream & os, const std::unordered_multiset<T> & vec){
    os<<"{";
    for(auto elem : vec)
        os<<elem<<",";
    os<<"}";
    return os;
}
template<typename T1, typename T2>
std::ostream & operator << (std::ostream & os, const std::pair<T1,T2> & p){
    os<<"{"<<p.first<<","<<p.second<<"}";
    return os;
}
template<typename T1, typename T2>
std::ostream & operator << (std::ostream & os, const std::map<T1,T2> & p){
    os<<"{";
    for(auto x: p)
        os<<x.first<<"->"<<x.second<<", ";
    os<<"}";
    return os;
}
template<typename T1, typename T2>
std::ostream & operator << (std::ostream & os, const std::unordered_map<T1,T2> & p){
    os<<"{";
    for(auto x: p)
        os<<x.first<<"->"<<x.second<<", ";
    os<<"}";
    return os;
}
/*--------*/
#warning TODOt1-5
#define t6(a,b,c,d,e,f)   cerr<<#a<<"="<<a<<" "<<#b<<"="<<b<<" "<<#c<<"="<<c<<" "<<#d<<"="<<d<<" "<<#e<<"="<<e<<" "<<#f<<"="<<f<<endl
#define GET_MACRO(_1,_2,_3,_4,_5,_6,NAME,...) NAME
#ifndef ONLINE_JUDGE
#define tr(...) GET_MACRO(__VA_ARGS__,t6,t5, t4, t3, t2, t1)(__VA_ARGS__)
#else 
#define tr(...)
#endif
/*-------*/
#define __ freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#define fastio() ios::sync_with_stdio(0);cin.tie(0)
#define MEMS(x,t) memset(x,t,sizeof(x));
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
/*-------------------------------------------------------------------------------------------------------------------------------------*/
// #define MOD 1000000007
// #define MOD 998244353
#define endl "\n"
#define int long long
#define inf 1e18
#define ld long double
/*-------------------------------------------------------------------------------------------------------------------------------------*/

signed main()
{
    fastio();
    
}