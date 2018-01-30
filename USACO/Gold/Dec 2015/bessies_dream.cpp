#include <bits/stdc++.h>

#define MAXN 1111
#define MAXM 1111

using namespace std;

typedef pair < int, int > ii;

struct state{
    int x, y;
    int lastDir;
    bool smellOrange;
    bool wasOnPurple;
};

int N, M;
int vis[2][2][5][MAXN][MAXM];  /// initialize with -1
int grid[MAXN][MAXM];

queue < state > Q;

int di[] = {-1, 0, 1, 0};
int dj[] = {0, -1, 0, 1};

bool ok(int i, int j) {
    return (i > -1 && i < N && j > -1 && j < M);
}

void markVis(state yolo, state prev) {
    int x1 = yolo.smellOrange ? 1 : 0, _x1 = prev.smellOrange ? 1 : 0;
    int x2 = yolo.wasOnPurple ? 1 : 0, _x2 = prev.wasOnPurple ? 1 : 0;
    int dir = yolo.lastDir, _dir = prev.lastDir;
    int posx = yolo.x, _posx = prev.x;
    int posy = yolo.y, _posy = prev.y;
    vis[x1][x2][dir][posx][posy] = vis[_x1][_x2][_dir][_posx][_posy] + 1;
}

int valOfVis(state yolo) {
    int x1 = yolo.smellOrange ? 1 : 0;
    int x2 = yolo.wasOnPurple ? 1 : 0;
    int dir = yolo.lastDir;
    int posx = yolo.x;
    int posy = yolo.y;
    return vis[x1][x2][dir][posx][posy];
}

void print(state yolo) {
    cout << yolo.x << " " << yolo.y << endl;
}

void bfs() {
    state now;
    now.x = 0;
    now.y = 0;
    now.lastDir = 4;
    now.wasOnPurple = false;
    now.smellOrange = false;

    Q.push(now);
    vis[0][0][4][0][0] = 0;

    while (!Q.empty()) {
        now = Q.front();
        Q.pop();
        state next;

        if (grid[now.x][now.y] == 4 && now.wasOnPurple == true) {
            int nextx = now.x + di[now.lastDir];
            int nexty = now.y + dj[now.lastDir];
            if (ok(nextx, nexty) && grid[nextx][nexty] != 0 && grid[nextx][nexty] != 3) {
                next.x = nextx;
                next.y = nexty;
                next.smellOrange = false;
                next.wasOnPurple = true;
                next.lastDir = now.lastDir;
                markVis(next, now);
                Q.push(next);
                continue;
            } else {
                next.x = now.x;
                next.y = now.y;
                next.smellOrange = false;
                next.wasOnPurple = false;
                next.lastDir = 4;
            }
        }

        for (int i=0; i<4; i++) {
            next.x = now.x+di[i];
            next.y = now.y+dj[i];
            next.smellOrange = now.smellOrange;
            next.wasOnPurple = now.wasOnPurple;
            next.lastDir = 4;
            if (ok(next.x, next.y)) {
                if (grid[next.x][next.y] == 0) continue;
                if (grid[next.x][next.y] == 1) {
                    if (valOfVis(next) == -1) {
                        markVis(next, now);
                        Q.push(next);
                    }
                } else if (grid[next.x][next.y] == 2) {
                    next.smellOrange = true;
                    if (valOfVis(next) == -1) {
                        markVis(next, now);
                        Q.push(next);
                    }
                } else if (grid[next.x][next.y] == 3) {
                    if (next.smellOrange && valOfVis(next) == -1) {
                        markVis(next, now);
                        Q.push(next);
                    }
                } else if (grid[next.x][next.y] == 4) {
                    next.wasOnPurple = true;
                    next.lastDir = i;
                    next.smellOrange = false;
                    if (valOfVis(next) == -1) {
                        markVis(next, now);
                        Q.push(next);
                    }
                }
            }
        }
    }
}

int main()
{
    freopen("dream.in", "r", stdin);
    freopen("dream.out", "w", stdout);

    scanf("%d %d", &N, &M);

    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
            scanf("%d", &grid[i][j]);

    for (int i=0; i<4; i++) for (int j=0; j<5; j++)
        for (int k=0; k<N; k++) for (int c=0; c<M; c++)
            vis[i/2][i%2][j][k][c] = -1;

    bfs();

    int minAns = -1;
    for (int i=0; i<4; i++) for (int j=0; j<5; j++) {
        if (minAns == -1) minAns = vis[i/2][i%2][j][N-1][M-1];
        else if (vis[i/2][i%2][j][N-1][M-1] != -1 && minAns != -1) minAns = min(minAns, vis[i/2][i%2][j][N-1][M-1]);
    }

    printf("%d\n", minAns);

    return 0;
}
