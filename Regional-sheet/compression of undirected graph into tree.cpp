// Idea is to compress two way connected components of an undirected connected graph into a tree. So all the set of nodes that have two or more ways to reach one from another is compressed to one node.

// Algorithm:
// 1) Make a recursion function to create a directed graph:
void construct_directed_graph(int node,int prev){
    //t(node);
    if(vis[node])
    	return;
    vis[node]=1;
    for(auto &x: undirected[node]){
        if(x==prev)
        	continue;
        adj[node].push_back(x);
        adjtranspose[x].push_back(node);
        construct_directed_graph(x,node);
    }
}
// 2) This will create a directed graph. 
// 3) we can compress all the components in this directed graph if they are Strongly connected components.
// Use condensation_of_directed_graph_using_SCC.cpp
// 4) To get back tree, modify the code from condensation_of_directed_graph_using_SCC.cpp 
