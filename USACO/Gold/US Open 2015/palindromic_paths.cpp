#include <algorithm>
#include <string.h>
#include <iostream>
#include <utility>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <cstdio>
#include <math.h>
#include <stack>
#include <cmath>
#include <map>
#include <set>

//#define SEGMENT_TREE 0

#ifdef SEGMENT_TREE
    #define l 2*pos
    #define r 2*pos+1
    #define mid (i+j)/2
#endif // SEGMENT_TREE

#define MAXN 510
#define MOD 1000000007
#define INF 1000000000 /// 1B

#define cin fin
#define cout fout

using namespace std;

ifstream fin("palpath.in");
ofstream fout("palpath.out");

typedef long long ll;
typedef vector < int > vi;
typedef pair < int, int > ii;

int N;
char grid[MAXN][MAXN];
ll dp[2][MAXN][MAXN];

int main()
{
    cin >> N;

    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            cin >> grid[i][j];

    for (int i=0; i<N; i++)
        dp[(N-1)%2][i][N-i-1] = 1LL;

    for (int diag=N-2; diag>=0; diag--) {
        for (int i=0; i<=diag; i++)             /// this can be improved
            for (int j=0; j<=diag; j++) {
                int x1, x2;             /// y1 = i, y2 = N-j-1
                x1 = diag-i;
                x2 = diag-j; x2 = N-x2-1;

                ll ans = 0;
                if ((grid[x1][i] == grid[x2][N-j-1]) && (x1 <= x2) && (i <= N-j-1)) {
                    //cout << "processing: " << x1 << " " << i << "  versus  " << x2 << " " << N-j-1 << endl;
                    ans = (ans + dp[(diag+1)%2][i][j])%MOD;

                    ans = (ans + dp[(diag+1)%2][i][j+1])%MOD;

                    ans = (ans + dp[(diag+1)%2][i+1][j])%MOD;

                    ans = (ans + dp[(diag+1)%2][i+1][j+1])%MOD;
                    //cout << "ans is: " << ans << endl;
                }
                dp[diag%2][i][j] = ans;
            }
    }

    cout << dp[0][0][0] << endl;


    return 0;
}
