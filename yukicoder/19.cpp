#include <algorithm>
#include <cassert>
#include <set>
#include <vector>

/**
 * Strong connected components.
 * Header requirement: algorithm, cassert, set, vector
 * Verified by: AtCoder ARC010 (http://arc010.contest.atcoder.jp/submissions/1015294)
 *              yukicoder No. 19 (http://yukicoder.me/submissions/141513)
 */
class SCC {
private:
  int n;
  int ncc;
  typedef std::vector<int> vi;
  std::vector<vi> g; // graph in adjacent list
  std::vector<vi> rg; // reverse graph
  vi vs;
  std::vector<bool> used;
  vi cmp;
public:
  SCC(int n): n(n), ncc(-1), g(n), rg(n), vs(n), used(n), cmp(n) {}
  void add_edge(int from, int to) {
    g[from].push_back(to);
    rg[to].push_back(from);
  }
private:
  void dfs(int v) {
    used[v] = true;
    for (int i = 0; i < g[v].size(); ++i) {
      if (!used[g[v][i]]) { dfs(g[v][i]); }
    }
    vs.push_back(v);
  }
  void rdfs(int v, int k) {
    used[v] = true;
    cmp[v] = k;
    for (int i = 0; i < rg[v].size(); ++i) {
      if (!used[rg[v][i]]) { rdfs(rg[v][i], k); }
    }
  }
public:
  int scc() {
    std::fill(used.begin(), used.end(), 0);
    vs.clear();
    for (int v = 0; v < n; ++v) {
      if (!used[v]) { dfs(v); }
    }
    std::fill(used.begin(), used.end(), 0);
    int k = 0;
    for (int i = vs.size() - 1; i >= 0; --i) {
      if (!used[vs[i]]) { rdfs(vs[i], k++); }
    }
    return ncc = k;
  }
  std::vector<int> top_order() const {
    if (ncc == -1) assert(0);
    return cmp;
  }
  std::vector<std::vector<int> > scc_components(void) const {
    if (ncc == -1) assert(0);
    std::vector<std::vector<int> > ret(ncc);
    for (int i = 0; i < n; ++i) {
      ret[cmp[i]].push_back(i);
    }
    return ret;
  }
  /*
   * Returns a dag whose vertices are scc's, and whose edges are those of the original graph, in the adjacent-list format.
   */
  std::vector<std::vector<int> > dag() const {
    if (ncc == -1) {
      assert(0);
    }
    typedef std::set<int> si;
    std::vector<si> ret(ncc);
    for (int i = 0; i < g.size(); ++i) {
      for (int j = 0; j < g[i].size(); ++j) {
	int to = g[i][j];
	if (cmp[i] != cmp[to]) {
	  assert (cmp[i] < cmp[to]);
	  ret[cmp[i]].insert(cmp[to]);
	}
      }
    }
    std::vector<std::vector<int> > vret(ncc);
    for (int i = 0; i < ncc; ++i) {
      vret[i] = std::vector<int>(ret[i].begin(), ret[i].end());
    }
    return vret;
  }
  std::vector<std::vector<int> > rdag() const {
    if (ncc == -1) {
      assert(0);
    }
    typedef std::set<int> si;
    std::vector<si> ret(ncc);
    for (int i = 0; i < g.size(); ++i) {
      for (int j = 0; j < g[i].size(); ++j) {
	int to = g[i][j];
	if (cmp[i] != cmp[to]) {
	  assert (cmp[i] < cmp[to]);
	  ret[cmp[to]].insert(cmp[i]);
	}
      }
    }
    std::vector<std::vector<int> > vret(ncc);
    for (int i = 0; i < ncc; ++i) {
      vret[i] = std::vector<int>(ret[i].begin(), ret[i].end());
    }
    return vret;
  }
};
#include <iostream>


#define REP(i,s,n) for(int i=(int)(s);i<(int)(n);i++)

using namespace std;
typedef vector<int> VI;




int main(void){
  int n;
  cin >> n;
  int tot = 0;
  VI l(n), s(n);
  // SCC de naguru (Using SCC is too much for this problem!!)
  SCC scc(n);
  REP(i, 0, n) {
    cin >> l[i] >> s[i];
    s[i]--;
    tot += l[i];
    scc.add_edge(i, s[i]);
  }
  scc.scc();
  vector<VI> comps = scc.scc_components();
  // Get the minimum level for every cycle, and count it twice
  REP(i, 0, comps.size()) {
    if (comps[i].size() >= 2
	|| (comps[i].size() == 1 && s[comps[i][0]] == comps[i][0])) {
      int mi = 101;
      REP(j, 0, comps[i].size()) {
	mi = min(mi, l[comps[i][j]]);
      }
      tot += mi;
    }
  }
  printf("%.1f\n", tot / 2.0);
}
