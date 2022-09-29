struct Condense_graph_SCC //WARNING: 1-based indexing
{
    int n;
    vector<vector<int>> adj, adjtranspose;
    vector<bool> visited1, visited2;
    stack<int> st;
    vector<int> color;
    vector<vector<int>> SCC;    // Beware of Multi-edge between two SCC's
    int c=0;                    //number of colors
    void init(int r)            // pass the exact number of nodes n from 1 to n in consideration.
    {
        adj.clear();
        adjtranspose.clear();
        visited1.clear();
        visited2.clear();
        st.clear();
        color.clear();
        SCC.clear();
        n=r;
        adj.resize(r+5);
        adjtranspose.resize(r+5);
        visited1.resize(r+5,false);
        visited2.resize(r+5,false);
        color.resize(r+5,-1);
        c=0;
    }
    void add_edge(int u,int v){
        adj[u].push_back(v);
        adjtranspose[v].push_back(u);
    }
    void dfs1(int node){
        visited1[node]=true;
        for(auto x: adj[node]){
            if(!visited1[x]){
                dfs1(x);
            }
        }
        st.push(node);
    }
    void dfs2(int node,int c){
        visited2[node]=true;
        color[node]=c;
        for(auto x: adjtranspose[node]){
            if(!visited2[x])
                dfs2(x,c);
        }
    }
    void condense_directed_graph()// adj and adjtranspose should already be constructed before calling this function
    {   
        for(int i=1;i<=n;i++){
            if(!visited1[i]){
                dfs1(i);
            }
        }       
        while(!st.empty()){
            int x=st.top();
            st.pop();
            if(!visited2[x]){
                dfs2(x,c++);
            }
        }
        SCC.resize(c);
        for(int i=1;i<=n;i++){
            for(auto x: adj[i]){
                if(color[i]!=color[x]){
                    SCC[color[i]].push_back(color[x]);
                }
            }
        }   
    }
};
