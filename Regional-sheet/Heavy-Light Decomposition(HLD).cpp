const int N = 250005;
vector<int> adj[N];
vector<int> subtree_size(N);

int dfs_subtree_size(int node, int par){
    subtree_size[node] = 1;
    for (auto x : adj[node])
        if (x != par)
            subtree_size[node] += dfs_subtree_size(x, node);
    return subtree_size[node];
}

vector<int> chain_number(N), index_in_chain(N); //chain_number and index_in_chain for each node.
vector<vector<int>> chains(N);                  // atmost N chains. each chain is collection of nodes in order from top to bottom by height.
map<pair<int, int>, int> chainInfo_to_node;     //mapping from {chain_number, index in chain} -> node of tree.
vector<pair<int, int>> parent_chain(N);         // contains information of {parent_chain_no, index_in_parent_chain} from each chain. -1 for root chain.
int cur_chain = 0;

void dfs_hld(int node, int par, int chain_no)
{
    chain_number[node] = chain_no;
    index_in_chain[node] = chains[chain_no].size();
    chains[chain_no].push_back(node);
    chainInfo_to_node[make_pair(chain_number[node], index_in_chain[node])] = node;

    pair<int, int> bigChild = {0, -1}; //{subSize of child, child_node}
    for (auto x : adj[node])
        if (x != par)
            bigChild = max(bigChild, make_pair(subtree_size[x], x));

    if (bigChild.second != -1)
        dfs_hld(bigChild.second, node, chain_no);

    for (auto x : adj[node]){
        if (x != par && x != bigChild.second){
            cur_chain++;
            parent_chain[cur_chain] = make_pair(chain_no, index_in_chain[node]);
            dfs_hld(x, node, cur_chain);
        }
    }
}