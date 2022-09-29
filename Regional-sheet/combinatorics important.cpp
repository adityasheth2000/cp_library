/*
1) n distinct objects in k distinct boxes: k^n.
2) n distinct objects in k identical boxes: S(n, r) or B_n , stirling number of second kind or bell number. Description below
3) n identical objects in k distinct boxes: (n+k-1)C(k-1);
4) n identical objects in k identical boxes giving atleast one to each of the box:
	can be calculated by in O(n*k) dp using the following theorem:
	The number of partitions of an integer nn into rr parts is the same as the number of partitions of nn for which the largest part is rr. Intuition is : think of it as histogram where x is upto r and taking the lowest row each time will reduce it by r forming smaller subproblem.	
	Thereafter the dp relation becomes: dp[n][r]=summation(dp[n-r][k]) for k=1 to k=r
	we can use prefix sum and calculate each dp[n][r] in O(1) giving the final complexity O(n*k).
	the whole idea is given on Brilliant.org 
	

Stirling number of second kind : A Stirling number of the second kind, denoted as S(n, r) is the number of ways to partition n objects in r non-empty sets.

S(n, r) = r * S(n-1, r) + S(n-1, r-1)
Base cases : 
S(n, r) = 1,if r == n 
S(n, r) = 0 if r > n

Bell numbers : B_n is the number of ways of arranging n distinct objects into upto n identical non-empty bins. 
B_n = S(n, 1) + S(n, 2) + ... + S(n, n) */