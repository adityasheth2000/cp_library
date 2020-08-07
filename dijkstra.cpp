int dijkstra(int source,int destination)
{
	int n=adj.size();
	int var[n];
	int fix[n];
	for(int i=0;i<n;i++)
	{
		var[i]=inf;
	}
	memset(fix,-1,sizeof(fix));
	set<pair<int,int>> s;
	s.insert({0,source});
	fix[source]=0;
	var[source]=0;
	while(s.size())
	{
		pair<int,int> cur=*(s.begin());
		s.erase(cur);
		fix[cur.second]=cur.first;
		for(auto x: adj[cur.second])
		{
			if(var[x.first]>cur.first+x.second)
			{
				s.erase({var[x.first],x.first});
				var[x.first]=cur.first+x.second;
				s.insert({var[x.first],x.first});
			}
		}
	}
	return fix[destination];
}