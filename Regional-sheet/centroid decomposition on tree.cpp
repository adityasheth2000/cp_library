int nodes = 0;
int subtree[N], parentcentroid[N];
set<int> g[N];


void dfs(int u, int par){
	nodes++;
	subtree[u] = 1;
	for(auto &it:g[u]){
		if(it == par)
			continue;
		dfs(it, u);
		subtree[u] += subtree[it];
	}
}

int centroid(int k, int parent){
	for(auto it:g[k]){
		if(it==parent)
			continue;
		if(subtree[it]>(nodes>>1))
			return centroid(it,k);
	}
	return k;
}

void decompose(int u, int par){
	nodes = 0;
	dfs(u, u);
	int node = centroid(u, u);
	//do something
	parentcentroid[node] = par;
	for(auto &it:g[node]){
		g[it].erase(node);
		decompose(it, node);
	}
}


/*
Properties of Centroid Tree(VERY IMP): https://www.quora.com/q/threadsiiithyderabad/Centroid-Decomposition-of-a-Tree 
*/