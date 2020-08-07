// Dont use #define int long long when working with these.
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define T  // Type of data structure: example-(int, pair<int,int>)
#define ordered_set tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>
/* how to use:
 * find_by_order(k) returns an iterator to k-th largest element(starting from 0)
 * order_of_key(k) returns the number of items in set strictly less than k.
 * int main()
 * {
 * 	ordered_set x;
 * 	x.insert(1);
 * 	x.insert(2);
 * 	x.insert(4);
 * 	x.insert(8);
 * 	x.insert(16);
 * 	cout<<*X.find_by_order(1)<<endl; // 2
    	cout<<*X.find_by_order(2)<<endl; // 4
    	cout<<*X.find_by_order(4)<<endl; // 16
    	cout<<(end(X)==X.find_by_order(6))<<endl; // true
	cout<<X.order_of_key(-5)<<endl;  // 0
    	cout<<X.order_of_key(1)<<endl;   // 0
    	cout<<X.order_of_key(3)<<endl;   // 2
    	cout<<X.order_of_key(4)<<endl;   // 2
    	cout<<X.order_of_key(400)<<endl; // 5
 * }
 * */
