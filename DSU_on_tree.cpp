/*
This is Heavy light decomposition style of DSU on tree.
Link to tutorial: https://codeforces.com/blog/entry/44351
*/
// can answer queries of type:How many vertices in the subtree of vertex v has some property in  time O(nlogn) (for all of the queries)?
const int maxn=;

int cnt[maxn];
bool big[maxn];
int sz[maxn];     // call szdfs for filling this.

void szdfs(int node,int par)
{
    sz[node]=1;
    for(auto x: adj[node])
    {
        if(x!=par)
        {
            szdfs(x,node);
            sz[node]+=sz[x];
        }
    }
}
void add(int v, int p, int x)// this implementation changes as per question.
{
    cnt[ col[v] ] += x;
    for(auto u: adj[v])
        if(u != p && !big[u])
            add(u, v, x);
}

void dfs(int v, int p, bool keep)
{
    int mx = -1, bigChild = -1;
    for(auto u : adj[v])
       if(u != p && sz[u] > mx)
          mx = sz[u], bigChild = u;
    for(auto u : adj[v])
        if(u != p && u != bigChild)
            dfs(u, v, 0);  // run a dfs on small childs and clear them from cnt
    if(bigChild != -1)
        dfs(bigChild, v, 1), big[bigChild] = 1;  // bigChild marked as big and not cleared from cnt
    add(v, p, 1);
    //now cnt[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    if(bigChild != -1)
        big[bigChild] = 0;
    if(keep == 0)
        add(v, p, -1);
}
