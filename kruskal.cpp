#include<bits/stdc++.h>
typedef long long ll;
#define M 1000000007
#define endl "\n"
#define int long long 
using namespace std;

int find_parent(int parent[],int a)
{
    if(parent[a]>=0)
    {
        return find_parent(parent,parent[a]);
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

vector<pair<int,pair<int,int>>> graph; //{weight,{u,v}}

void kruskal()
{
	int n;// number of vertex
	int parent[n+1];
	sort(graph.begin(),graph.end());
	vector<pair<int,int>> MST;
	for(auto edge: graph)
	{
		if(find_parent(parent,edge.second.first)==find_parent(parent,edge.second.second))
		{
			continue;
		}
		merge_sets(parent,edge.second.first,edge.second.second);
		MST.push_back(make_pair(edge.second.first,edge.second.second));
	}
}

int32_t main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    
}

