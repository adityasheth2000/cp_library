#include<bits/stdc++.h>
typedef long long ll;
#define M 1000000007
#define endl "\n"
#define int long long 
using namespace std;

int n;
vector<vector<int>> adj;


void dfs1(int source,int prev,int distance,int dis1[])
{
	dis1[source]=distance;
	for(auto x: adj[source])
	{
		if(x!=prev)
		dfs1(x,source,distance+1,dis1);
	}	
}

void dfs2(int source,int prev,int distance,int dis1[],int parent[],int p)
{
	
	dis1[source]=distance;
	parent[source]=p;
	for(auto x: adj[source])
	{
		if(x!=prev)
		dfs2(x,source,distance+1,dis1,parent,source);
	}
}
int get_centre() // returns the node number of centre of tree.
{
	int dis1[n+1];   	
   	memset(dis1,-1,sizeof(dis1));
   	dfs1(1,-1,0,dis1);
    int node1,ma=-1;
    for(int i=1;i<=n;i++)
    {
    	//printf("%d ",dis1[i]);
    	if(dis1[i]>ma)
    	{
    		ma=dis1[i];
    		node1=i;
    	}
    }
    int parent[n+1];
    memset(parent,-1,sizeof(parent));
    dfs2(node1,-1,0,dis1,parent,-1);    
    ma=-1;
    int node2;
    for(int i=1;i<=n;i++)
    {
    	//printf("%d ",dis1[i]);
    	if(dis1[i]>ma)
		{	
			ma=dis1[i];
			node2=i;
		}
    }
    vector<int> path;
    int start=node2;
    cout<<endl;
    while(start!=-1)
    {
    	cout<<start<<" ";
    	path.push_back(start);
    	start=parent[start];
    }

   	if(path.size()%2==1)
   	{
   		return path[path.size()/2];
   	}
   	return -1;
}


int32_t main()
{
    ios::sync_with_stdio(0);cin.tie(0);
   
    cin>>n;
    adj.resize(n+1);
    for(int i=1;i<n;i++)
    {
    	int u,v;
    	cin>>u>>v;
    	adj[u].push_back(v);
    	adj[v].push_back(u);
    }
    int centre=get_centre();
    cout<<endl<<"centre="<<centre<<endl;

}

