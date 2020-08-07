vector <int> prime;
bool is_composite[MAXN];

void sieve (int n) {
	fill(is_composite, is_composite + n, false);
	for (int i = 2; i < n; ++i) {
		if (!is_composite[i]) prime.push_back (i);
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			is_composite[i * prime[j]] = true;
			if (i % prime[j] == 0) break;//reason: if i%prime[j]==0, then i*prime[j+1] will also have prime[j] as it's spf, so i*prime[j+1] will be taken care later ig.
		}
	}
}

/*
check logic at: https://codeforces.com/blog/entry/54090
*/


/*
For finding the value of any multiplicative function(read definition at the blog mentioned above)
use this :
*/
vector <int> prime;
bool is_composite[MAXN];
int func[MAXN], cnt[MAXN];
//func[i] is the value of multiplicative function at i
void sieve (int n) {
	fill (is_composite, is_composite + n, false);
	func[1] = 1;
	for (int i = 2; i < n; ++i) {
		if (!is_composite[i]) {
			prime.push_back (i);
			func[i] = ;// according to definition. 
			cnt[i] = 1;
		}
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			is_composite[i * prime[j]] = true;
			if (i % prime[j] == 0) {
				func[i * prime[j]] = func[i] / cnt[i] * (cnt[i] + 1);
				cnt[i * prime[j]] = cnt[i] + 1;
				break;
			} else {
				func[i * prime[j]] = func[i] * func[prime[j]];
				cnt[i * prime[j]] = 1;
			}
		}
	}
}