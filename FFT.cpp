template<typename S, typename T> struct FFT //Use typename S as long long int, T as the data type of input vector and result vector
{
	using cmplx = complex<long double>; // Can use long double for more precision but it will increase constant factor.
	const long double PI = acos(-1.0); 
	void doDFT(vector<cmplx> &a, bool toInvert = false) 
	{
		S n = a.size();
		for(S i = 1, j = 0; i < n; i ++)
		{
			S bit = (n >> 1);
			for(; (j & bit); bit >>= 1) j ^= bit;
			j ^= bit;
			if(i < j) swap(a[i], a[j]);
		}
		for(S length = 2; length <= n; (length <<= 1)) 
		{
			long double angle = ((2.0 * PI) / length) * (toInvert ? -1 : 1); 	
			cmplx omegaLen(cos(angle), sin(angle));
			for(S i = 0; i < n; i += length) 
			{
				cmplx omega(1);
				for(S j = 0; j < (length / 2); j ++) 
				{
					cmplx evenVal = a[i+j], oddVal = (a[i+j+(length/2)] * omega);
					a[i+j] = evenVal + oddVal;
					a[i+j+(length/2)] = evenVal - oddVal;
					omega *= omegaLen;  
				}
			}
		}
		if(toInvert) 
		{
			for(cmplx &i : a) i /= n;
		}
	}
	vector<T> doFFT(vector<T> &a, vector<T> &b) 
	{
		vector<cmplx> newA(a.begin(), a.end());
		vector<cmplx> newB(b.begin(), b.end());
		S n = 1;
		while(n < (int)(a.size() + b.size())) n <<= 1;
		newA.resize(n);
		newB.resize(n); 
		doDFT(newA, false);
		doDFT(newB, false);
		for(S i = 0; i < n; i ++) 
		{
			newA[i] *= newB[i];
		}
		doDFT(newA, true);
		vector<T> result(n);
		for(S i = 0; i < n; i ++) 
		{
			result[i] = roundl(newA[i].real());//is T is floating point, don't round it.	
		}
		return result;
	}
};
/*
	How to use with int:
	FFT<int,int> ft;
    vector<int> a={1,1,1,1};
    auto v=ft.doFFT(a,a);
    for(auto x: v)
    {
        tr(x);
    }	
	Same way with double, just remove the round function in line 54.
*/
