
int find_parent(int parent[],int a)
{
    if(parent[a]>=0)
    {
        parent[a]=find_parent(parent,parent[a]);
        return parent[a];
    }
    else
    {
        return a;
    }    
}
void merge_sets(int parent[],int a,int b)
{
    int p1=find_parent(parent,a);
    int p2=find_parent(parent,b);
    if(p1==p2)
    {
        return;
    }
    else
    {
        if(abs(parent[p1])>abs(parent[p2]))
        {
            parent[p1]-=abs(parent[p2]);
            parent[p2]=p1;
        }   
        else
        {
            parent[p2]-=abs(parent[p1]);
            parent[p1]=p2;
        }        
    }       
}
/*
Explanation:
1) Parent[] array stores the information of the parent of the index position.
2) if The parent of the index pos is not there then it contains the total number of nodes it has as its children and grand children with negative sign.
*/
