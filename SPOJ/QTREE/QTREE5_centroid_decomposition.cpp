/*
  Solution to QTREE5 from SPOJ
  Solution is using Centroid Decomposition of Tree
  and Lowest Common Ancestor (Sparse Table/DP)
*/

#include <bits/stdc++.h>
 
#define MAXN 100010
#define LOG 17
 
using namespace std;
 
typedef vector < int > vi;
 
int N, Q;
bool isWhite[MAXN];
multiset < int > ans[MAXN];
 
vi adj[MAXN];
 
/// for LCA
int L[MAXN];
int P[LOG][MAXN];
 
/// for centroid
int totalSub;
int sub[MAXN];
int parent[MAXN];
bool inactive[MAXN];
 
int minDistance;
 
int findSub(int node, int pre) {
    if (inactive[node])
        sub[node] = 0;
    else {
        sub[node] = 1;
        for (int i=0; i<adj[node].size(); i++) if (adj[node][i] != pre)
            sub[node] += findSub(adj[node][i], node);
    }
    return sub[node];
}
 
int findBestVert(int node, int pre) {
    if (inactive[node]) return -1;
 
    int maxSub;
    if (pre == -1) maxSub = 0;
    else maxSub = totalSub - sub[node];
 
    for (int i=0; i<adj[node].size(); i++) if (adj[node][i] != pre)
        maxSub = max(maxSub, sub[adj[node][i]]);
 
    if (2*maxSub <= totalSub) return node;
 
    for (int i=0; i<adj[node].size(); i++) if (adj[node][i] != pre) {
        int temp = findBestVert(adj[node][i], node);
        if (temp != -1) return temp;
    }
    return -1;
}
 
int getCentroid(int node) {
    totalSub = findSub(node, -1);
    return findBestVert(node, -1);
}
 
void process(int node) {
    inactive[node] = true;
    for (int i=0; i<adj[node].size(); i++)
        if (!inactive[adj[node][i]]) {
            int next = getCentroid(adj[node][i]);
            parent[next] = node;
            process(next);
        }
}
 
void dfs(int node, int pre) {
    for (int i=0; i<adj[node].size(); i++) if (adj[node][i] != pre) {
        L[adj[node][i]] = L[node]+1;
        P[0][adj[node][i]] = node;
        dfs(adj[node][i], node);
    }
}
 
void prepare() {
    L[0] = 0;
    P[0][0] = -1;
    dfs(0, -1);
 
    for (int i=1; i<LOG; i++) {
        for (int j=0; j<N; j++) {
            if (P[i-1][j] == -1) P[i][j] = -1;
            else P[i][j] = P[i-1][P[i-1][j]];
        }
    }
}
 
int lca(int u, int v) {
    if (L[u] > L[v]) swap(u, v);
 
    for (int i=LOG-1; i>=0; i--)
        if (P[i][v] != -1 && L[v]-(1 << i) >= L[u])
            v = P[i][v];
 
    if (u == v) return u;
 
    for (int i=LOG-1; i>=0; i--)
        if (P[i][u] != -1 && P[i][v] != -1 && P[i][u] != P[i][v]) {
            u = P[i][u];
            v = P[i][v];
        }
    if (P[0][u] != -1) return P[0][u];
}
 
int dist(int u, int v) {
    return L[u] + L[v] - 2*L[lca(u, v)];
}
 
int cost(int u) {
    if (ans[u].empty()) return N+2;
    return *(ans[u].begin());
}
 
int main()
{
    int u, v, cmd, now;
    scanf("%d", &N);
 
    for (int i=1; i<N; i++) {
        scanf("%d %d", &u, &v);
        adj[--u].push_back(--v);
        adj[v].push_back(u);
    }
 
    /// build centroid
    int start = getCentroid(0);
    parent[start] = -1;
    process(start);
 
    /// build lca array
    prepare();
 
    scanf("%d", &Q);
 
    for (int i=0; i<Q; i++) {
        scanf("%d %d", &cmd, &now);
        now --;
 
        if (cmd == 0) {
            int temp = now;
            while (temp >= 0) {
                if (isWhite[now]) ans[temp].erase(ans[temp].find(dist(now, temp)));
                else ans[temp].insert(dist(now, temp));
                temp = parent[temp];
            }
            isWhite[now] = !isWhite[now];
        }
 
        else {
            minDistance = N+2;
            int temp = now;
            while (temp >= 0) {
                minDistance = min(minDistance, dist(now, temp) + cost(temp));
                temp = parent[temp];
            }
            if (minDistance > N) minDistance = -1;
            printf("%d\n", minDistance);
        }
    }
 
    return 0;
}
