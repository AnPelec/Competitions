#include <bits/stdc++.h>

#define x first
#define y second
#define MAXR 1000010
#define MAXN 100010

#define l 2*pos
#define r 2*pos+1
#define mid (i+j)/2

using namespace std;

typedef pair < int, int > ii;

int N;
ii cows[MAXN];
int seg_tree[4*MAXR];
int cumCows[MAXR]; /// find how many cows have y-coord less than i
int bestAns;

void update(int pos, int i, int j, int target) {
    if (i == j) {
        seg_tree[pos]++;
        return;
    }

    if (target <= mid)
        update(l, i, mid, target);
    else
        update(r, mid+1, j, target);

    seg_tree[pos] = seg_tree[l] + seg_tree[r];
}

int queryLeftPriority(int pos, int i, int j, int holdUp, int holdDown) {
    int C = holdDown, B = holdUp, down = cumCows[mid];  /// down = C+D
    if (i != j) {
        C += seg_tree[l];
        B += seg_tree[r];
    }

    int D = down-C;
    int A = N-B-C-D;

    int retVal = max(max(A, B), max(C, D));

    if (i == j) return retVal;

    if ((A == D && C > B) || (D > A))// && ((mid+i)/2) != mid) {
        return min(retVal, queryLeftPriority(l, i, mid, holdUp+seg_tree[r], holdDown));
    //}
    else// if ((mid+1+j)/2 != mid) {
        return min(retVal, queryLeftPriority(r, mid+1, j, holdUp, holdDown+seg_tree[l]));
    //}
}

int queryRightPriority(int pos, int i, int j, int holdUp, int holdDown) {
    int C = holdDown, B = holdUp, down = cumCows[mid];  /// down = C+D
    if (i != j) {
        C += seg_tree[l];
        B += seg_tree[r];
    }

    int D = down-C;
    int A = N-B-C-D;

    int retVal = max(max(A, B), max(C, D));

    if (i == j) return retVal;

    if ((A == D && C > B) || (D > A))// && ((mid+i)/2) != mid) {
        return min(retVal, queryRightPriority(l, i, mid, holdUp+seg_tree[r], holdDown));
    //}
    else// if ((mid+1+j)/2 != mid) {
        return min(retVal, queryRightPriority(r, mid+1, j, holdUp, holdDown+seg_tree[l]));
    //}
}

int query(int pos, int i, int j, int holdUp, int holdDown) {
    int C = holdDown, B = holdUp, down = cumCows[mid];  /// down = C+D
    if (i != j) {
        C += seg_tree[l];
        B += seg_tree[r];
    }

    int D = down-C;
    int A = N-B-C-D;

    int retVal = max(max(A, B), max(C, D));

    if ((i == j) || (mid == (i+mid)/2)) return retVal;

    if (retVal == A || retVal == B)
        return min(retVal, query(r, mid+1, j, holdUp, holdDown+seg_tree[l]));
    return min(retVal, query(l, i, mid, holdUp+seg_tree[r], holdDown));
}



int main()
{
    ifstream fin("balancing.in");
    ofstream fout("balancing.out");

    fin >> N;
    for (int i=0; i<N; i++) {
        fin >> cows[i].x >> cows[i].y;
        cumCows[cows[i].y] ++;
    }
    sort(cows, cows+N);
    for (int i=1; i<MAXR; i++)
        cumCows[i] += cumCows[i-1];

    /// brute force x-coordinate
    bestAns = N;
    int xIdx = 0;
    while (xIdx < N) {
        update(1, 1, MAXR, cows[xIdx].y);
        while (xIdx < N-1 && cows[xIdx].x == cows[xIdx+1].x) {
            xIdx ++;
            update(1, 1, MAXR, cows[xIdx].y);
        }
        int choice1 = query(1, 1, MAXR, 0, 0); //queryLeftPriority(1, 1, MAXR, 0, 0);
        int choice2 = query(1, 1, MAXR, 0, 0); //queryRightPriority(1, 1, MAXR, 0, 0);
        //cout << xIdx << " " << choice1 << " vs " << choice2 << endl;

        bestAns = min(bestAns, min(choice1, choice2));
        xIdx ++;
    }

    fout << bestAns << endl;

    return 0;
}
