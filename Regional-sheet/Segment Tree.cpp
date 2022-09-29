
struct dat
{
	int mn;
	dat() : mn(1e9) {};
};

struct SegTree
{
	int N;
	vector<dat> st;
	vector<bool> cLazy;
	vector<int> lazy;

	void init(int n){
		N = n;
		st=vector<dat>(4 * N + 5);
		cLazy=vector<bool>(4 * N + 5, false);
		lazy=vector<int>(4 * N + 5, 0);
	}

	//Write reqd merge functions
	void merge(dat &cur, dat &l, dat &r) {
		cur.mn = min(l.mn, r.mn);
	}
	
	//	Handle lazy propagation appriopriately
	// 	think what should happen if clazy[2*node] is already 1 before propagate is called
	void propagate(int node, int L, int R){
		if(L != R){
			cLazy[node*2] = 1;
			cLazy[node*2 + 1] = 1;
			lazy[node*2] = lazy[node];
			lazy[node*2 + 1] = lazy[node]; 
		}
		st[node].mn = lazy[node];
		cLazy[node] = 0;
	}

	dat Query(int node, int L, int R, int i, int j){
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

	dat pQuery(int node, int L, int R, int pos){
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

	void Update(int node, int L, int R, int i, int j, int val){
		if(cLazy[node])
			propagate(node, L, R);
		if(j<L || i>R)
			return;
		if(i<=L && R<=j){
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

	void pUpdate(int node, int L, int R, int pos, int val){
		if(cLazy[node])
			propagate(node, L, R);
		if(L == R){
			change_here
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

	dat query(int pos){
		return pQuery(1, 1, N, pos);
	}

	dat query(int l, int r){
		return Query(1, 1, N, l, r);
	}

	void update(int pos, int val){
		pUpdate(1, 1, N, pos, val);
	}

	void update(int l, int r, int val){
		Update(1, 1, N, l, r, val);
	}
};
