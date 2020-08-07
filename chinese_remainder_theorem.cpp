/*
Use #define int long long or BigInteger Library in case of Large numbers possible.
*/
long long GCD(long long a, long long b) { return (b == 0) ? a : GCD(b, a % b); }
inline long long LCM(long long a, long long b) { return a / GCD(a, b) * b; }
inline long long normalize(long long x, long long mod) { x %= mod; if (x < 0) x += mod; return x; }
struct GCD_type { long long x, y, d; };
GCD_type ex_GCD(long long a, long long b)
{
    if (b == 0) return {1, 0, a};
    GCD_type pom = ex_GCD(b, a % b);
    return {pom.y, pom.x - a / b * pom.y, pom.d};
}
pair<int,int> CRT(vector<int> a,vector<int> b)// finds ans such that (ans=a[i]) mod(b[i]). IF NOT possible, returns {-1,-1}
{
    int t=a.size();
    for(int i=0;i<t;i++)
    {
        normalize(a[i],b[i]);  
    }
    int ans=a[0];
    int lcm=b[0];
    for(int i=1;i<t;i++)
    {
        auto pom = ex_GCD(lcm, b[i]);
        int x1 = pom.x;
        int d = pom.d;
        if((a[i] - ans) % d != 0) return cerr << "No solutions" << endl, make_pair(-1,-1);
        ans = normalize(ans + x1 * (a[i] - ans) / d % (b[i] / d) * lcm, lcm * b[i] / d);
        lcm = LCM(lcm, b[i]); // you can save time by replacing above lcm * n[i] /d by lcm = lcm * n[i] / d
    }
    return make_pair(ans,lcm);
}
