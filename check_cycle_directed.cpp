#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const double PI=acos(-1.0);
#define t1(x)             cerr<<#x<<"="<<x<<endl
#define t2(x, y)          cerr<<#x<<"="<<x<<" "<<#y<<"="<<y<<endl
#define t3(x, y, z)       cerr<<#x<<"=" <<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define t4(a,b,c,d)       cerr<<#a<<"="<<a<<" "<<#b<<"="<<b<<" "<<#c<<"="<<c<<" "<<#d<<"="<<d<<endl
#define t5(a,b,c,d,e)     cerr<<#a<<"="<<a<<" "<<#b<<"="<<b<<" "<<#c<<"="<<c<<" "<<#d<<"="<<d<<" "<<#e<<"="<<e<<endl
#define t6(a,b,c,d,e,f)   cerr<<#a<<"="<<a<<" "<<#b<<"="<<b<<" "<<#c<<"="<<c<<" "<<#d<<"="<<d<<" "<<#e<<"="<<e<<" "<<#f<<"="<<f<<endl
#define GET_MACRO(_1,_2,_3,_4,_5,_6,NAME,...) NAME
#define t(...) GET_MACRO(__VA_ARGS__,t6,t5, t4, t3, t2, t1)(__VA_ARGS__)
//freopen("output.txt","w",stdout);
//freopen("input.txt","r",stdin);
/*-------------------------------------------------------------------------------------------------------------------------------------*/
#define mod 1000000007
#define endl "\n" 
#define int long long // remove when constraints are tight.
/*-------------------------------------------------------------------------------------------------------------------------------------*/
const int N=5e3+5;
int n;
vector<int> adj[N];


int col[N];
bool is_cycle=0;
void dfs_cycle_check(int node)
{
	if(col[node]==1)
	{
		is_cycle=1;
		return;
	}
	else if(col[node]==2)
	{
		return;
	}
	col[node]=1;
	for(int x: adj[node])
	{
		dfs_cycle_check(x);
	}
	col[node]=2;
	return;
}
bool check_cycle()
{	
	for(int i=1;i<=n;i++)
	{
		if(col[i]==0)
		{
			dfs_cycle_check(i);
		}
	}
	return is_cycle;
}
int32_t main()
{
	ios::sync_with_stdio(0);cin.tie(0);
	int n,m;
	cin>>n>>m;
	
}
