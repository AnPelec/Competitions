/// SOLUTION USES 4D DYNAMIC PROGRAMMING

#include <bits/stdc++.h>

#define MAXN 52

using namespace std;

ifstream fin("subrev.in");
ofstream fout("subrev.out");

int N;
int A[MAXN];
int dp[MAXN][MAXN][MAXN][MAXN];  /// start idx, stop idx, start value, stop value

int Solve(int start, int stop, int minval, int maxval) {
    if (start > stop) return 0;
    if (minval > maxval) return 0;
    if (start == stop)
        return (minval <= A[start] && A[stop] <= maxval);

    if (dp[start][stop][minval][maxval] != -1)
        return dp[start][stop][minval][maxval];

    int result = 0;
    result = max(result, Solve(start+1, stop, minval, maxval));
    result = max(result, Solve(start, stop-1, minval, maxval));
    //result = max(result, Solve(start, stop, minval+1, maxval));
    //result = max(result, Solve(start, stop, minval, maxval-1));

    if (minval <= A[start] && A[start] <= maxval) {
        result = max(result, Solve(start+1, stop, A[start], maxval)+1);
        result = max(result, Solve(start+1, stop-1, minval, A[start])+1);
    }
    if (minval <= A[stop] && A[stop] <= maxval) {
        result = max(result, Solve(start, stop-1, minval, A[stop])+1);
        result = max(result, Solve(start+1, stop-1, A[stop], maxval)+1);
    }


    if (A[start] > A[stop] &&
        minval <= A[start] && A[start] <= maxval &&
        minval <= A[stop] && A[stop] <= maxval)
        result = max(result, Solve(start+1, stop-1, A[stop], A[start])+2);

    dp[start][stop][minval][maxval] = result;

    return result;
}

int main()
{
    fin >> N;

    for (int i=0; i<N; i++) {
        fin >> A[i];
    }

    for (int i=0; i<MAXN; i++) for (int j=0; j<MAXN; j++) {
        for (int c=0; c<MAXN; c++) for (int k=0; k<MAXN; k++) {
            dp[i][j][k][c] = -1;
        }
    }

    fout << Solve(0, N-1, 1, 50) << endl;

    return 0;
}
