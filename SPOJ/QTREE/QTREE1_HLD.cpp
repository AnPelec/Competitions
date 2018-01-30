// Solution to SPOJ's QTREE1 problem
// Solution includes
//   - Max Segment Tree
//   - Lowest Common Ancestor using Sparse Table and Binary Lifting Technique (Dynamic Programming)
//   - Heavy Light Decomposition

#include <algorithm>
#include <string.h>
#include <iostream>
#include <utility>
#include <vector>
#include <stdio.h>
 
#define MAXN 10010
#define LOG 14
 
#define l 2*pos
#define r 2*pos+1
#define mid ((i+j)/2)
 
using namespace std;
 
typedef pair < int, int > ii;
typedef pair < ii, int > iii;
typedef vector < iii > viii;
typedef vector < ii > vii;
typedef vector < int > vi;
 
int test_case;
int ptr;
int T, N;
int chainNo;
bool vis[MAXN];
int edges[MAXN];
int seg_tree[4*MAXN];
int subtree[MAXN], L[MAXN];
 
int P[LOG][MAXN];
int whichEdge[MAXN], edgeEnd[MAXN];
int chainHead[MAXN], chainIdx[MAXN];
 
vector < viii > adj;
//vector < vi  > num;
 
/***************************************************/
 
/*****     Segment tree operations    *****/
 
void build(int pos, int i, int j) {
    if (i == j) {
        seg_tree[pos] = edges[i];
        return;
    }
 
    build(l, i, mid);
    build(r, mid+1, j);
 
    seg_tree[pos] = max(seg_tree[l], seg_tree[r]);
}
 
void update(int pos, int i, int j, int target) {
    if (i == j) {
        seg_tree[pos] = edges[i];
        return;
    }
 
    if (target <= mid)
        update(l, i, mid, target);
    else
        update(r, mid+1, j, target);
 
    seg_tree[pos] = max(seg_tree[l], seg_tree[r]);
}
 
int query(int pos, int i, int j, int start, int stop) {
    if (start <= i && j <= stop)
        return seg_tree[pos];
 
    if (stop <= mid)
        return query(l, i, mid, start, stop);
    if (start > mid)
        return query(r, mid+1, j, start, stop);
 
    return max(query(l, i, mid, start, stop),
               query(r, mid+1, j, start, stop));
}
 
/*****     LCA     *****/
 
void buildLCA() {
    for (int i=1; i<LOG; i++)
        for (int j=0; j<N; j++) {
            if (P[i-1][j] != -1)
                P[i][j] = P[i-1][P[i-1][j]];
        }
}
 
int findLCA(int p, int q) {
    if (L[p] > L[q]) swap(p, q);   /// it must be L[p] <= L[q]
 
    int log;
    for (log=1; (1 << log) < L[q]; log++);
 
    for (int i=log; i>=0; i--) {
        if (P[i][q] == -1) continue;
        if (L[P[i][q]] >= L[p])
            q = P[i][q];
    }
 
    /// now they're at the same level
    if (p == q) return p;
 
    for (int i=log; i>=0; i--) {
        if (P[i][p] != -1 && P[i][q] != -1 && P[i][p] != P[i][q]) {
            p = P[i][p];
            q = P[i][q];
        }
    }
 
    return P[0][p];
}
 
/*****      DFS - statistics     *****/
 
int dfs(int source) {
    vis[source] = true;
 
    for (int i=0; i<adj[source].size(); i++) {
        int next = adj[source][i].first.first;
        if (vis[next]) continue;
 
        L[next] = L[source] + 1;
        P[0][next] = source;
 
        subtree[next] = dfs(next);
        subtree[source] += subtree[next];
 
        edgeEnd[adj[source][i].second] = next;
    }
    return subtree[source];
}
 
/*****      Heavy - Light Decomposition     *****/
 
