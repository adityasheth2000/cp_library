/* For Directed Graph:*/
vector<int> ptr;//remembers the currenct ptr to each node adjacency list
vector<vector<int>> adj;
vector<int> tour;//the tour is stored in reverse order. Don't forget to reverse it after completing dfs.
void dfs(int node)
{
	while(ptr[node]<adj[node].size())
	{
		int nxt=adj[node][ptr[node]++];
		dfs(nxt);
	}
	tour.push_back(node);
}

/* For Undirected Graph: */
vector<int> ptr;
vector<vector<pair<int,int>>> adj; //adj[u].push_back({v,edge_no});adj[v].push_back({u,edge_no});
vector<int> tour;
vector<bool> mark;// remembers whether we have visited the undirected or not.

void dfs(int node)
{
	while(ptr[node]<adj[node].size())
	{
		auto nxt=adj[node][ptr[node]++];
		if(mark[nxt.second])continue;
		mark[nxt.second]=1;
		dfs(nxt.first);
	}
	tour.push_back(node);
}
