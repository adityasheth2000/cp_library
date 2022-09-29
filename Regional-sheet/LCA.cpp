const int N=1e5+100;
int n;
vector<int> adj[N];
const int LOGMAX=20;
int T[N];// T[i] returns father of node i
int P[N][LOGMAX]; // P[i][j]= 2^jth ancestor of i
int L[N]; // L[i]=level of node i

void dfs_lca(int node,int par,int level){
	L[node]=level;
	T[node]=par;
	for(auto x: adj[node]){
		if(x!=par){
			dfs_lca(x,node,level+1);
		}
	}
}
void preprocess(){
	dfs_lca(1,0,0);
	for(int i=0;i<=n;i++)
		for(int j=0;j<LOGMAX;j++)
			P[i][j]=-1;
	for(int i=1;i<=n;i++){
		P[i][0]=T[i];
	}
	for(int log=1;log<LOGMAX;log++){
		for(int i=1;i<=n;i++){
			if(P[i][log-1]!=-1){
				P[i][log]=P[P[i][log-1]][log-1];
			}
		}
	}
}	
int LCA(int p,int q){
	//make sure level of p>= level of q
	if(L[q]>L[p])
		swap(p, q);
	int loglp;
	for(loglp=1; 1<<loglp <=L[p] ; loglp++)
	{}
	loglp--;

	// make p=(the ancestor of p which is at same level as that of q)
	for(int log=loglp;log>=0;log--)
	{
		if(L[p]-(1<<log)>=L[q])
		{
			p=P[p][log];
		}
	}
	// now p and q are at same level.
	if(p==q)
		return p; 
	for(int i=loglp;i>=0;i--){
		if(P[p][i]!=-1 && P[p][i]!=P[q][i]){
			p=P[p][i];
			q=P[q][i];
		}
	}
	return T[p];
}
