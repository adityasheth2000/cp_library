// Dont use #define int long long when working with these.
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define T  // Type of data structure: example-(int, pair<int,int>)
#define ordered_set tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>
/* how to use:
*X.find_by_order(1) 
X.order_of_key(400)
 * }
 * */
