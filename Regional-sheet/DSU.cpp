struct DSU{
    int parent = -1;
};
int find_parent(vector<DSU> &ds, int v){
    while (ds[v].parent >= 0)
        v = ds[v].parent;
    return v;
}
void merge_sets(vector<DSU> &ds, int a, int b){
    int p1 = find_parent(ds, a);
    int p2 = find_parent(ds, b);
    if (p1 == p2)
        return;
    if (abs(ds[p1].parent) < abs(ds[p2].parent)){
        swap(p1, p2);
        swap(a, b);
    }
    ds[p1].parent -= abs(ds[p2].parent);
    ds[p2].parent = p1;
}
