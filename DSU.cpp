int find_parent(int parent[],int a){
    if(parent[a]>=0)return parent[a]=find_parent(parent,parent[a]);else return a;
}
void merge_sets(int parent[],int a,int b){
    int p1=find_parent(parent,a),p2=find_parent(parent,b);if(p1==p2)return;
    if(abs(parent[p1])<abs(parent[p2]))swap(p1,p2);
    parent[p1]-=abs(parent[p2]);parent[p2]=p1;
}
