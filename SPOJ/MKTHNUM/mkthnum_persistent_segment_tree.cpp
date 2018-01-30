// K-th Number Solution
// Solution is offline and uses a persistent version of segment tree
// Total complexity is O(NlogN)

#include <bits/stdc++.h>
 
#define MAXN 100010
#define LOG 17
 
#define mid (i+j)/2
 
using namespace std;
 
typedef pair < int, int > ii;
 
int N, M;
int freq[MAXN];
int original[MAXN], coord[MAXN];
int nums[MAXN], compressed[MAXN];
 
int seg_tree[4*MAXN*LOG];
int L[4*MAXN*LOG], R[4*MAXN*LOG];
 
int root[MAXN];
int nextIdx=1, initialRoot;
 
void build(int pos, int i, int j) {
    if (i == j) {
        seg_tree[pos] = freq[i];
        return;
    }
 
    L[pos] = nextIdx ++;
    R[pos] = nextIdx ++;
 
    build(L[pos], i, mid);
    build(R[pos], mid+1, j);
 
    seg_tree[pos] = seg_tree[L[pos]] + seg_tree[R[pos]];
}
 
int update(int pos, int i, int j, int target) {
    int idx = nextIdx ++;
 
    if (i == j) {
        seg_tree[idx] = freq[i];
        return idx;
    }
 
    L[idx] = L[pos];
    R[idx] = R[pos];
 
    if (target <= mid)
        L[idx] = update(L[idx], i, mid, target);
    else
        R[idx] = update(R[idx], mid+1, j, target);
 
    seg_tree[idx] = seg_tree[L[idx]] + seg_tree[R[idx]];
 
    return idx;
}
 
int query(int posL, int posR, int i, int j, int K) {
    if (i == j) return i;
    if (seg_tree[L[posR]] - seg_tree[L[posL]] >= K)
        return query(L[posL], L[posR], i, mid, K);
    K -= (seg_tree[L[posR]] - seg_tree[L[posL]]);
    return query(R[posL], R[posR], mid+1, j, K);
}
 
void Read() {
    scanf("%d %d", &N, &M);
 
    for (int i=0; i<N; i++) {
        scanf("%d", &nums[i]);
        coord[i] = nums[i];
    }
}
 
int main()
{
    Read();
 
    sort(coord, coord+N);
 
    for (int i=0; i<N; i++) {
        compressed[i] = lower_bound(coord, coord+N, nums[i]) - coord;
        original[compressed[i]] = nums[i];
    }
 
    build(initialRoot, 0, N-1);
 
    for (int i=0; i<N; i++) {
        freq[compressed[i]] ++;
        root[i] = update((i == 0 ? initialRoot : root[i-1]), 0, N-1, compressed[i]);
    }
 
    int x, y, K, startIdx;
    for (int i=0; i<M; i++) {
        scanf("%d %d %d", &x, &y, &K);
        x --; y --;
        if (x == 0) startIdx = initialRoot;
        else        startIdx = root[x-1];
        printf("%d\n", original[query(startIdx, root[y], 0, N-1, K)]);
    }
 
    return 0;
}
