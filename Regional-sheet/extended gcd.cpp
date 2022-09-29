int extgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
/*
 * It is used for getting the coefficients x, y such that ax+by=gcd(a,b)
 * 
 * this is particularly useful in solving linear diophantine equation.
 * check out cpalgorithms.com if you want the proof how it works.
 * it works even for negative value.
 * /
