vector<int> sort_cyclic_shifts(string const& s) {
    int n = s.size();
    const int alphabet = 256;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
        cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}
vector<int> suffix_array(string s) {
    s += "$";
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}
/*
Uses of suffix_array:
1)Finding the smallest cyclic shift: The function sort_cyclic_shift(string s)
sorts all the cyclic shifts. Use that function and the p[0] gives the position
of smallest cyclic shift.

2) Finding a substring in a string: 
The task is to find a string s inside some text t online - we know the text t 
beforehand, but not the string s. We can create the suffix array for the text 
t in O(|t|log|t|) time. Now we can look for the substring s in the following way. 
The occurrence of s must be a prefix of some suffix from t. Since we sorted all the 
suffixes we can perform a binary search for s in p. Comparing the current suffix and 
the substring s within the binary search can be done in O(|s|) time, therefore the complexity 
for finding the substring is O(|s|log|t|). Also notice that if the substring occurs multiple 
times in t, then all occurrences will be next to each other in p. Therefore the number 
of occurrences can be found with a second binary search, and all occurrences can be printed easily.



Returns lcp[i] = LCP(string starting at sa[i], '' '' '' sa[i+1])
where sa=suffix_array(string s)
*/
vector<int> lcp_construction(string const& s, vector<int> const& p) {
    int n = s.size();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)
        rank[p[i]] = i;
    int k = 0;
    vector<int> lcp(n-1, 0);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k])
            k++;
        lcp[rank[i]] = k;
        if (k)
            k--;
    }
    return lcp;
}
/*
Use of LCP:
1) To find the LCP of string starting from sa[i] and sa[j],
find the min(lcp[i],lcp[i+1], ... , lcp[j-1]).
For efficiency, use segtree or sparse table for RMQ of lcp array.

2) Number of different substrings of a string of length n:
    get sa=suffix_array and lcp array. Then:
    int ans=0;
    ans+=(n*(n+1))/2;
    ans-=summation(lcp[0],lcp[1], ..., lcp[n-2]);
    return ans;
    check the logic from cp-algorithms if forgotten.
*/
