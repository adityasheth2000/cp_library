/*
Minimum Excludant(MEX): 
1)Operation performed on a set.
2)returns the smallest number not present in the set.
 
Grundy numbers:
Grundy is the MEX of a set of moves that we can play.
Defines the entire game state.
Calculated as follows: 
	1)take the Mex of set.
	2)If set is empty: mex(null set)=0
		Grundy(losing condition)=0
	3)Grundy(x)=MEX({Grundy of reachable states}).
		if a reachable state in (3) consist of multiple piles,to find grundy of that reachable state,
		take xor of grundy of each pile.

How to find if a state is winning state or losing state:

-> if Grundy is 0, losing state, else winning state.
*/

int mex(set<int> &se)
{
	int me=0;
	while(se.count(me))
	{
		me++;
	}
	return me;
}