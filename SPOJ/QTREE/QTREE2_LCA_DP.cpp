// Solution to QTREE2
// Solution uses Lowest Common Ancestor (LCA) by the Binary Lifting Technique (Dynamic Programming)
// Total Complexity is O(NlogN)

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define MAXN 10005
#define LOGMAXN 14

using namespace std;

/**
    Solution of Query on Tree II
    Using Dynamic Programming and Divide and Conquer
    (Sparse Table and Binary Search)
**/

typedef pair < int, int > ii;
typedef vector < ii > vii;

int N;
bool v[MAXN];
int P[MAXN][LOGMAXN];
int T[MAXN], D[MAXN], L[MAXN];

vector < vii > adj;

void Read() {
    cin >> N;

    int a, b, w;

    for (int i=1; i<N; i++) {
        cin >> a >> b >> w;
        a --;
        b --;
        adj[a].push_back(ii(b, w));
        adj[b].push_back(ii(a, w));
    }
}

void dfs(int source) {
    v[source] = true;

    for (int i=0; i<adj[source].size(); i++)
        if (!v[adj[source][i].first]) {
            T[adj[source][i].first] = source;
            L[adj[source][i].first] = L[source] + 1;
            D[adj[source][i].first] = D[source] + adj[source][i].second;
            dfs(adj[source][i].first);
        }
}

void sparse_table() {
    for (int i = 0; i < N; i++)
        for (int j = 0; (1 << j) < N; j++)
            P[i][j] = -1;

    for (int i = 0; i < N; i++)
        P[i][0] = T[i];

    for (int j = 1; 1 << j < N; j++)
        for (int i = 0; i < N; i++)
            if (P[i][j - 1] != -1)
                P[i][j] = P[P[i][j - 1]][j - 1];
}

int query(int p, int q) {
    int tmp, log, i;

    if (L[p] < L[q])
        swap(p, q);

    for (log = 1; 1 << log <= L[p]; log++); log--;

    for (i = log; i >= 0; i--)
        if (L[p] - (1 << i) >= L[q])
            p = P[p][i];

    if (p == q)
        return p;

    for (i = log; i >= 0; i--)
        if (P[p][i] != -1 && P[p][i] != P[q][i])
            p = P[p][i], q = P[q][i];

    return T[p];
}

int kth(int start, int stop, int k) {
    int lca = query(start, stop);
    int nodes = L[start] + L[stop] -2*L[lca] + 1;

    if (k > L[start] - L[lca] + 1) { /// second half
        k = nodes - k + 1;
        swap(start, stop);
    }
    k --;

    int retVal = start, log;

    for (log = 1; (1 << log) <= L[start]; log++);

    for (int i=log; i>=0; i--)
        if (k >= (1 << i)) {
            k -= (1 << i);
            retVal = P[retVal][i];
        }

    return retVal+1;
}

void solution() {
    int a, b, k;
    string command;

    while (cin >> command && command != "DONE") {
        if (command == "DIST") {
            cin >> a >> b;
            a --;
            b --;
            int lca = query(a, b);
            cout << (D[a] + D[b] - 2*D[lca]) << endl;
        }

        else {
            cin >> a >> b >> k;
            a --;
            b --;
            cout << kth(a, b, k) << endl;
        }
    }
}

void Finish() {
    for (int i=0; i<adj.size(); i++)
        adj[i].clear();
}

int main()
{
    int testcases;

    cin >> testcases;

    adj.assign(MAXN, vii());

    while (testcases --) {
        Read();

        for (int i=0; i<MAXN; i++) v[i] = false;

        T[0] = -1;
        L[0] = 0;
        D[0] = 0;
        dfs(0);

        sparse_table();

        solution();

        Finish();

        cout << endl;
    }


    return 0;
}

