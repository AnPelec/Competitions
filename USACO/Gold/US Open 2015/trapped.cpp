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

#define MAXN 100010
#define INF 1000000000 /// 1B

#define cin fin
#define cout fout

using namespace std;

ifstream fin("trapped.in");
ofstream fout("trapped.out");

typedef long long ll;
typedef vector < int > vi;
typedef pair < int, int > ii;

int N;
int ans;
ii bales[MAXN];

int main()
{
    cin >> N;

    for (int i=0; i<N; i++) {
        cin >> bales[i].second >> bales[i].first;
    }

    sort(bales, bales+N);

    int lIdx, rIdx;
    bool ok;
    for (int i=0; i<N-1; i++) {
        lIdx = i+1; rIdx = lIdx;

        while (lIdx > 0 && rIdx < N) {
            ok = false;
            while (bales[rIdx].first - bales[lIdx-1].first >= bales[rIdx].second+1) {
                rIdx ++;
                ok = true;
                if (rIdx == N)
                    break;
            }
            while (bales[rIdx].first - bales[lIdx-1].first >= bales[lIdx-1].second+1) {
                lIdx --;
                ok = true;
                if (lIdx == 0)
                    break;
            }
            if (!ok) break;
        }

        if (lIdx > 0 && rIdx < N)
            ans += bales[i+1].first - bales[i].first;
    }

    cout << ans << endl;

    return 0;
}
