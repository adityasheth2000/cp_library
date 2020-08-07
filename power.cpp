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
1) (a/b)%mod= (a*(poww(b,phi(mod)-1,mod)))%mod iff a%b==0
2) (a^b)%mod= (a^(b%(mod-1)))%mod iff mod is prime
3) Fermat's little theorem: 
        a^(phi(n))=1 mod(n)  when a and n are relatively prime.
*/