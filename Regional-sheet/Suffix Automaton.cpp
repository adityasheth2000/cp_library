class SuffixAutomaton{
    private:
        map <int,int> c;
    public:
        vector <map<char,int> > edges; vector <int> link;
        vector <int> length; map <int,int> terminals;
        vector <int> count;
        int last;

        SuffixAutomaton(string s) {
        edges.push_back(map<char,int>());
        link.push_back(-1);
        length.push_back(0);
        last = 0;
        for(int i=0;i<s.size();i++) {
            edges.push_back(map<char,int>());
            length.push_back(i+1);
            link.push_back(0);
            int r = edges.size() - 1;
            int p = last;
            while(p >= 0 && edges[p].find(s[i]) == edges[p].end()) {
                edges[p][s[i]] = r;
                p = link[p];
            }
            if(p != -1) {
                int q = edges[p][s[i]];
                if(length[p] + 1 == length[q]) {
                    link[r] = q;
                } 
                else {
                    edges.push_back(edges[q]);
                    length.push_back(length[p] + 1);
                    link.push_back(link[q]);
                    int qq = edges.size()-1;
                    c[qq]=1;
                    link[q] = qq;
                    link[r] = qq;
                    while(p >= 0 && edges[p][s[i]] == q) {
                        edges[p][s[i]] = qq;
                        p = link[p];
                    }
                }
            }
            last = r;
        }
        set <pair<int,int> > base;c[0]=0;
        for(int i=0;i<sz(length);i++){
            if(c[i]==1){
                count.push_back(0);
                base.insert(make_pair(length[i],i));}
            else{count.push_back(1);
                base.insert(make_pair(length[i],i));}
        }
        for(auto itr=base.rbegin();itr!=base.rend();itr++){
            count[link[itr->second]]+=count[itr->second];
        }
        int p = last;
        while(p > 0) {
            terminals[p]=1;
            p = link[p];
        }
    }
};