#include <bits/stdc++.h>

#define MAXT 5000010

using namespace std;

typedef pair < int, int > ii;

int T, A, B;
bool vis[2][MAXT];
queue < ii > Q;

bool isOK(int val, int b) {
    if (val < 0 || val > T) return false;
    return (!vis[b][val]);
}

void Solve() {
    Q.push(ii(0, 0));

    while (!Q.empty()) {
        ii now = Q.front();
        Q.pop();

        if (!isOK(now.first, now.second)) continue;
        vis[now.second][now.first] = true;
        if (isOK(now.first+A, now.second)) Q.push(ii(now.first+A, now.second));
        if (isOK(now.first+B, now.second)) Q.push(ii(now.first+B, now.second));
        if (now.second == 0 && isOK(now.first/2, now.second)) Q.push(ii(now.first/2, 1));
    }
}

int main()
{
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);

    scanf("%d %d %d", &T, &A, &B);

    Solve();

    for (int i=T; i>=0; i--) {
        if (vis[0][i] || vis[1][i]) {
            printf("%d\n", i);
            break;
        }
    }

    return 0;
}
