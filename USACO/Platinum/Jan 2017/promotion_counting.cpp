/// Solution uses Binary Indexed Tree (BIT) for fast updates and queries to array

#include <bits/stdc++.h>

#define MAXN 100010

using namespace std;

ifstream fin("promote.in");
ofstream fout("promote.out");

typedef vector < int > vi;
typedef pair < int, int > ii;

int N;
int pre, global;
int val[MAXN];
int BIT[MAXN];
int start[MAXN], stop[MAXN];
vector < vi > adj;
vector < ii > input;
int answer[MAXN];

void dfs(int source) {
    start[source] = global;
    ++ global;

    for (int i=0; i<adj[source].size(); ++i)
        dfs(adj[source][i]);

    stop[source] = global - 1;
}

void update(int x) {
    while (x < MAXN) {
        BIT[x] ++;
        x += x&(-x);
    }
}

int query(int x) {
    int retVal = 0;
    while (x > 0) {
        retVal += BIT[x];
        x -= x&(-x);
    }
    return retVal;
}

int main()
{
    fin >> N;

    for (int i=0; i<N; i++) {
        fin >> val[i];
        input.push_back(ii(val[i], i));
    }

    adj.assign(N, vi());
    for (int i=1; i<N; i++) {
        fin >> pre;
        adj[pre-1].push_back(i);
    }

    global = 1;

    dfs(0);

    sort(input.begin(), input.end());
    for (int i=N-1; i>=0; --i) {
        int now = input[i].second;
        answer[now] = query(stop[now])-query(start[now]-1);
        update(start[now]);
    }

    for (int i=0; i<N; i++)
        fout << answer[i] << endl;

    return 0;
}
