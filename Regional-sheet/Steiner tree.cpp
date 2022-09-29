/*
n=number of steiner node(the optional intermediate nodes)
k=number of terminal nodes.(all nodes that has to be connected)
dp[i][mask]=minimum cost that the root is i and contains all terminal nodes which are set in mask.
g[i][j]=minimum cost from steiner node i to steiner node j. Run floyd warshall initially for finding g[][]
*/

for(int i=0;i<n;i++){
	for(int j=0;j<k;j++){
		dp[i][(1<<j)]= ;// distance from steiner node i to terminal node j, base case for dp.
	}	
	dp[i][0]=0;
}
for(int mask=1;mask<(1<<k);mask++){
	for(int i=0;i<n;i++){
		for(int ss=mask;ss>0;ss=(ss-1)&mask){
			dp[i][mask]=min(dp[i][mask],dp[i][ss]+dp[i][mask-ss]);
		}
		if(dp[i][mask]<inf){
			for(int j=0;j<n;j++){
				dp[j][mask]=min(dp[j][mask],dp[i][mask]+g[i][j]);
			}
		}
	}
} 	