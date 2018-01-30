#include <bits/stdc++.h>

#define MAXN 1111
#define MAXK 8

using namespace std;

typedef long long ll;

int N, K;
int r[MAXN];
int rr[2*MAXN];
ll cumSum[2*MAXN];
ll dp[MAXK][MAXN];

ll sum(int start, int stop) {
    if (start < 0) start += N;
    if (stop < 0) stop += N;
    if (start > stop) stop += N;
    return cumSum[stop] - (start == 0 ? 0LL : cumSum[start-1]);
}

ll solve(int firstDoor) {
    dp[K-1][N-1] = 0LL;
    for (int i=0; i<firstDoor; i++)
        dp[K-1][N-1] += (ll)(i+1)*(ll)r[i];
    for (int i=N-2; i>=firstDoor+K-1; i--)
        dp[K-1][i] = dp[K-1][i+1] + sum(i+1, firstDoor-1);
    for (int i=firstDoor+K-2; i>=0; i--)
        dp[K-1][i] = 1000000000000LL;

    for (int i=0; i<K-1; i++)
        for (int j=0; j<N; j++)
        dp[i][j] = 1000000000000LL;

    for (int doors=K-2; doors>=0; doors--) {
        for (int room=N+doors-K; room>=firstDoor+doors; room--) {
            //cout << doors << " room: " << room << endl;
            ll temp = 0LL;
            dp[doors][room] = 1000000000LL;
            dp[doors][room] = dp[doors+1][room+1]; /// next room has door
            for (int next=room+2; next<N; next++) {
                temp += (ll)(next-room-1)*(ll)(r[next-1]);
                dp[doors][room] = min(dp[doors][room], dp[doors+1][next] + temp);
            }
        }
    }

    /*for (int i=0; i<K; i++)
        for (int j=0; j<N; j++)
            cout << dp[i][j] << " \n"[j == N-1];*/


    return dp[0][firstDoor];
}

int main()
{
    ifstream fin("cbarn.in");
    ofstream fout("cbarn.out");
    /// N = K
    fin >> N >> K;
    for (int i=0; i<N; i++)
        fin >> r[i];

    for (int i=0; i<2*N; i++)
        rr[i] = (ll)r[i%N];

    cumSum[0] = (ll)rr[0];
    for (int i=1; i<2*N; i++)
        cumSum[i] = cumSum[i-1] + (ll)rr[i];

    ll bestValue = solve(0);
    for (int i=1; i<=N-K; i++)
        bestValue = min(bestValue, solve(i));

    fout << bestValue << endl;

    return 0;
}
