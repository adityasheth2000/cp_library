template<typename T> T FastPower(T num, T raise, T modulo) {
	T result = 1;
	while(raise) {
		if(raise & 1) result = (result * num) % modulo;
		num = (num * num) % modulo;
		raise = (raise >> 1);
	}
	return result;
} 
template<typename S> struct NTT {
	const S threshold = 400;
	S modulo, root, rootInverse, rootPower;

	NTT(S setMod = 998244353, S setRoot = 15311432, S setInverse = 469870224, S setPower = (1 << 23)) {
		setNewMod(setMod, setRoot, setInverse, setPower);
	} 
	void setNewMod(S setMod, S setRoot, S setInverse, S setPower) {
		modulo = setMod;
		root = setRoot;
		rootInverse = setInverse;
		rootPower = setPower;
	}
	void doDFT(vector<S> &a, bool toInvert = false) {
		S n = a.size();
		for(S i = 1, j = 0; i < n; i ++) {
			S bit = (n >> 1);
			for(; (j & bit); bit >>= 1) j ^= bit;
			j ^= bit;
			if(i < j) swap(a[i], a[j]);
		}
		for(S length = 2; length <= n; (length <<= 1)) {
			S omegaLen = toInvert ? rootInverse : root;
			for(S i = length; i < rootPower; i <<= 1) {
				omegaLen = ((omegaLen * omegaLen) % modulo);
			}
			for(S i = 0; i < n; i += length) {
				S omega = 1;
				for(S j = 0; j < (length / 2); j ++) {
					S evenVal = a[i+j], oddVal = ((a[i+j+(length/2)] * omega) % modulo);
					a[i+j] = (evenVal+oddVal < modulo) ? evenVal+oddVal : evenVal+oddVal-modulo;
					a[i+j+(length/2)] = (evenVal-oddVal >= 0) ? evenVal-oddVal : evenVal-oddVal+modulo;
					omega = ((omega * omegaLen) % modulo);
				}
			}
		}
		if(toInvert) {
			S nInverse = FastPower(n, (S)(modulo-2), modulo);
			for(S &x : a) x = ((x * nInverse) % modulo);
		}
	}
	void bruteMulti(vector<S> &a, vector<S> &b) {
		vector<S> res(a.size()+b.size()-1, 0);
		for(S i = 0; i < a.size(); i ++) {
			for(S j = 0; j < b.size(); j ++) {
				res[i+j] = (res[i+j] + ((a[i] * b[j]) % modulo) + modulo) % modulo;
			}
		}
		a = res;
	}
	void doNTT(vector<S> &newA, vector<S> &newB) {
		if((newA.size() + newB.size()) <= threshold) {
			bruteMulti(newA, newB);	
			return;
		}
		S n = 1;
		while(n < (newA.size() + newB.size())) n <<= 1;
		newA.resize(n);
		newB.resize(n);
		doDFT(newA, false);
		doDFT(newB, false);
		for(int i = 0; i < n; i ++) {
			newA[i] = ((newA[i] * newB[i]) % modulo);
		}
		doDFT(newA, true);
	}
};

/*
Read abt primitive roots once if in doubt.
*/
