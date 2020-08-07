/*--------------------Dinic's flow:-----------------------------*/
/*
Time complexity:
general case : O((V^2)*E)
0-1 flow     : O(E*sqrt(V))
Bipartite graph: O(sqrt(v)*E)
*/
struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};

/*--------------------------------Push Relabel method-------------------------------------------*/
//Time Complexity: O(V^2 √E) 
//To obtain the actual flow values, look at all edges with capacity > 0
//Zero capacity edges are residual edges
struct edge
{
    int from, to, cap, flow, index;
    edge(int from, int to, int cap, int flow, int index):
        from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct PushRelabel
{
    static const long long INF=1e18;

    int n;
    vector<vector<edge> > g;
    vector<long long> excess;
    vector<int> height;
    PushRelabel(int n):
        n(n), g(n), excess(n), height(n) {}

    void addEdge(int from, int to, int cap)
    {
        g[from].push_back(edge(from, to, cap, 0, g[to].size()));
        if(from==to)
            g[from].back().index++;
        g[to].push_back(edge(to, from, 0, 0, g[from].size()-1));
    }

    void push(edge &e)
    {
        int amt=(int)min(excess[e.from], (long long)e.cap - e.flow);
        if(height[e.from]<=height[e.to] || amt==0)
            return;
        e.flow += amt;
        g[e.to][e.index].flow -= amt;
        excess[e.to] += amt;
        excess[e.from] -= amt;
    }

    void relabel(int u)
    {
        int d=2e5;
        for(auto &it:g[u])
        {
            if(it.cap-it.flow>0)
                d=min(d, height[it.to]);
        }
        if(d<INF)
            height[u]=d+1;
    }

    vector<int> find_max_height_vertices(int source, int dest)
    {
        vector<int> max_height;
        for(int i=0;i<n;i++)
        {
            if(i!=source && i!=dest && excess[i]>0)
            {
                if(!max_height.empty() && height[i] > height[max_height[0]])
                    max_height.clear();
                if(max_height.empty() || height[i] == height[max_height[0]])
                    max_height.push_back(i);
            }
        }
        return max_height;
    }

    long long max_flow(int source, int dest)
    {
        excess.assign(n, 0);
        height.assign(n, 0);
        height[source]=n;
        excess[source]=INF;
        for(auto &it:g[source])
            push(it);

        vector<int> current;
        while(!(current = find_max_height_vertices(source, dest)).empty())
        {
            for(auto i:current)
            {
                bool pushed=false;
                for(auto &e:g[i])
                {
                    if(excess[i]==0)
                        break;
                    if(e.cap - e.flow>0 && height[e.from] == height[e.to] + 1)
                    {
                        push(e);
                        pushed=true;
                    }
                }
                if(!pushed)
                {
                    relabel(i);
                    break;
                }
            }
        }

        long long max_flow=0;
        for(auto &e:g[source])
            max_flow+=e.flow;
        return max_flow;
    }
};

//Problem 1: http://codeforces.com/contest/546/problem/E
//Solution 1: http://codeforces.com/contest/546/submission/40528334


/*--------------------MIN COST MAX FLOW ALGORITHM------------------*/
// Time complexity: O(min(E^2 *V log V, E logV * flow))
const int mxN = ;//fill this everytime
const int INF = 2e9;
struct Edgee {
  int to, cost, cap, flow, backEdge;
};
struct MCMF {
  int s, t, n;
  vector<Edgee> g[mxN];
  MCMF(int _s, int _t, int _n) {
    s = _s, t = _t, n = _n;
  }
  void addEdge(int u, int v, int cost, int cap) {
    Edgee e1 = { v, cost, cap, 0, (int)g[v].size() };
    Edgee e2 = { u, -cost, 0, 0, (int)g[u].size() };
    g[u].push_back(e1); g[v].push_back(e2);
  }
  pair<int, int> minCostMaxFlow() {
    int flow = 0, cost = 0;
    vector<int> state(n), from(n), from_edge(n), d(n);
    deque<int> q;
    while (true) {
      for (int i = 0; i < n; i++)
        state[i] = 2, d[i] = INF, from[i] = -1;
      state[s] = 1; q.clear(); q.push_back(s); d[s] = 0;
      while (!q.empty()) {
        int v = q.front(); q.pop_front(); state[v] = 0;
        for (int i = 0; i < (int) g[v].size(); i++) {
          Edgee e = g[v][i];
          if (e.flow >= e.cap || d[e.to] <= d[v] + e.cost)
            continue;
          int to = e.to; d[to] = d[v] + e.cost;
          from[to] = v; from_edge[to] = i;
          if (state[to] == 1) continue;
          if (!state[to] || (!q.empty() && d[q.front()] > d[to]))
            q.push_front(to);
          else q.push_back(to);
          state[to] = 1;
        }
      }
      if (d[t] == INF) break;
      int it = t, addflow = INF;
      while (it != s) {
        addflow = min(addflow,
            g[from[it]][from_edge[it]].cap
            - g[from[it]][from_edge[it]].flow);
        it = from[it];
      }
      it = t;
      while (it != s) {
        g[from[it]][from_edge[it]].flow += addflow;
        g[it][g[from[it]][from_edge[it]].backEdge].flow -= addflow;
        cost += g[from[it]][from_edge[it]].cost * addflow;
        it = from[it];
      }
      flow += addflow;
    }
    return {cost,flow};
  }
};

// PushRelabel O(V^2*root(E))

struct edge
{
    int from, to, cap, flow, index;
    edge(int from, int to, int cap, int flow, int index):
        from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct PushRelabel
{
    static const long long INF=1e18;

    int n;
    vector<vector<edge> > g;
    vector<long long> excess;
    vector<int> height;

    PushRelabel(int n):
        n(n), g(n), excess(n), height(n) {}

    void addEdge(int from, int to, int cap)
    {
        g[from].push_back(edge(from, to, cap, 0, g[to].size()));
        if(from==to)
            g[from].back().index++;
        g[to].push_back(edge(to, from, 0, 0, g[from].size()-1));
    }

    void push(edge &e)
    {
        int amt=(int)min(excess[e.from], (long long)e.cap - e.flow);
        if(height[e.from]<=height[e.to] || amt==0)
            return;
        e.flow += amt;
        g[e.to][e.index].flow -= amt;
        excess[e.to] += amt;
        excess[e.from] -= amt;
    }

    void relabel(int u)
    {
        int d=2e5;
        for(auto &it:g[u])
        {
            if(it.cap-it.flow>0)
                d=min(d, height[it.to]);
        }
        if(d<INF)
            height[u]=d+1;
    }

    vector<int> find_max_height_vertices(int source, int dest)
    {
        vector<int> max_height;
        for(int i=0;i<n;i++)
        {
            if(i!=source && i!=dest && excess[i]>0)
            {
                if(!max_height.empty() && height[i] > height[max_height[0]])
                    max_height.clear();
                if(max_height.empty() || height[i] == height[max_height[0]])
                    max_height.push_back(i);
            }
        }
        return max_height;
    }

    long long max_flow(int source, int dest)
    {
        excess.assign(n, 0);
        height.assign(n, 0);
        height[source]=n;
        excess[source]=INF;
        for(auto &it:g[source])
            push(it);

        vector<int> current;
        while(!(current = find_max_height_vertices(source, dest)).empty())
        {
            for(auto i:current)
            {
                bool pushed=false;
                for(auto &e:g[i])
                {
                    if(excess[i]==0)
                        break;
                    if(e.cap - e.flow>0 && height[e.from] == height[e.to] + 1)
                    {
                        push(e);
                        pushed=true;
                    }
                }
                if(!pushed)
                {
                    relabel(i);
                    break;
                }
            }
        }

        long long max_flow=0;
        for(auto &e:g[source])
            max_flow+=e.flow;

        return max_flow;
    }
};
