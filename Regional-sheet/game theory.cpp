/*
How to check if our classification of winning and losing state is correct:
1) Final position should be losing position.
2) In winning position it's possible to go to atleast one losing position.
3)In losing position we are forced to go to winning position.


Minimum Excludant(MEX):
1) Operation performed on a set.
2) returns the smallest number not present in the set.

Grundy numbers:
Grundy is the MEX of a set of moves that we can play.
Defines the entire game state.
Calculated as follows:
	1)take the Mex of set.
	2)If set is empty: mex(null set)=0
		Grundy(losing condition=0
	3)Grundy(x)=MEX({Grundy of reachable states}).
		if a reachable state in (3) consist of multiple piles,to find grundy of that reachable state,
		take xor of grundy of each pile.
	4) a set of piles can be converted to a single pile with the value as the xor of the set
	

How to find if a state is winning state or losing state:

1) If there are independent sub-games involved, we can take xor sum of grundy numbers of subgames 
	and the xorsum we get is the grundy number of overall game.
2) If Grundy is 0, losing state, else winning state.
*/
