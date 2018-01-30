// My solution in ORDERSET using segment tree
// As segment tree is a static data structure, my solution is offline
// ie it first reads the whole data and performs data compression

#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <utility>
#include <vector>
#include <math.h>
#include <stack>
#include <map>
#include <set>

#define MAXQ 200010
#define l 2*pos
#define r 2*pos+1
#define mid (i+j)/2

using namespace std;

typedef pair < int, int > ii;
typedef pair < char, int > ci;

/**
    OFFLINE SOLUTION OF ORDERSET
    USING SEGMENT TREES
    AND VALUE COMPRESSION
**/

int Q, N;

set < int > numbers;
vector < ci > queries;

int idx[MAXQ];
int seg_tree[4*MAXQ];

void Read() {
    ios_base::sync_with_stdio(false);
    cin >> Q;

    for (int i=0; i<Q; i++) {  /// offline initialization
        int x; char c;
        cin >> c >> x;
        queries.push_back(ci(c, x));
        numbers.insert(x);
    }

    N = 1;
    for (set<int>::iterator t = numbers.begin(); t!=numbers.end(); ++t) {
        idx[N] = *t;
        N ++;
    }
    N --;
}

///  SEGMENT TREE FUNCTIONS

int target, type;
void update(int pos, int i, int j) {
    if (i == j) {
        seg_tree[pos] = type;
        return;
    }

    if (target <= mid) update(l, i, mid);
    else update(r, mid+1, j);

    seg_tree[pos] = seg_tree[l]+seg_tree[r];
}

int K;
int Kth(int pos, int i, int j) {
    if (i == j)
        return i;

    if (seg_tree[l] >= K)
        return Kth(l, i, mid);
    K -= seg_tree[l];
    return Kth(r, mid+1, j);
}

int sum(int pos, int i, int j) {
    if (j <= target)
        return seg_tree[pos];

    if (i == j)
        return 0;

    if (target <= mid)
        return sum(l, i, mid);
    return seg_tree[l] + sum(r, mid+1, j);
}

int bSearch(int elem) {
    int high=N, low=0;

    while (low <= high) {
        int med = (low+high)/2;
        if (idx[med] == elem)
            return med;
        else if (idx[med] < elem)
            low = med+1;
        else high = med-1;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);

    Read();

    for (int i=0; i<Q; i++) {

        /// INSERT

        if (queries[i].first == 'I') {
            target = bSearch(queries[i].second);
            type = 1;
            update(1, 1, N);
        }

        /// DELETE

        else if (queries[i].first == 'D') {
            target = bSearch(queries[i].second);
            type = 0;
            update(1, 1, N);
        }

        /// COUNT

        else if (queries[i].first == 'C') {

            /// binary search
            int low=1, high=N, ans=0;

            while (low <= high) {
                int med = (low+high)/2;
                if (idx[med] < queries[i].second) {
                    ans = max(ans, med);
                    low = med + 1;
                } else {
                    high = med - 1;
                }
            }
            target = ans;

            cout << sum(1, 1, N) << "\n";
        }

        /// KTH

        else {
            K = queries[i].second;
            if (K > seg_tree[1])
                cout << "invalid\n";
            else
                cout << idx[Kth(1, 1, N)] << "\n";
        }
    }

    return 0;
}
