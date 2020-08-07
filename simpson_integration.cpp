const int N_steps = 3e7; // number of steps (already multiplied by 2)

ld f(ld x) //changes every time according to integration.
{
    
}
 
ld simpson_integration(ld a, ld b){
    ld h = (b - a) / N_steps;
    ld s = f(a) + f(b); // a = x_0 and b = x_2n
    for (int i = 1; i <= N_steps - 1; ++i) { // Refer to final Simpson's formula
        ld x = a + h * i;
        s += f(x) * ((i & 1) ? 4 : 2);
    }
    s *= h / 3;
    return s;
}