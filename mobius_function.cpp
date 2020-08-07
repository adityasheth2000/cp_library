
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
Properties and uses of mobius function: https://codeforces.com/blog/entry/53925
*/