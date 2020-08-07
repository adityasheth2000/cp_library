ll poww(long long a, long long n, long long m)
{
        long long ans = 1;
        long long mul = a;
        while (n != 0)
        {
                if (n % 2)
                {
                        ans = (ans * mul) % m;
                }
                mul = (mul * mul) % m;
                n /= 2;
        }
        return ans;
}
/* 
Fermat's little theorem: 
1) (a/b)%mod= (a*(poww(b,mod-2,mod)))%mod iff a%b==0
2) (a^b)%mod= (a^(b%(mod-1)))%mod iff mod is prime
*/
const int SZ=2e5+100;
ll factorial[SZ];
ll iv[SZ];
void precompute()
{
	factorial[0]=1;
    iv[0]=1;
	for(int i=1;i<SZ;i++)
	{
		factorial[i]=(factorial[i-1]*i)%MOD;
	    iv[i]=poww(factorial[i],MOD-2,MOD);
    }
}
ll InverseEuler(ll n, ll m)
{
    return poww(n, m - 2, m);
}
ll C(ll n, ll r, ll m)
{
	if(r>n || r<0)return 0;
    return (factorial[n] * ((iv[r] * iv[n-r]) % m)) % m;
}
