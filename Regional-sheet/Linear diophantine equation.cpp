/*
A Linear Diophantine Equation (in two variables) is an equation of the general form:

ax+by=c
where a, b, c are given integers, and x, y are unknown integers.

In this article, we consider several classical problems on these equations:

finding one solution
finding all solutions
finding the number of solutions and the solutions themselves in a given interval
finding a solution with minimum value of x+y
*/

/* CODE FOR FINDING ONE SOLUTION OF ax+by=c.
The function will return false if any solution is not possible. x0 ,y0 and g are modified as passed by reference
*/
int gcd(int a, int b, int &x, int &y) 
{
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    int x1, y1;
    int d = gcd(b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) 
{
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }
    
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

/*
To find any other solution: 
x=x0+k*(b/g)
y=y0−k*(a/g)
Where k is any integer.
*/