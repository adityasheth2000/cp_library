/*

Algorithm:
1) Create an empty stack.

2) Start from first bar, and do following for every bar ‘hist[i]’ where ‘i’ varies from 0 to n-1.
……a) If stack is empty or hist[i] is higher than the bar at top of stack, then push ‘i’ to stack.
……b) If this bar is smaller than the top of stack, then keep removing the top of stack while top of the stack 
	is greater. Let the removed bar be hist[tp]. Calculate area of rectangle with hist[tp] as smallest bar. 
	For hist[tp],the ‘left index’ is previous (previous to tp) item in stack and ‘right index’ is ‘i’ (current index).
3) If the stack is not empty, then one by one remove all bars from stack and do step 2.b for every removed bar.

*/

int largest_area_under_histogram(vector<int> hist)
{
	int n=hist.size();
	stack<int> st;
	int i=0;
	int ans=0;
	while(i<n)
	{
		if(st.empty() || hist[st.top()]<=hist[i])
		{
			st.push(i++);
		}		
		else
		{
			int tp=st.top();
			st.pop();
			int cur=hist[tp]*(st.empty()?i:(i-1-st.top()));
			ans=max(ans,cur); 
		}
	}
	while(!st.empty())
	{
		int tp=st.top();
		st.pop();
		int cur=hist[tp]*(st.empty()?i:(i-1-st.top()));
		ans=max(ans,cur); 
	}
	return ans;
}