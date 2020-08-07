/*
sqrt(n) method for finding phi(n); 
*/
int phi(int n) 
{
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            while(n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if(n > 1)
        result -= result / n;
    return result;
}
/*
Properties of phi function:
1) phi(n)= count of numbers less than n that are co prime to n.
2) if p is prime, phi(p)=p-1;
3) if a and b are coprime, phi(ab)=phi(a)*phi(b)
4) in general: phi(ab)=phi(a)*phi(b)*(d/phi(d)) : where d=gcd(a,b)
5) if p is prime: phi(p^k)=p^k-p^(k-1), k>=1 
6) let n= (p1^a1)*(p2^a2)*(p3^a3)....*(pk^ak), then phi(n)=n*(1-1/p1)*(1-1/p2)....*(1-1/pk);
7) summation((phi(d))(for all d divisible by n))=n;

https://cp-algorithms.com/algebra/phi-function.html
https://en.wikipedia.org/wiki/Euler%27s_totient_function
*/

/*
algorithm for  finding euler totient function till nlog(log(n)).
Logic is similar to linear sieve.
*/
void phi_1_to_n(int n) {
    vector<int> phi(n + 1);
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}
