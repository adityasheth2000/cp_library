typedef struct data
{
	data* bit[2];
	int cnt = 0;
}trie;

void insert(trie* &head,int x)
{
	if(!head)
	{
		head=new trie();
	}
	trie* cur = head;
	for(int i=30;i>=0;i--)
	{
		int b = (x>>i) & 1;
		if(!cur->bit[b])
			cur->bit[b] = new trie();
		cur = cur->bit[b];
		cur->cnt++;
	}
}

void remove(trie* &head,int x)
{
	trie* cur = head;
	for(int i=30;i>=0;i--)
	{
		int b = (x>>i) & 1;
		cur = cur->bit[b];
		cur->cnt--;
	}
}

int maxxor(trie* &head,int x)
{
	trie* cur = head;
	int ans = 0;
	for(int i=30;i>=0;i--)
	{
		int b = (x>>i)&1;
		if(cur->bit[!b] && cur->bit[!b]->cnt>0)
		{
			ans += (1LL<<i);
			cur = cur->bit[!b];
		}
		else
			cur = cur->bit[b];
	}
	return ans;
}
int minxor(trie* &head,int x)
{
	trie* cur = head;
	int ans = 0;
	for(int i=30;i>=0;i--)
	{
		
		int b = (x>>i)&1;
		if(cur->bit[b] && cur->bit[b]->cnt>0)
		{
			cur = cur->bit[b];
		}
		else
		{
			ans+=(1LL<<i);
			cur = cur->bit[!b];
		}
	}
	return ans;
}

void fork_new_trie(trie* &head,trie* par, int val)
{	
	head=new trie();
	trie* cur=head;
	for(int i=30;i>=0;i--)
	{
		int b=(val>>i)&1;
		cur->bit[b]=new trie();
		cur->bit[b]->cnt++;
		if(par)
		{
			cur->bit[!b]=par->bit[!b];
		}
		cur=cur->bit[b];
		if(par)
		{
			par=par->bit[b];
		}
	}
}

//https://www.codechef.com/problems/GPD (Persistent trie,check this once)
