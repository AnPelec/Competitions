#include <bits/stdc++.h>

#define MAXN 50010

using namespace std;

int N;
int oppCards[MAXN], cards[MAXN];
bool use[2*MAXN];

int maxHighScore() {
    int score = 0;
    int myHighIdx = N-1;

    for (int i=N/2-1; i>=0; i--) {
        if (oppCards[i] < cards[myHighIdx]) {
            score ++;
            myHighIdx --;
        }
    }

    return score;
}

int maxLowScore() {
    int score = 0;
    int myHighIdx = 0;

    for (int i=N/2; i<N; i++) {
        if (oppCards[i] > cards[myHighIdx]) {
            score ++;
            myHighIdx ++;
        }
    }

    return score;
}

int main()
{
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);

    scanf("%d", &N);
    for (int i=0; i<N; i++) {
        scanf("%d", &oppCards[i]);
        use[oppCards[i]] = true;
    }

    int idx = 0;
    for (int i=1; i<=2*N; i++) {
        if (use[i] == false)
            cards[idx ++] = i;
    }

    sort(oppCards, oppCards+N/2);
    sort(oppCards+N/2, oppCards+N);

    printf("%d\n", (maxHighScore() + maxLowScore()));

    return 0;
}
