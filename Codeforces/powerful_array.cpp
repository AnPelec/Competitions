/**
  Yandex Algorithm Round 2
  Problem D
  Solution Uses MO's algorithm --- square root decomposition on queries
**/

#include <algorithm>
#include <utility>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <stack>

#define MAXN 200010
#define RANGE 1000010

using namespace std;

typedef pair < int, int > ii;
typedef pair < ii, ii > iiii;
typedef unsigned long long ll;

ll ans;
int x, y;
int N, B, t;
ll answers[MAXN];
int countx[RANGE], nums[MAXN];
vector < iiii > queries;

void add(int x) {
    ll tmp = (2*countx[x-1]+1)*x;
    ans += tmp;
    countx[x-1] ++;
}

void subt(int x) {
    ll tmp = (2*countx[x-1]-1)*x;
    ans -= tmp;
    countx[x-1] --;
}

bool check(const iiii& a, const iiii& b) {
    if (a.first.first == b.first.first)
        return a.second.second < b.second.second;
    return a.first.first < b.first.first;
}

int main()
{
    scanf("%d %d", &N, &t);

    queries.reserve(t+2);
    B = floor(sqrt(N));

    for (int i=0; i<N; i++)
        scanf("%d", &nums[i]);

    for (int i=0; i<t; i++) {
        scanf("%d %d", &x, &y);
        x --; y --;
        int buck = x/B;
        queries.push_back(iiii(ii(buck, i), ii(x, y)));
    }

    sort(queries.begin(), queries.end(), check);

    int nowL=0, nowR=0;
    countx[nums[0]-1] = 1;
    ans = nums[0];

    for (int i=0; i<t; i++) {
        int targetL = queries[i].second.first;
        int targetR = queries[i].second.second;

        while (targetL < nowL) {
            nowL --;
            add(nums[nowL]);
        }

        while (nowL < targetL) {
            subt(nums[nowL]);
            nowL ++;
        }

        while (nowR < targetR) {
            nowR ++;
            add(nums[nowR]);
        }

        while (targetR < nowR) {
            subt(nums[nowR]);
            nowR --;
        }

        answers[queries[i].first.second] = ans;
    }

    for (int i=0; i<t; i++)
        printf("%I64d\n", answers[i]);

    return 0;
}
