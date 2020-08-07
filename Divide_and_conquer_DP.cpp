/*The recurrence relation of following type:
dp(i,j)=min{dp(i−1,k)+C(k,j)} -> where k<=j 

The above recurrence relation can be solved using divide and conquer optimization of Dp.

Let opt(i,j) be the value of k that minimizes the above expression. 
If opt(i,j)≤opt(i,j+1) for all i,j, then we can apply divide-and-conquer DP. 
This known as the monotonicity condition. 
The optimal "splitting point" for a fixed i increases as j increases.
Reference:
https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html
*/
// Pseudo code:
/*
Original time complexity: O(n*n*k)
Reduced time complexity : O(n*k*log(n))
*/
const int N=
int dp[N][N];
int C(int i,int j);//Implementation differs every time.

void rec(int i,int l,int r,int optl,int optr)
{
    if(l>r)
    {
        return;
    }
    int mid=(l+r)>>1;
    int &ans=dp[i][mid];
    pair<int,int> best={inf,-1};
    for(int j=optl;j<=min(optr,mid);j++)
    {
        best=min(best,{dp[i-1][j]+C(j,mid),j});
    }
    ans=best.first;    
    rec(i,l,mid-1,optl,best.second);
    rec(i,mid+1,r,best.second,optr);    
}           
int compute_full()
{
    dp[0][0]=0;
    for(int i=1;i<=k;i++)
    {
        rec(i,1,n,0,n);
    }
}