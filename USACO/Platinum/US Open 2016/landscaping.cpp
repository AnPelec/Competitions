/**
    Angelos Pelecanos
    USACO US OPEN 2016
    Platinum Division
    Problem Landscaping
**/

#include <bits/stdc++.h>
#define INF 2000000000

#define MAXN 5510

using namespace std;

typedef long long ll;

ifstream fin("landscape.in");
ofstream fout("landscape.out");

int N;
int A[MAXN], B[MAXN], nA, nB;
ll dp[MAXN][MAXN], X, Y, Z;

int main()
{
    fin >> N >> X >> Y >> Z;
    for (int i=0; i<N; i++) {
        int tmp;
        fin >> tmp; while (tmp>0) { A[++nA] = i; tmp--; }
        fin >> tmp; while (tmp>0) { B[++nB] = i; tmp--; }
    }

    for (int i=0; i<=nB; i++) dp[0][i] = i*X;
    for (int i=0; i<=nA; i++) dp[i][0] = i*Y;

    for (int i=1; i<=nA; i++)
        for (int j=1; j<=nB; j++) {
            dp[i][j] = 1000000000000000LL;
            dp[i][j] = min(dp[i][j], dp[i][j-1] + X);
            dp[i][j] = min(dp[i][j], dp[i-1][j] + Y);
            dp[i][j] = min(dp[i][j], dp[i-1][j-1] + Z * abs(A[i]-B[j]));
        }

    fout << dp[nA][nB] << endl;
    return 0;
}
