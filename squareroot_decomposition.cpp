const int SZ = ;

struct sqrtDecomposition
{
    int L, R;
    int col[SZ + 3];
    int contrib[SZ + 3];
    bool lazy;
    int lazyval;
    int sum;
    int extra = 0;
    void init(int l, int r)
    {
        L = l, R = r;
        for (int i = l; i <= r; i++)
        {
            col[i - l] = i;
            contrib[i - l] = 0;
        }
        lazy = 0;
        sum = 0;
        extra=0;
        lazyval = 0;
    }

    int full_query()
    {
        return sum;
    }
    int semi_query(int l, int r)
    {
        if (l > r)
            return 0;
        if (lazy)
        {
            for (int i = L; i <= R; i++)
            {
                contrib[i - L] += extra;
                col[i - L] = lazyval;
            }
            extra = 0;
            lazy = 0;
            lazyval = 0;
        }
        int ans = 0;
        for (int i = max(L, l); i <= min(r, R); i++)
        {
            ans += contrib[i - L];
        }
        return ans;
    }
    void full_update(int x)
    {
        if (lazy)
        {
            sum += abs(x - lazyval) * (R - L + 1);
            extra += abs(x - lazyval);
        }
        else
        {
            for (int i = L; i <= R; i++)
            {
                contrib[i - L] += abs(x - col[i - L]);
                sum += abs(x - col[i - L]);
                col[i - L] = x;
            }
        }
        lazy = 1;
        lazyval = x;
    }
    void semi_update(int l, int r, int x)
    {
        if (l > r)
        {
            return;
        }
        if (lazy)
        {
            for (int i = L; i <= R; i++)
            {
                contrib[i - L] += extra;
                col[i - L] = lazyval;
            }
            extra = 0;
            lazy = 0;
            lazyval = 0;
        }
        for (int i = max(l, L); i <= min(r, R); i++)
        {
            contrib[i - L] += abs(x - col[i - L]);
            sum += abs(x - col[i - L]);
            col[i - L] = x;
        }
    }
    void update(int l, int r, int x)
    {
        if (l <= L && r >= R)
        {
            full_update(x);
        }
        else
        {
            semi_update(l, r, x);
        }
    }
    int query(int l, int r)
    {
        if (l <= L && r >= R)
        {
            return full_query();
        }
        else
        {
            return semi_query(l, r);
        }
    }
};

/*
Reference submissions: https://codeforces.com/problemset/submission/444/70436608
*/