// Solution obtains 50% of the points because of TLE verdict (Time Limit Exceeded)
// It is using the CCW test to check if point is in triangle
// Complexity is O(N^3)

#include <bits/stdc++.h>
#include <stdio.h>

#define MAXN 305

using namespace std;

typedef long long ll;
typedef pair < int, int > ii;
typedef pair < ll, ll > llll;

int N;
ii tree[MAXN];
int answer[MAXN];

inline bool ccw(ii A, ii B, ii C) {
    return ((ll)(B.first-A.first)*(ll)(C.second-A.second) - (ll)(B.second-A.second)*(ll)(C.first-A.first)) > 0LL;
}

inline bool isInsideTriangle(ii A, ii B, ii C, ii P) {
    return (ccw(A, B, P) == ccw(B, C, P)) && (ccw(A, B, P) == ccw(C, A, P));
}

int main()
{
    ifstream fin("triangles.in");
    ofstream fout("triangles.out");

    fin >> N;

    for (int i=0; i<N; i++)
        fin >> tree[i].first >> tree[i].second;

    for (int i=0; i<N; i++) {
        for (int j=i+1; j<N; j++) {
            for (int k=j+1; k<N; k++) {
                int pointsInside = 0;
                for (int c=0; c<N; c++)  if (c != i && c != j && c != k) {
                    if (isInsideTriangle(tree[i], tree[j], tree[k], tree[c]))
                        ++pointsInside;
                }
                ++ answer[pointsInside];
            }
        }
    }

    for (int i=0; i<=N-3; i++)
        fout << answer[i] << "\n";


    return 0;
}
