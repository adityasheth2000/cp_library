vector<int> dijkstra(int source,int destination)
{
	int n=adj.size();
	vector<int> var(n, inf);
	vector<int> fix(n);
	set<pair<int,int>> s;
	s.insert({0,source});
	fix[source]=0;
	var[source]=0;
	while(s.size()){
		pair<int,int> cur=*(s.begin());
		s.erase(cur);
		fix[cur.second]=cur.first;
		for(auto x: adj[cur.second]){
			if(var[x.first]>cur.first+x.second){
				s.erase({var[x.first],x.first});
				var[x.first]=cur.first+x.second;
				s.insert({var[x.first],x.first});
			}
		}
	}
	return fix;
}