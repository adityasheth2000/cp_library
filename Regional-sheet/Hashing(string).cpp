struct Hash_string// make one struct for each string to be hashed;
{
	vector<ll> hash;
	vector<ll> inv;

	const int base=31;
	int m;

	ll cur_val=0;
	ll compute_hash(string &s,int mod){
		m=mod;
		int n=s.length();
		hash.resize(n+1);
		inv.resize(n+1);
		ll p_pow=1;
		for(int i=0;i<n;i++){	
			cur_val=cur_val+(p_pow*(s[i]-'a'+1))%m;
			cur_val%=m;
			hash[i]=cur_val;
			inv[i]=poww(p_pow,m-2,m);
			p_pow=(p_pow*base)%m;
		}
		return cur_val;
	}
	ll get_hash(int l,int r){
		if(l==0)
			return hash[r];
		ll ret=hash[r]-hash[l-1];
		ret%=m;
		ret=(ret+m)%m;
		ret=ret*inv[l];
		ret%=m;
		return ret;
	}
};
// When u need double hash, make two struct object for the string(one with MOD=1e9+7, another with MOD=1e9+9).