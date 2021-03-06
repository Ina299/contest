#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#define REP(i,s,n) for(int i=(int)(s);i<(int)(n);i++)

using namespace std;
typedef long long int ll;
typedef vector<int> VI;
typedef pair<int, int> PI;
const double EPS=1e-9;

class Dinic {
private:
  struct edge {
    int to, cap, rev; // rev is the position of reverse edge in graph[to]
  };
  std::vector<std::vector<edge> > graph;
  std::vector<int> level;
  std::vector<int> iter;
  /* Perform bfs and calculate distance from s */
  void bfs(int s) {
    level.assign(level.size(), -1);
    std::queue<int> que;
    level[s] = 0;
    que.push(s);
    while (! que.empty()) {
      int v = que.front(); que.pop();
      for (int i = 0; i < graph[v].size(); ++i) {
	edge &e = graph[v][i];
	if (e.cap > 0 && level[e.to] == -1) {
	  level[e.to] = level[v] + 1;
	  que.push(e.to);
	}
      }
    }
  }
  /* search augment path by dfs.
   if f == -1, f is treated as infinity. */
  int dfs(int v, int t, int f) {
    if (v == t) {
      return f;
    }
    for (int &i = iter[v]; i < graph[v].size(); ++i) {
      edge &e = graph[v][i];
      if (e.cap > 0 && level[v] < level[e.to]) {
	int newf = f == -1 ? e.cap : std::min(f, e.cap);
	int d = dfs(e.to, t, newf);
	if (d > 0) {
	  e.cap -= d;
	  graph[e.to][e.rev].cap += d;
	  return d;
	}
      }
    }
    return 0;
  }
public:
  /* v is the number of vertices (labeled from 0 .. v-1) */
  Dinic(int v) : graph(v), level(v, -1), iter(v, 0) {}
  void add_edge(int from, int to, int cap) {
    graph[from].push_back((edge) {to, cap, graph[to].size()});
    graph[to].push_back((edge) {from, 0, graph[from].size() - 1});
  }
  int max_flow(int s, int t) {
    int flow = 0;
    while (1) {
      bfs(s);
      if (level[t] < 0) {
	return flow;
      }
      iter.assign(iter.size(), 0);
      int f;
      while ((f = dfs(s, t, -1)) > 0) {
	flow += f;
      }
    }
  }
};


int main(void){
  int n;
  cin >> n;
  const int inf = 0x100000;
  Dinic din(2 * n + 2);
  int sum = 0;
  REP(i, 0, n) {
    int b, c;
    cin >> b >> c;
    din.add_edge(0, 2 + i, c);
    din.add_edge(2 + n + i, 1, b);
    din.add_edge(2 + i, 2 + n + i, inf);
    sum += b + c;
  }
  int m;
  cin >> m;
  REP(i, 0, m) {
    int d, e;
    cin >> d >> e;
    din.add_edge(2 + e, 2 + n + d, inf);
  }
  cout << sum - din.max_flow(0, 1) << endl;
}
