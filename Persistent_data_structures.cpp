int st[21*N],lpt[21*N],rpt[21*N];
int root[N];

int NODE=0;
int build(int l,int r)
{
    int curnode=NODE++;
    if(l==r)
    {
        return curnode;
    }
    int m=(l+r)/2;
    lpt[curnode]=build(l,m);
    rpt[curnode]=build(m+1,r);
    return curnode;
}
int insert(int oldnode,int l,int r,int w)
{
    if(w>=l && w<=r)
    {
        int curnode=NODE++;
        st[curnode]=st[oldnode]+1;//change this according to question.
        if(l==r)
        {
            return curnode;
        }
        int m=(l+r)/2;
        lpt[curnode]=insert(lpt[oldnode],l,m,w);
        rpt[curnode]=insert(rpt[oldnode],m+1,r,w);
        return curnode;
    }
    else
    {
        return oldnode;
    }    
}

/*
1)  Problem: https://www.spoj.com/problems/COT/ (Persistent segment tree + coordinate compression + LCA)
    code: https://pastebin.com/JuP3Q6Lv
2)  Problem: https://www.codechef.com/problems/GPD (Persistent trie)
    code: check on my submission
3)  Problem: https://www.spoj.com/problems/MKTHNUM/ (Persistent segment tree)
    Code: https://pastebin.com/XsH5iAzu
4)  Problem 3 (Take atmost K values of a particular value in a range): https://codeforces.com/contest/813/problem/E
    code: https://codeforces.com/contest/813/submission/81633694 

*/