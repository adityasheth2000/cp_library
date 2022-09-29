int LIS(vector<int> a)//Returns size of Longest increasing sequence.
{
	int n=a.size();
	vector<int> d(n+1,inf);
	for(int i=0;i<n;i++)
	{
		*(lower_bound(d.begin(),d.end(),a[i]))=a[i];
	}
	for(int i=0;i<=n;i++)
	{
		if(d[i]==inf)
		{
			return i;
		}
	}
	return 0;
}
<-------------------------------------------------------------------------------------------------->
Ishmeet code:

/*
	Note!
	1) Makes a dp array in which number represent to maximum length of sequence ending at the current index.
	2) Makes a predecessor array in which number represent the index of previous element. If it is equal to -1 then the current element is first element.
*/
template<typename S, typename T> /*vector<T>*/ /*pair<vector<S>, vector<S>>*/ S LIS(vector<T> a) {
	S sz = a.size();
	S maxLength = 1;
	vector<S> dp(sz, 1);
	vector<S> predecessor(sz, -1);
	set<pair<pair<T, S>, S>> cur;
	cur.insert({{a[0], 1}, 0});
	for(S i = 1; i < sz; i ++) {
		auto it = cur.upper_bound({{a[i], -1}, -1});
		if(it == cur.begin()) {
			cur.insert({{a[i], dp[i]}, i});
			continue;
		}
		it --;
		dp[i] += (*it).first.second;
		predecessor[i] = (*it).second;
		maxLength = max(maxLength, dp[i]);
		it ++;
		vector<pair<pair<T, S>, S>> toDelete;
		while((it != cur.end()) && (((*it).first.first >= a[i]) && ((*it).first.second <= dp[i]))) {
			toDelete.push_back((*it));
			it ++;
		}
		for(auto i : toDelete) cur.erase(i);
		cur.insert({{a[i], dp[i]}, i});
	}
	return maxLength;
	//return dp;
	//return {dp, predecessor};
}
