
const int MAXN=1e7+100;
vector <int> prime;
bool is_composite[MAXN];
int mobius[MAXN];
void sieve (int n) {
	mobius[1] = 1;
	for (int i = 2; i < n; ++i) {
		if (!is_composite[i]) {
			prime.push_back (i);
			mobius[i] = -1;// according to definition.
		}
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			is_composite[i * prime[j]] = true;
			if (i % prime[j] == 0) {
				mobius[i * prime[j]] = 0;
				break;
			} else {
				mobius[i * prime[j]] = mobius[i] * mobius[prime[j]];
			}
		}
	}
}

/*
O(n) implementation of calculating the mobius value from 1 to n-1.

mobius[p^k] = [k=0] - [k=1] // where [] is boolean function
mobius[p1^k1 * p2^k2 * p3^k3 ... ] = mobius[p1^k1] * mobius[p2^k2] .... // mobius is multiplicative function

Mobius inversion states that :
if g(n) = summation_(d|n) f(d), then
f(n) = summation_(d|n) g(d) * mobius(n/d)

Most important property for mobius inversion : 

(summation_(d|n) mobius(d)) = [n=1] , that is summation of mobius(d) for (divisors d of n) is 1 iff [n=1], otherwise 0

Few results : 
1) Number of co-prime pair of integers (x, y) in range [1, n] := summation_{d=1 to d=n} mobius(d) * floor(n/d)^2
2) Sum of gcd of every pair of integers (x, y) in range[1, n] := summation_{k=1 to n} (number of co-prime pair of integers in range [1,n/k])

*/