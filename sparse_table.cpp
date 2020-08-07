const int k = 20;
const int N = 3e5+5;
const int ZERO = 0; // ZERO + x = x + ZERO = x (for any x)
int table[N][k + 1]; // k + 1 because we need to access table[r][k]// gcd,min
void build()
{
    for(int i = 0; i < n; i++)
    {
        table[i][0] = ar[i];            
    }
    for(int j = 1; j <= k; j++) 
    {
        for(int i = 0; i <= n - (1 << j); i++)
        {
            table[i][j] =min(table[i][j - 1],table[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int L,int R)
{   
    int answer=1e18;	
    for(int j = k; j >= 0; j--) {
        if(L + (1 << j) - 1 <= R) {
            answer=min(answer,table[L][j]);
            L += 1 << j; // instead of having L', we increment L directly
        }
    }
    return answer;
}
