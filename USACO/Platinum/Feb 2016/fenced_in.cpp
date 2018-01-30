#include <bits/stdc++.h>

#define MAXN 25010
#define MAXnodes 10000010

using namespace std;

typedef long long ll;
typedef pair < int, int > ii;
typedef pair < int, ii > iii;

int A, B, N, M;
int v[MAXN], h[MAXN];
int pre[MAXnodes];
int rr[MAXnodes];
ll cost;
vector < iii > edges;

int id(int i, int j) {
    return (i-1)*(M+1)+j-1;
}

int find_pre(int x) {
    if (pre[x] == x) return x;
    return pre[x] = find_pre(pre[x]);
}

void add(int x, int y) {
    int PX = find_pre(x);
    int PY = find_pre(y);

    if (rr[PX] < rr[PY])
        pre[PX] = PY;
    else
        pre[PY] = PX;
    if (rr[PX] == rr[PY])
        rr[PX] ++;
}

int main()
{
    ifstream fin("fencedin.in");
    ofstream fout("fencedin.out");

    fin >> A >> B >> N >> M;
    for (int i=1; i<=N; i++)
        fin >> v[i];
    for (int i=1; i<=M; i++)
        fin >> h[i];

    sort(v+1, v+N+1);
    sort(h+1, h+M+1);
    v[N+1] = A;
    h[M+1] = B;

    for (int i=1; i<=N+1; i++)
        for (int j=1; j<=M+1; j++) {
            int node = id(i, j);
            pre[node] = node;
            int next;
            if (i != N) {
                next = id(i+1, j);
                edges.push_back(iii(h[j]-h[j-1], ii(node, next)));
            }
            if (j != M) {
                next = id(i, j+1);
                edges.push_back(iii(v[i]-v[i-1], ii(node, next)));
            }
        }

    sort(edges.begin(), edges.end());

    int mst = 0;
    for (int i=0; i<edges.size(); i++) {
        if (find_pre(edges[i].second.first) != find_pre(edges[i].second.second)) {
            add(edges[i].second.first, edges[i].second.second);
            cost += edges[i].first;
            mst ++;
        }

        if (mst+1 == (N+1)*(M+1)) break;
    }

    fout << cost << endl;

    return 0;
}
