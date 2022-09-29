/*
   In DFS tree, a vertex u is articulation point if one of the following two conditions is true.
1) u is root of DFS tree and it has at least two children.
2) u is not root of DFS tree and it has a child v such that no vertex in subtree rooted with 
   v has a back edge to one of the ancestors (in DFS tree) of u.
*/
const int N=2e5;
vector<int> adj[N];


bool is_AP[N];
int tim_AP=0;
bool vis_AP[N];
int disc_AP[N];
int low_AP[N];
void dfs_AP(int node,int par) // call dfs_AP(1,-1)
{	
	vis_AP[node]=true;
	disc_AP[node]=++tim_AP;
	low_AP[node]=disc_AP[node];
	int child=0;
	for(auto x: adj[node]){
		if(!vis_AP[x]){
			dfs_AP(x,node);
			child++;
			low_AP[node]=min(low_AP[node],low_AP[x]);
			if(par==-1 && child>1)
				is_AP[node]=true;
			if(par!=-1 && low_AP[x]>=disc_AP[node])
				is_AP[node]=true;
		}
		else if(x!=par){
			low_AP[node]=min(low_AP[node],disc_AP[x]);
		}		
	}
}