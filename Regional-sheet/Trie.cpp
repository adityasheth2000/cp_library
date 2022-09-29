typedef struct data
{
	data* bit[2];
	int cnt = 0;
}trie;

void insert(trie* &head,int x){
	if(!head){
		head=new trie();
	}
	trie* cur = head;
	for(int i=30;i>=0;i--){
		int b = (x>>i) & 1;
		if(!cur->bit[b])
			cur->bit[b] = new trie();
		cur = cur->bit[b];
		cur->cnt++;
	}
}

//use only for persistent trie
void fork_new_trie(trie* &head,trie* par, int val){	
	head=new trie();
	trie* cur=head;
	for(int i=30;i>=0;i--){
		int b=(val>>i)&1;
		cur->bit[b]=new trie();
		cur->bit[b]->cnt++;
		if(par){
			cur->bit[!b]=par->bit[!b];
		}
		cur=cur->bit[b];
		if(par){
			par=par->bit[b];
		}
	}
}
