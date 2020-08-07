//Gives vector of prime_factors of a number in O(sqrt(n))
vector<int> prime_factors(int n) 
{ 
    vector<int> v;
    for (int i=2; i*i<=n; i++) 
    { 
        if(n%i==0)
        {
            v.push_back(i);
            n/=i;
            i--;
        }
    } 
    v.push_back(n);
    return v;
} 
