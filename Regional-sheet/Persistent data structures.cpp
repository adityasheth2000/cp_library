int st[21*N],lpt[21*N],rpt[21*N];
int root[N];

int NODE=0;
int build(int l,int r)
{
    int curnode=NODE++;
    if(l==r)
        return curnode;
    int m=(l+r)/2;
    lpt[curnode]=build(l,m);
    rpt[curnode]=build(m+1,r);
    return curnode;
}
int insert(int oldnode,int l,int r,int w)
{
    if(w>=l && w<=r){
        int curnode=NODE++;
        st[curnode]=st[oldnode]+1;//change this according to problem.
        if(l==r)
            return curnode;
        int m=(l+r)/2;
        lpt[curnode]=insert(lpt[oldnode],l,m,w);
        rpt[curnode]=insert(rpt[oldnode],m+1,r,w);
        return curnode;
    }
    else
        return oldnode;    
}