#include<bits/stdc++.h>
using namespace std;


void multiple(int F[2][2],int M[2][2])
{
	int t1;
	t1=F[0][0]*M[0][0]+F[0][1]*M[1][0];
	
	int t2;
        t2=F[0][0]*M[0][1]+F[0][1]*M[1][1];
	
	int t3;
        t3=F[1][0]*M[0][0]+F[1][1]*M[1][0];
	
	int t4;
        t4=F[1][0]*M[0][1]+F[1][1]*M[1][1];
	
	F[0][0]=t1;
	F[0][1]=t2;
	F[1][0]=t3;
	F[1][1]=t4;


}
int power(int F[2][2],int n)
{
	int ans[2][2]={{1,0},{0,1}};

	while(n>0)
	{
		if(n%2==0)
		{
			multiple(F,F);
			n/=2;
		}
		else
		{
			multiple(ans,F);
			multiple(F,F);
			n/=2;
		}
	}
	return ans[0][0];
}
int fib(int n)
{
	int F[2][2]={{1,1},{1,0}};
	return power(F,n-1);
}

int main()
{
	int n;
	cin>>n;

	int ans=fib(n);
	cout<<ans;

	//printf("%d",ans);
}
