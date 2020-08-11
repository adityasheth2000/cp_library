/*
The problem: Given a tree with n nodes, and an order -order[1...n](all values are distinct), construct a new tree from original tree,
with the following brute idea:
1) The root must be the the node with lowest order[node].
2) Recursively solve for the subtrees which are formed on removing this root. 
Then add edge from this root to the roots of smaller subtrees.

Time complexity to construct new tree: O(n*log(n))
Problem:    https://www.codechef.com/AUG20A/problems/CHEFCOMP
Solution:   https://www.codechef.com/viewsolution/36547239
*/


struct dat
{
	//Use required attributes
	pair<int,int> mn;
	//Default Values
	dat() : mn(make_pair(inf,inf)) {};
};

struct SegTree
{
	int N;
	vector<dat> st;
	vector<bool> cLazy;
	vector<pair<int,int>> lazy;

	void init(int n)
	{
		N = n;
		st.clear();
		st.resize(4 * N + 5);
		cLazy.assign(4 * N + 5, false);
		lazy.assign(4 * N + 5, make_pair(inf,inf));
	}

	//Write reqd merge functions
	void merge(dat &cur, dat &l, dat &r) 
	{
		cur.mn = min(l.mn, r.mn);
	}
	
	//	Handle lazy propagation appriopriately
	// 	think what should happen if clazy[2*node] is already 1 before propagate is called
	void propagate(int node, int L, int R)
	{
		if(L != R)
		{
			cLazy[node*2] = 1;
			cLazy[node*2 + 1] = 1;
			lazy[node*2] = lazy[node];
			lazy[node*2 + 1] = lazy[node]; 
		}
		st[node].mn = lazy[node];
		cLazy[node] = 0;
	}

	
	dat Query(int node, int L, int R, int i, int j)
	{
		if(cLazy[node])
			propagate(node, L, R);
		if(j<L || i>R)
			return dat();
		if(i<=L && R<=j)
			return st[node];
		int M = (L + R)/2;
		dat left=Query(node*2, L, M, i, j);
		dat right=Query(node*2 + 1, M + 1, R, i, j);
		dat cur;
		merge(cur, left, right);
		return cur;
	}

	dat pQuery(int node, int L, int R, int pos)
	{
		if(cLazy[node])
			propagate(node, L, R);
		if(L == R)
			return st[node];
		int M = (L + R)/2;
		if(pos <= M)
			return pQuery(node*2, L, M, pos);
		else
			return pQuery(node*2 + 1, M + 1, R, pos);
	}	

	void Update(int node, int L, int R, int i, int j, pair<int,int> val)
	{
		if(cLazy[node])
			propagate(node, L, R);
		if(j<L || i>R)
			return;
		if(i<=L && R<=j)
		{
			cLazy[node] = 1;
			lazy[node] = val;
			propagate(node, L, R);
			return;
		}
		int M = (L + R)/2;
		Update(node*2, L, M, i, j, val);
		Update(node*2 + 1, M + 1, R, i, j, val);
		merge(st[node], st[node*2], st[node*2 + 1]);
	}

	void pUpdate(int node, int L, int R, int pos, pair<int,int> val)
	{
		if(cLazy[node])
			propagate(node, L, R);
		if(L == R)
		{
			st[node].mn=val;
			return;
		}
		int M = (L + R)/2;
		if(pos <= M)
			pUpdate(node*2, L, M, pos, val);
		else
			pUpdate(node*2 + 1, M + 1, R, pos, val);
		dat tleft=Query(2*node,L,M,L,M);
		dat tright=Query(2*node+1,M+1,R,M+1,R);
		merge(st[node],tleft,tright);
	}

	dat query(int pos)
	{
		return pQuery(1, 1, N, pos);
	}

	dat query(int l, int r)
	{
		return Query(1, 1, N, l, r);
	}

	void update(int pos, pair<int,int> val)
	{
		pUpdate(1, 1, N, pos, val);
	}

	void update(int l, int r, pair<int,int> val)
	{
		Update(1, 1, N, l, r, val);
	}
};

int n;
vector<int> tim;
int curtime;
vector<int> par;
vector<vector<int>> sz;
SegTree st;
int dfs_filltim(int node,int parent,vector<vector<int>> &adj)
{
	tim[node]=curtime++;
	par[node]=parent;
	int sum=1;
	for(auto x: adj[node])
	{
		if(x!=parent)
		{
			int tmp=dfs_filltim(x,node,adj);
			sum+=tmp;
			sz[node].push_back(tmp);
		}
	}
	return sum;
}

int get_best_in_range(int l,int r,vector<vector<int>> &g,vector<vector<int>>&adj)
{
	pair<int,int> best=st.query(l,r).mn;
	if(best.first>1e7)return -1;	
	int node=best.second;
	int done=1;
	int c=0;
	for(auto x: adj[node])
	{
		if(x==par[node])continue;
		int nw=get_best_in_range(tim[node]+done,tim[node]+done+sz[node][c]-1,g,adj);
		if(nw>0)g[node].push_back(nw);
		done+=sz[node][c];
		c++;
	}
	st.update(tim[node],tim[node]+done-1,make_pair(inf,inf));
	int nw=get_best_in_range(l,r,g,adj);
	if(nw>0)g[node].push_back(nw);
	return node;
}

vector<vector<int>> reconstruct_directed_tree(vector<vector<int>> adj,vector<int> order)
{
	assert(adj.size()==order.size());
	vector<vector<int>> g(n+1);		
	{
		tim.clear();tim.resize(n+1);
		curtime=1;
		par.clear();par.resize(n+1,-1);
		sz.clear();sz.resize(n+1);
	}		
	dfs_filltim(1,-1,adj);
	st.init(n+1);
	for(int i=1;i<=n;i++)
	{
		st.update(tim[i],{order[i],i});
	}
	int root=get_best_in_range(1,n,g,adj);
	return g;
}
