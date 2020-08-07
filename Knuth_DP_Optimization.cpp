/*Applicable when the dp problem takes the following form:
 * dp[i][j]=min(dp[i][k]+dp[k+1][j])+Cost[i][j]; for every k in [i,j].
 * Now the conditions required to apply Knuth optimizations are as follows:
 * 1) Quadrangle inequality: Cost[a][c]+cost[b][d]<=cost[a][d]+cost[b][c] for a<=b<=c<=d;
 * 2) Monotonicity: cost[b][c]<=cost[a][d]; for a<=b<=c<=d;
 * 
 * Let K=k[i][j] be the point at which dp[i][j]= min(dp[i][K]+dp[i][K+1]+Cost[i][j]) is satisfied, 
 * then according to knuth's optimization, k[i][j] lies in the range: [ k[i][j-1], k[i+1][j] ].
 * 
 * So using this idea, knuth's optimization helps calculation of dp[i][j] over all i,j in O(n^2) instead of bruteforce dp O(n^3).
 * */


for(int i=1;i<=n;i++)
{
	dp[i][i]=;//initialize this.
	k[i][i]=i;
}
for(int len=2;len<=n;len++)
{
    for(int l=1;l+len-1<=n;l++)
    {
        int r=l+len-1;
        int kleft=k[l][r-1];
        int kright=k[l+1][r];
        dp[l][r]=1e18;
        k[l][r]=l;
		for(int kf=kleft;kf<=kright;kf++)
		{
			if(dp[l][r]>dp[l][kf]+dp[kf+1][r]+cum[r]-cum[l-1])
			{
				dp[l][r]=dp[l][kf]+dp[kf+1][r]+Cost(l,r);// change Cost(l,r) according to the question. 
				k[l][r]=kf;
			}
		}
  	}
}