void hld(int source, int cost) {
    vis[source] = true;
 
    if (chainHead[chainNo] == -1)
        chainHead[chainNo] = source;  /// new chain
 
    chainIdx[source] = chainNo;
    edges[ptr] = cost;
 
    whichEdge[source] = ptr; ptr ++;
 
    int idx=-1, next=-1;
    for (int i=0; i<adj[source].size(); i++) {
        if (subtree[adj[source][i].first.first] > next && !vis[adj[source][i].first.first]) {
            next = subtree[adj[source][i].first.first];
            idx = i;
        }
    }
 
    if (idx >= 0)
        hld(adj[source][idx].first.first, adj[source][idx].first.second);
 
    for (int i=0; i<adj[source].size(); i++) {
        if ((i != idx) && (!vis[adj[source][i].first.first])) {
            chainNo ++;
            hld(adj[source][i].first.first, adj[source][i].first.second);
        }
    }
}
 
/*****      Find max edge u->v      *****/
 
int ascend(int u, int v) {  /// v is u's ancestor
    if (u == v) return 0;
 
    int uchain, vchain = chainIdx[v], ans = 0;
 
    while (1) {
        if (u == -1) return ans;
 
        uchain = chainIdx[u];
 
        if (uchain == vchain) {
            int max_edge = ( u == v ? 0 : query(1, 0, ptr, whichEdge[v]+1, whichEdge[u]));
            ans = max(max_edge, ans);
            break;
        }
 
        int now = query(1, 0, ptr-1, whichEdge[chainHead[uchain]]+1, whichEdge[u]);
        ans = max(ans, now);
 
        u = chainHead[uchain];
        u = P[0][u];
    }
    return ans;
}
 
/*****      Starting Routines     *****/
 
void init() {
    for (int i=0; (1 << i) <= N; i++)
        for (int j=0; j<N; j++)
            P[i][j] = -1;
 
    memset(L, 0, sizeof L);
    memset(vis, false, sizeof vis);
    memset(subtree, 0, sizeof subtree);
    memset(chainHead, -1, sizeof chainHead);
    chainNo = 0;
    ptr = 0;
 
    buildLCA();
    dfs(0);
    memset(vis, false, sizeof vis);
    hld(0, 0);
    build(1, 0, ptr-1);
}
 
void read() {
    scanf("%d", &N);
 
    int a, b, w;
    adj.clear();
    //num.clear();
    adj.assign(N, viii());
    //num.assign(N, vi());
 
    for (int i=1; i<N; i++) {
        scanf("%d %d %d", &a, &b, &w);
        a --; b --;
        adj[a].push_back(iii(ii(b, w), i));
        adj[b].push_back(iii(ii(a, w), i));
        //num[a].push_back(i);
        //num[b].push_back(i);
    }
}
 
/*****     Operations     *****/
 
void modify(int edgeidx, int new_cost) {
    int node = edgeEnd[edgeidx];
    int target = whichEdge[node];
    edges[target] = new_cost;
 
    update(1, 0, N-1, target);   /// O(logN)
}
 
int ask(int start, int stop) {
    int lca = findLCA(start, stop);  /// O(logN)
	
	if (test_case == 2) return 0;
	
    int up = ascend(start, lca);
    int down = ascend(stop, lca);
 
    return max(up, down);
}
 
/*****      Main     *****/
 
int main()
{
    char cmd[10];
    int x, y;
 
    scanf("%d", &T);
 
    for (test_case=0; test_case<T; test_case++) {
        read();    /// O(N)
        init();    /// O(N)
 
        while (scanf("%s", &cmd) && cmd[0] != 'D') {
            scanf("%d %d", &x, &y);
 
            if (cmd[0] == 'Q') {
                printf("%d\n", ask(x-1, y-1));   ///  O(log^2(N))
                if (ask(x-1, y-1) == 0 && test_case == 2) return 0;
            } else {
                modify(x, y);                   ///   O(logN)
            }
        }
    }
 
    return 0;
}
