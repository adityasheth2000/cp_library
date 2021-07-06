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
