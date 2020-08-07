#include<bits/stdc++.h>
typedef long long ll;
#define mod 1000000007
#define endl "\n"
using namespace std;


/*
Problem statement 1D: Given an array of length n, find all the minima of each sliding window of size k.
Problem statement 2D: Given a 2D array of n*m, find all the minima of submatrix of size k*l

Link: https://codeforces.com/blog/entry/53810
*/

void solve_1D(vector<int> ar,int k)
{
	deque<pair<int,int>> q;// stores {value, index}; Store the minimum element at q.back() at any time
	int n=ar.size();
	for(int i=0;i<n;i++)
	{
		while(!q.empty() && q.front().first>=ar[i])
		{
			q.pop_front();
		}
		while(!q.empty() && q.back().second <= (i-k))
		{
			q.pop_back();
		}
		q.push_front({ar[i],i});
		cout<<q.back().first<<endl;
	}
}



void solve_2D(vector<vector<int>> matrix,int k,int l)
{
	int n=matrix.size();
	int m=matrix[0].size();
	vector<vector<int>> colmin;
	colmin.resize(n);
	vector<vector<int>> ans(n-k+1,vector<int>(m-l+1));
	for(int row=0;row<matrix.size();row++)
	{
		deque<pair<int,int>> q;
		for(int col=0;col<matrix[row].size();col++)
		{
			while(!q.empty() && q.front().first>=matrix[row][col])
			{
				q.pop_front();
			}
			while(!q.empty() && q.back().second <= (col-l))
			{
				q.pop_back();
			}
			q.push_front({matrix[row][col],col});
			if(col>=l-1)
			{
				colmin[row].push_back(q.back().first);
			}
		}
	}

	for(int col=0;col<colmin[0].size();col++)
	{
		deque<pair<int,int>> q;	
		for(int row=0;row<colmin.size();row++)
		{
			while(!q.empty() && q.front().first>=colmin[row][col])
			{
				q.pop_front();
			}
			while(!q.empty() && q.back().second <= (row-k))
			{
				q.pop_back();
			}
			q.push_front({colmin[row][col],row});
			if(row>=k-1)
			{
				ans[row-(k-1)][col]=q.back().first;
			}
		}
	}

	for(int i=0;i<ans.size();i++)
	{
		for(auto x: ans[i])
		{
			cout<<x<<" ";
		}
		cout<<endl;
	}
}




int32_t main()
{
	//freopen("output.txt","w",stdout);
	//freopen("input.txt","r",stdin);
	ios::sync_with_stdio(0);cin.tie(0);	

	int n,m,k,l;
	cin>>n>>m>>k>>l;
	vector<vector<int>> matrix(n,vector<int>(m));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cin>>matrix[i][j];
		}
	}
	solve_2D(matrix, k, l);
}
