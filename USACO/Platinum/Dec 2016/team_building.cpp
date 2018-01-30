// Solution is using 3 dimensional Dynamic Programming

#include <bits/stdc++.h>

#define MOD 1000000009
#define MAXN 1003
#define MAXK 11

using namespace std;

typedef long long ll;

int N, M, K;
int fj[MAXN], fp[MAXN];
ll dp[MAXN][MAXN][MAXK];

ifstream fin("team.in");
ofstream fout("team.out");

int main()
{
    fin >> N >> M >> K;

    for (int i=1; i<=N; i++)
        fin >> fj[i];
    for (int i=1; i<=M; i++)
        fin >> fp[i];

    sort(fj+1, fj+N+1);
    sort(fp+1, fp+M+1);

    for (int i=0; i<=N; i++)
        for (int j=0; j<=M; j++)
            dp[i][j][0] = 1LL;

    for (int k=1; k<=K; k++) {
        for (int i=1; i<=N; i++) {
            for (int j=1; j<=M; j++) {
                if (fj[i] > fp[j])
                    dp[i][j][k] = dp[i-1][j-1][k-1];
                dp[i][j][k] = (dp[i][j][k] + dp[i][j-1][k])%MOD;
            }
        }

        for (int j=1; j<=M; j++)
            for (int i=2; i<=N; i++)
                dp[i][j][k] = (dp[i][j][k] + dp[i-1][j][k])%MOD;
    }

    fout << dp[N][M][K]<< endl;

    return 0;
}
