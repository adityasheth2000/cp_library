// add this line at the top of your code.
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//

// to randomly shuffle a vector v, use: 
// shuffle(v.begin(),v.end(),rng);
// to get a random number x use: int x=rng();
