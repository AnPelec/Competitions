/**
    Angelos Pelecanos
    USACO US OPEN 2016
    Platinum Division
    Problem 262144
**/

#include <bits/stdc++.h>

#define MAXN 270000
#define MAXH 60

using namespace std;

typedef long long ll;

ifstream fin("262144.in");
ofstream fout("262144.out");

int N;
int A[MAXN];
int best[MAXH][MAXN];
int maxAns;

int main()
{
    fin >> N;

    for (int i=0; i<N; i++) {
        fin >> A[i];
        best[A[i]][i] = 1;
        maxAns = max(maxAns, A[i]);
    }

    for (int i=2; i<MAXH; i++) {
        for (int j=0; j<N; j++) {
            if (best[i-1][j] == 0) continue;
            if (best[i-1][j+best[i-1][j]] == 0) continue;
            best[i][j] = best[i-1][j] + best[i-1][j+best[i-1][j]];
            maxAns = max(maxAns, i);
        }
    }

    fout << maxAns << endl;

    return 0;
}
