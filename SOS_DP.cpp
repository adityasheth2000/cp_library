/*
	Sum_over_submask blog: https://codeforces.com/blog/entry/45223
	Sum_over_supermask: https://discuss.codechef.com/t/andpref-editorial/84247 
*/


void sum_over_submask()
{
	for(int i = 0; i<(1<<max_bit); ++i)
		F[i] = A[i];
	for(int i = 0;i < max_bit; ++i) for(int mask = 0; mask < (1<<max_bit); ++mask){
		if(mask & (1<<i))
			F[mask] += F[mask^(1<<i)]; 
	}
}

void sum_over_supermask()
{
	for(int i=0;i<(1<<max_bit);i++)
		F[i]=A[i];
	for(int i=0;i<max_bit;i++){
		for(int mask=0;mask<(1<<max_bit);mask++){
			if(mask&(1<<i))
				F[mask^(1<<i)]+=F[mask];
		}
	}	
}



vector<int> mobius_transform(int n, vector<int> f)
{
	//BLOG : https://codeforces.com/blog/entry/72488
	/* Definition : mu[S] = + f[S]  
							- (all subset of S with exactly one element removed) 
							+ (all subsets of S with exactly 2 elements removed)
							- ()
							+ ()  
		check definition in blog for more clarity.
	*/
	assert(f.size() == (1<<n));
	// Apply odd-negation transform
	for(int mask = 0; mask < (1 << n); mask++) {
		if((__builtin_popcount(mask) % 2) == 1) {
			f[mask] *= -1;
		}
	}

	// Apply zeta transform
	for(int i = 0; i < n; i++) {
		for(int mask = 0; mask < (1 << n); mask++) {
			if((mask & (1 << i)) != 0) {
				f[mask] += f[mask ^ (1 << i)];
			}
		}
	}

	// Apply odd-negation transform
	for(int mask = 0; mask < (1 << n); mask++) {
		if((__builtin_popcount(mask) % 2) == 1) {
			f[mask] *= -1;
		}
	}
	vector<int> mu(1<<n);
	for(int mask = 0; mask < (1 << n); mask++)  mu[mask] = f[mask];
	
	return mu;
}
